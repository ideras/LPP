#include <cmath>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include "lpp_interp.h"
#include "lpp_serializer.h"
#include "lpp_exception.h"

struct BiProcInfo
{
    std::string name;
    std::initializer_list<ProcInfo::Param> params;
    TypeInfoSPtr rt_type;
};

BiProcInfo bi_procs[] = {
    { "nueva_linea", {}, nullptr },
    { "longitud", { {"str", TypeInfo::String(0)} }, TypeInfo::Int },
    { "entero_a_cadena", { {"num", TypeInfo::Int} }, TypeInfo::String(0) },
    { "real_a_cadena", { {"num", TypeInfo::Real}, {"prec", TypeInfo::Int} }, TypeInfo::String() },
    { "valor_ascii", { {"ch", TypeInfo::Char} }, TypeInfo::Int },
    { "caracter_ascii", { {"code", TypeInfo::Int} }, TypeInfo::Char },
    { "inicializar_aleatorio", {}, nullptr },
    { "aleatorio", {}, TypeInfo::Real },
    { "limpiar_pantalla", {}, nullptr },
    { "color_texto",  { {"color", TypeInfo::Int} }, nullptr },
    { "color_fondo",  { {"color", TypeInfo::Int} }, nullptr },
    { "posicionar_cursor",  { {"row", TypeInfo::Int}, {"col", TypeInfo::Int} }, nullptr },
    { "obtener_caracter", {}, TypeInfo::Char },
    { "obtener_tecla", {}, TypeInfo::Int },
    { "obtener_caracter", {}, TypeInfo::Bool },
    { "pausa", { {"millis", TypeInfo::Int} }, nullptr },
    { "fda", { {"fh", TypeInfo::Int} }, nullptr },
    { "fda", { {"fh", TypeInfo::Int} }, nullptr },
    { "ir_a_inicio", { {"fh", TypeInfo::File} }, nullptr },
    { "ir_a_fin", { {"fh", TypeInfo::File} }, nullptr },
    { "ir_a", { {"fh", TypeInfo::File}, {"pos", TypeInfo::Int} }, nullptr },
    { "posicion_actual", { {"fh", TypeInfo::File} }, nullptr },
};

static constexpr int BIPROC_COUNT = sizeof(bi_procs)/sizeof(bi_procs[0]);

#define HANDLE_STMT_NODE(TNode, node) \
        case Ast::NodeKind::TNode :  \
            visit(node->cptr<Ast::TNode>()); \
            return LppVariant::Empty

#define HANDLE_EXPR_NODE(TNode, node) \
        case Ast::NodeKind::TNode :  \
            return visit(node->cptr<Ast::TNode>())

#define HANDLE_VARREF_NODE(TNode, node, extra_arg) \
    case Ast::NodeKind::TNode :  \
        return visit(node->cptr<Ast::TNode>(), extra_arg)

void LppInterp::loadBuiltinProcs()
{
    for (int i = 0; i < BIPROC_COUNT; i ++) {
        std::string name(bi_procs[i].name);

        proc_map.add(name,
                     ProcInfo::create(name, bi_procs[i].params, bi_procs[i].rt_type));
    }
}

LppVariant LppInterp::AstVisitor::visit(const Ast::Node *root)
{
    switch (root->getKind()) {
        // Statements
        HANDLE_STMT_NODE(AssignStmt, root);
        HANDLE_STMT_NODE(IfStmt, root);
        HANDLE_STMT_NODE(CallStmt, root);
        HANDLE_STMT_NODE(CaseStmt, root);
        HANDLE_STMT_NODE(WhileStmt, root);
        HANDLE_STMT_NODE(RepeatStmt, root);
        HANDLE_STMT_NODE(ForStmt, root);
        HANDLE_STMT_NODE(ReadStmt, root);
        HANDLE_STMT_NODE(WriteStmt, root);
        HANDLE_STMT_NODE(OpenFileStmt, root);
        HANDLE_STMT_NODE(ReadFileStmt, root);
        HANDLE_STMT_NODE(WriteFileStmt, root);
        HANDLE_STMT_NODE(CloseFileStmt, root);
        HANDLE_STMT_NODE(ReturnStmt, root);

        // Expressions
        HANDLE_EXPR_NODE(LtExpr, root);
        HANDLE_EXPR_NODE(GtExpr, root);
        HANDLE_EXPR_NODE(LteExpr, root);
        HANDLE_EXPR_NODE(GteExpr, root);
        HANDLE_EXPR_NODE(EqExpr, root);
        HANDLE_EXPR_NODE(NeqExpr, root);
        HANDLE_EXPR_NODE(AddExpr, root);
        HANDLE_EXPR_NODE(SubExpr, root);
        HANDLE_EXPR_NODE(MultExpr, root);
        HANDLE_EXPR_NODE(IDivExpr, root);
        HANDLE_EXPR_NODE(DivExpr, root);
        HANDLE_EXPR_NODE(ModExpr, root);
        HANDLE_EXPR_NODE(PowExpr, root);
        HANDLE_EXPR_NODE(OrExpr, root);
        HANDLE_EXPR_NODE(AndExpr, root);
        HANDLE_EXPR_NODE(NotExpr, root);
        HANDLE_EXPR_NODE(NegExpr, root);
        HANDLE_EXPR_NODE(PlusExpr, root);
        HANDLE_EXPR_NODE(FuncCallExpr, root);
        HANDLE_EXPR_NODE(LhsExpr, root);
        HANDLE_EXPR_NODE(IndexVar, root);
        HANDLE_EXPR_NODE(SimpleVar, root);
        HANDLE_EXPR_NODE(BoolConstExpr, root);
        HANDLE_EXPR_NODE(StrConstExpr, root);
        HANDLE_EXPR_NODE(CharConstExpr, root);
        HANDLE_EXPR_NODE(IntConstExpr, root);
        HANDLE_EXPR_NODE(RealConstExpr, root);
        default:
            throw std::runtime_error("Invalid statement kind '" + root->kindName() + "' in Statement visitor");
    }
}

LppVariant LppInterp::AstVisitor::visit(const Ast::VarRef *expr, LppVariant &parent_val)
{
    switch (expr->getKind()) {
        HANDLE_VARREF_NODE(IndexVar, expr, parent_val);
        HANDLE_VARREF_NODE(SimpleVar, expr, parent_val);
        default:
            throw std::runtime_error("Invalid node kind '" + expr->kindName() + "' in VarRef visitor");
    }
}

std::tuple<LppVariant, LppVariant> LppInterp::AstVisitor::visit(const Ast::BinaryExpr *expr)
{
    LppVariant val1 = visit(expr->getExpr1());
    LppVariant val2 = visit(expr->getExpr2());

    return { val1, val2 };
}

LppVariant LppInterp::AstVisitor::visit(const Ast::RelExpr *expr)
{
    auto [val1, val2] = visit(expr->cptr<Ast::BinaryExpr>());

    switch (expr->getKind()) {
        case Ast::NodeKind::LtExpr: return val1 < val2; break;
        case Ast::NodeKind::GtExpr: return val1 > val2; break;
        case Ast::NodeKind::EqExpr: return val1 == val2; break;
        case Ast::NodeKind::NeqExpr: return val1 != val2; break;
        case Ast::NodeKind::LteExpr: return val1 <= val2; break;
        case Ast::NodeKind::GteExpr: return val1 >= val2; break;
        default:
            throw std::runtime_error("Invalid operator in RelExpr");
    }
}

LppVariant LppInterp::AstVisitor::visit(const Ast::AddExpr *expr)
{
    auto [val1, val2] = visit(expr->cptr<Ast::BinaryExpr>());

    if (val1.isInt() && val2.isInt()) {
        return val1.toInt() + val2.toInt();
    } else if ( (val1.isInt() && val2.isReal())
               || (val1.isReal() && val2.isInt())
               || (val1.isReal() && val2.isReal()) ) {
        return val1.toReal() + val2.toReal();
    }
    else if (val1.isString() && val2.isString()) {
        return val1.stringCRef() + val2.stringCRef();
    }
    else if (val1.isString() && val2.isChar()) {
        return val1.stringCRef() + val2.toChar();
    }
    else if (val1.isChar() && val2.isString()) {
        return val1.toChar() + val2.stringCRef();
    } else {
        throw std::runtime_error("Invalid values in AddExpr");
    }
}

LppVariant LppInterp::AstVisitor::visit(const Ast::SubExpr *expr)
{
    auto [val1, val2] = visit(expr->cptr<Ast::BinaryExpr>());

    if (val1.isInt() && val2.isInt()) {
        return val1.toInt() - val2.toInt();
    } else if ( (val1.isInt() && val2.isReal())
               || (val1.isReal() && val2.isInt())
               || (val1.isReal() && val2.isReal()) ) {
        return val1.toReal() - val2.toReal();
    } else {
        throw std::runtime_error("Invalid values in SubExpr");
    }
}

LppVariant LppInterp::AstVisitor::visit(const Ast::MultExpr *expr)
{
    auto [val1, val2] = visit(expr->cptr<Ast::BinaryExpr>());

    if (val1.isInt() && val2.isInt()) {
        return val1.toInt() * val2.toInt();
    } else if ( (val1.isInt() && val2.isReal())
               || (val1.isReal() && val2.isInt())
               || (val1.isReal() && val2.isReal()) ) {
        return val1.toReal() * val2.toReal();
    } else {
        throw std::runtime_error("Invalid values in MultExpr");
    }
}

LppVariant LppInterp::AstVisitor::visit(const Ast::IDivExpr *expr)
{
    auto [val1, val2] = visit(expr->cptr<Ast::BinaryExpr>());

    return val1.toInt() / val2.toInt();
}

LppVariant LppInterp::AstVisitor::visit(const Ast::DivExpr *expr)
{
    auto [val1, val2] = visit(expr->cptr<Ast::BinaryExpr>());

    return val1.toReal() / val2.toReal();
}

LppVariant LppInterp::AstVisitor::visit(const Ast::ModExpr *expr)
{
    auto [val1, val2] = visit(expr->cptr<Ast::BinaryExpr>());

    return val1.toInt() % val2.toInt();
}

LppVariant LppInterp::AstVisitor::visit(const Ast::PowExpr *expr)
{
    auto [val1, val2] = visit(expr->cptr<Ast::BinaryExpr>());

    if (val1.isInt() && val2.isInt()) {
        return static_cast<Lpp::Int>(pow(val1.toInt(), val2.toInt()));
    } else if ( (val1.isInt() && val2.isReal())
               || (val1.isReal() && val2.isInt())
               || (val1.isReal() && val2.isReal()) ) {
        return pow(val1.toReal(), val2.toReal());
    } else {
        throw std::runtime_error("Invalid values in PowerExpr");
    }
}

LppVariant LppInterp::AstVisitor::visit(const Ast::OrExpr *expr)
{
    auto [val1, val2] = visit(expr->cptr<Ast::BinaryExpr>());

    if (val1.isBool() && val2.isBool()) {
        return val1.toBool() || val2.toBool();
    } else if (val1.isNumber() && val2.isNumber()) {
        return val1.toInt() | val2.toInt();
    } else {
        throw std::runtime_error("Invalid values in OrExpr");
    }
}

LppVariant LppInterp::AstVisitor::visit(const Ast::AndExpr *expr)
{
    auto [val1, val2] = visit(expr->cptr<Ast::BinaryExpr>());

    if (val1.isBool() && val2.isBool()) {
        return val1.toBool() && val2.toBool();
    } else if (val1.isNumber() && val2.isNumber()) {
        return val1.toInt() & val2.toInt();
    } else {
        throw std::runtime_error("Invalid values in AndExpr");
    }
}

LppVariant LppInterp::AstVisitor::visit(const Ast::NotExpr *expr)
{
    LppVariant val = visit(expr->getExpr());

    if (val.isBool()) {
        return !val.toBool();
    } else if (val.isNumber()) {
        return ~val.toInt();
    } else {
        throw std::runtime_error("Invalid values in NotExpr");
    }
}

LppVariant LppInterp::AstVisitor::visit(const Ast::NegExpr *expr)
{
    LppVariant val = visit(expr->getExpr());

    if (val.isInt()) {
        return -val.toInt();
    } else if (val.isReal()) {
        return -val.toReal() ;
    } else {
        throw std::runtime_error("Invalid values in NegExpr");
    }
}

LppVariant LppInterp::AstVisitor::visit(const Ast::PlusExpr *expr)
{
    LppVariant val = visit(expr->getExpr());

    if (val.isInt()) {
        return val.toInt();
    } else if (val.isReal()) {
        return val.toReal();
    } else {
        throw std::runtime_error("Invalid values in PlusExpr");
    }
}

LppVariant LppInterp::AstVisitor::visit(const Ast::FuncCallExpr *expr)
{
    ProcInfoSPtr fi = procs.get(expr->getName());

    const auto& params = fi->params();
    int index = 0;

    std::vector<LppVariant> arg_vals;
    for (const auto& arg : expr->getArgs()) {
        LppVariant aval = visit(arg.get());

        if (!params[index].isByref() && aval.isPtr()) {
            aval = aval.getPointedValue();
        }
        arg_vals.push_back(aval);
        index++;
    }

    if (fi->isBuiltin()) {
        LppVariant val = lpp_rt.call(fi->name(), arg_vals);

        return val ;
    }

    ProcFrameUPtr proc_frm = fi->makeProcFrame(arg_vals);

    call_stack.push_back(std::move(proc_frm));

    LppVariant ret_val;
    for (const auto& s : fi->stmts()) {
        try {
            visit(s);
        } catch (const ReturnException& rex) {
            ret_val = rex.getValue();
        }
    }

    call_stack.pop_back();
    return ret_val;
}

LppVariant LppInterp::AstVisitor::visit(const Ast::LhsExpr *expr)
{
    auto it = expr->getIndexVars().begin();
    const auto& v = *it;

    LppVariant lval = visit(v->cptr<Ast::VarRef>(), LppVariant::Empty);

    it++;
    while (it != expr->getIndexVars().end()) {
        const auto& v = *it;

        LppVariant rval = visit(v->cptr<Ast::VarRef>(), lval);

        it ++;
        lval = rval;
    }

    return lval;
}

LppVariant LppInterp::AstVisitor::visit(const Ast::IndexVar *expr, LppVariant &parent_val)
{
    LppVariant lval = visit(expr->getVarExpr<Ast::VarRef>(), parent_val);
    
    std::vector<int> idxs;
    for (const auto& eidx : expr->getIndexes()) {
        LppVariant eval = visit(eidx.get());

        idxs.push_back(eval.toInt() - 1);
    }

    const TypeInfo* ti = expr->getVarExpr<Ast::Expr>()->getTypeInfo();
    if (ti->is(TypeInfo::Kind::Array)) {
        const ArrayTypeInfo *ati = ti->cptr<ArrayTypeInfo>();
        size_t index = ati->flatIndex(idxs);

        if (index >= lval.arrayRef().size()) {
            throw LPPException(expr->getSrcLine(), "El indice del arreglo esta fuera de rango");
        }

        return std::addressof(lval.arrayRef().at(index));
    } else if (ti->is(TypeInfo::Kind::String)) {
        size_t index = idxs[0];

        if (index >= lval.stringCRef().size()) {
            throw LPPException(expr->getSrcLine(), "El indice de la cadena esta fuera de rango");
        }

        return std::addressof(lval.stringRef().at(idxs[0]));
    } else {
        throw LPPException(expr->getSrcLine(), "Variable con indizacion debe ser de tipo arreglo o cadena");
    }
}

LppVariant LppInterp::AstVisitor::visit(const Ast::SimpleVar *expr, LppVariant& parent_val)
{
    if (expr->getRecordTypeInfo()) {
        const RecordTypeInfo* rti = expr->getRecordTypeInfo();
        const RecordTypeInfo::FieldInfo* fldi = rti->field(expr->getName());
        
        return std::addressof(parent_val.arrayRef().at(fldi->index()));
    } else {
        LppVarSPtr var (nullptr);

        if (!call_stack.empty()) {
            var = call_stack.back()->getVar(expr->getName());
        }
        if (var == nullptr) {
            var = vars.get(expr->getName());
        }

        if (var->value().isPtr())
            return var->value();
        else
            return std::addressof(var->value());
    }
}

LppVariant LppInterp::AstVisitor::visit(const Ast::BoolConstExpr *expr)
{
    return expr->getConstValue();
}

LppVariant LppInterp::AstVisitor::visit(const Ast::StrConstExpr *expr)
{
    return expr->getConstValue();
}

LppVariant LppInterp::AstVisitor::visit(const Ast::CharConstExpr *expr)
{
    return expr->getConstValue();
}

LppVariant LppInterp::AstVisitor::visit(const Ast::IntConstExpr *expr)
{
    return expr->getConstValue();
}

LppVariant LppInterp::AstVisitor::visit(const Ast::RealConstExpr *expr)
{
    return expr->getConstValue();
}

void LppInterp::AstVisitor::visit(const Ast::AssignStmt *stmt)
{
    LppVariant lval = visit(stmt->getLhs());
    LppVariant rval = visit(stmt->getRhs());

    if (lval.isInt()) {
        lval.setPointedValue(rval.toInt());
    } else if (lval.isReal()) {
        lval.setPointedValue(rval.toReal());
    } else if (lval.isString() && rval.isChar()) {
        lval.setPointedValue(std::string(1, rval.toChar()));
    } else if (lval.isChar() && rval.isString()) {
        lval.setPointedValue(rval.stringCRef()[0]);
    } else {
        lval.setPointedValue(rval);
    }
}

void LppInterp::AstVisitor::visit(const Ast::IfStmt *stmt)
{
    for (const auto& blk : stmt->getCondBlocks()) {
        const auto& cblk = blk->cref<Ast::IfStmt::CondBlock>();

        LppVariant val = visit(cblk.getCond());

        if (val.toBool()) {
            for (const auto& s : cblk.getStmts()) {
                visit(s->cptr<Ast::Stmt>());
            }
            return;
        }
    }
    if (stmt->hasElseBlock()) {
        for (const auto& s : stmt->getElseStmts()) {
            visit(s->cptr<Ast::Stmt>());
        }
    }
}

void LppInterp::AstVisitor::visit(const Ast::CallStmt *stmt)
{
    const Ast::Expr* func_call = stmt->getFuncCallExpr()->cptr<Ast::Expr>();
    visit(func_call);
}

void LppInterp::AstVisitor::visit(const Ast::CaseStmt *stmt)
{
    LppVariant lval = visit(stmt->getVarExpr());

    for (const auto& blk : stmt->getCondBlocks()) {
        const auto& cblk = blk->cref<Ast::CaseStmt::CondBlock>();

        std::vector<CaseLiteral> literals = getCaseLiterals(cblk.getCondValues());

        auto it = std::find_if(literals.begin(), literals.end(),
                               [&lval, &blk] (const CaseLiteral& litv) {
                                    const auto& [v1, v2] = litv;
                                    if (v2.isEmpty()) {
                                        if (lval.isInt() && v1.isNumber()) {
                                            return lval.toInt() == v1.toInt();
                                        } else if (lval.isReal() && v1.isNumber()) {
                                            return lval.toReal() == v1.toReal();
                                        } else if (lval.isChar() && v1.isChar()) {
                                            return lval.toChar() == v1.toChar();
                                        } else {
                                            throw LPPException(blk->getSrcLine(), "Valor literal de tipo no compatible con la variable de la sentencia 'caso'");
                                        }
                                    } else {
                                        if (lval.isInt() && v1.isNumber() && v2.isNumber()) {
                                            return (lval.toInt() >= v1.toInt()) && (lval.toInt() <= v2.toInt());
                                        } else if (lval.isReal() && litv.first.isNumber()) {
                                            return (lval.toReal() >= v1.toReal()) && (lval.toReal() <= v2.toReal());
                                        } else if (lval.isChar() && litv.first.isChar()) {
                                            return (lval.toChar() >= v1.toChar()) && (lval.toChar() <= v2.toChar());
                                        } else {
                                            throw LPPException(blk->getSrcLine(), "Valor literal de tipo no compatible con la variable de la sentencia 'caso'");
                                        }
                                    }
                                });

        if (it != literals.end()) {
            for (const auto& s : cblk.getStmts()) {
                visit(s.get());
            }
            return;
        }
    }
    if (stmt->hasElseBlock()) {
        for (const auto& s : stmt->getElseStmts()) {
            visit(s.get());
        }
    }
}

void LppInterp::AstVisitor::visit(const Ast::WhileStmt *stmt)
{
    LppVariant val = visit(stmt->getCond());

    while (val.toBool()) {
        for (const auto& ss : stmt->getStmts()) {
            visit(ss->cptr<Ast::Stmt>());
        }
        val = visit(stmt->getCond());
    }
}

void LppInterp::AstVisitor::visit(const Ast::RepeatStmt *stmt)
{
    LppVariant val;
    do {
        for (const auto& ss : stmt->getStmts()) {
            visit(ss->cptr<Ast::Stmt>());
        }
        val = visit(stmt->getCond());
    } while (!val.toBool());
}

void LppInterp::AstVisitor::visit(const Ast::ForStmt *stmt)
{
    LppVariant lval = visit(stmt->getVar());
    LppVariant val1 = visit(stmt->getExpr1());

    lval.setPointedValue(val1.toInt());
    
    LppVariant val2 = visit(stmt->getExpr2());
    
    while (lval.toInt() <= val2.toInt()) {
        for (const auto& s : stmt->getStmts()) {
            visit(s->cptr<Ast::Stmt>());
        }

        lval.setPointedValue(lval.toInt() + 1);
        val2 = visit(stmt->getExpr2());
    }
}

void LppInterp::AstVisitor::visit(const Ast::ReadStmt *stmt)
{
    for (const auto& lexpr : stmt->getLValueList()) {
        LppVariant lval = visit(lexpr.get());

        if (lval.isInt()) {
            lval.setPointedValue(term.readInt());
        } else if (lval.isReal()) {
            lval.setPointedValue(term.readReal());
        } else if (lval.isBool()) {
            lval.setPointedValue(term.readBool());
        } else if (lval.isChar()) {
            lval.setPointedValue(term.readChar());
        } else if (lval.isString()) {
            lval.setPointedValue(term.readString());
        } else {
            const TypeInfo* ti = lexpr->cptr<Ast::Expr>()->getTypeInfo();
            throw LPPException(stmt->getSrcLine(), "No se pueden leer variable de tipo '" + ti->kindName() + "'");
        }
        term.writeChar('\n');
    }
}

void LppInterp::AstVisitor::visit(const Ast::WriteStmt *stmt)
{
    for (const auto& expr : stmt->getExprList()) {
        LppVariant val = visit(expr.get());
        
        if (val.isInt()) {
            term.writeInt(val.toInt());
        } else if (val.isReal()) {
            term.writeReal(val.toReal());
        } else if (val.isChar()) {
            term.writeChar(val.toChar());
        } else if (val.isBool()) {
            term.writeString(val.toBool() ? "Verdadero" : "Falso");
        } else if (val.isString()) {
            term.writeString(val.stringCRef());
        } else {
            const TypeInfo* ti = expr->cptr<Ast::Expr>()->getTypeInfo();
            throw LPPException(stmt->getSrcLine(), "No se puede escribir variables de tipo " + ti->kindName());
        }
    }
}

void LppInterp::AstVisitor::visit(const Ast::OpenFileStmt *stmt)
{
    LppVariant v_fname = visit(stmt->getFileNameExpr());
    LppVariant v_ref = visit(stmt->getFileHandleVar());

    std::ios::openmode flags = std::ios::in;
    switch (stmt->getOpenFlags()) {
        case Ast::OpenFileStmt::Flags::ReadWrite:
            flags = std::ios::in | std::ios::out;
            break;
        case Ast::OpenFileStmt::Flags::Write:
            flags = std::ios::out;
            break;
        default:
            break;
    }

    int blk_size = 0;
    if (stmt->getFileType() == Ast::FileStmt::FileType::Binary) {
        const auto* fti = stmt->getFileHandleVar<Ast::Expr>()->getTypeInfo()->cptr<FileTypeInfo>();

        blk_size = fti->elemType()->byteSize();
        flags |= std::ios::binary;
    }

    int fh = file_manager.openFile(v_fname.stringCRef(), flags, blk_size);
    if (fh < 0) {
        throw LPPException(stmt->getSrcLine(), "No se pudo abrir el archivo '" + v_fname.stringCRef() + "'");
    }
    v_ref.setPointedValue(fh);
}

void LppInterp::AstVisitor::visit(const Ast::ReadFileStmt *stmt)
{
    const Ast::NodeList& nl_vars = stmt->getLValueList();
    auto it = nl_vars.begin();
    const Ast::NodeUPtr& n_fhvar = *it++;

    LppVariant v_fh = visit(n_fhvar.get());

    while (it != nl_vars.end()) {
        const Ast::NodeUPtr& n_var = *it++;
        LppVariant v_ref = visit(n_var.get());

        if (stmt->getFileType() == Ast::FileStmt::FileType::Text) {
            LppVariant val = file_manager.textRead(v_fh.toInt());
            if (val.isEmpty()) {
                throw LPPException(stmt->getSrcLine(), "No se pudo leer el valor deseado del archivo de texto.");
            }

            if (v_ref.isValPtr()) {
                if (!LppSerializer::sameType(v_ref, val)) {
                    throw LPPException(stmt->getSrcLine(), "El valor leido del archivo de texto no es del tipo deseado.");
                }
                v_ref.setPointedValue(val);
            }
        } else {
            const TypeInfo *ti = n_var->cptr<Ast::Expr>()->getTypeInfo();
            std::vector<char> bytes(ti->byteSize());

            int rcount = file_manager.binaryRead(v_fh.toInt(), bytes.data(), bytes.size());
            if (rcount != bytes.size()) {
                throw LPPException(stmt->getSrcLine(), "El valor leido del archivo binario no es del tipo deseado.");
            }

            if (v_ref.isValPtr()) {
                if (!LppSerializer::fromBinary(v_ref, ti, bytes)) {
                    throw LPPException(stmt->getSrcLine(), "El valor leido del archivo binario no es del tipo deseado.");
                }
            }
        }
    }
}

void LppInterp::AstVisitor::visit(const Ast::WriteFileStmt *stmt)
{
    const Ast::NodeList& nl_expr = stmt->getExprList();
    auto it = nl_expr.begin();
    const Ast::NodeUPtr& n_fhvar = *it++;

    LppVariant v_fh = visit(n_fhvar.get());

    while (it != nl_expr.end()) {
        const Ast::NodeUPtr& n_expr = *it++;
        LppVariant val = visit(n_expr.get());

        if (val.isValPtr()) {
            val = val.getPointedValue();
        }

        if (stmt->getFileType() == Ast::FileStmt::FileType::Text) {
            if (!file_manager.textWrite(v_fh.toInt(), val)) {
                throw LPPException(stmt->getSrcLine(), "No se pudo escribir el valor deseado en el archivo de texto.");
            }
        } else {
            const TypeInfoSPtr& ti = n_expr->cptr<Ast::Expr>()->getTypeInfoSPtr();
            std::vector<char> bytes = LppSerializer::toBinary(val, ti);

            if (!file_manager.binaryWrite(v_fh.toInt(), bytes.data(), bytes.size())) {
                throw LPPException(stmt->getSrcLine(), "No se pudo escribir el valor en el archivo binario.");
            }
        }
    }
}

void LppInterp::AstVisitor::visit(const Ast::CloseFileStmt *stmt)
{
    LppVariant v_fh = visit(stmt->getVarExpr());

    file_manager.closeFile(v_fh.toInt());
}

void LppInterp::AstVisitor::visit(const Ast::ReturnStmt *stmt)
{
    ProcFrame *proc_frm = call_stack.back().get();

    if (stmt->getExpr() != nullptr) {
        LppVariant val = visit(stmt->getExpr());
        if (val.isPtr()) {
            val = val.getPointedValue();
        }

        throw ReturnException(val);
    } else {
        if (proc_frm->retType() != nullptr) {
            throw LPPException(stmt->getSrcLine(), "Una funcion debe retornar una valor");
        }
    }
}

LppVariant LppInterp::AstVisitor::getCaseValue(const Ast::Expr *vexpr)
{
    switch (vexpr->getKind()) {
        case Ast::NodeKind::IntConstExpr:
            return vexpr->cref<Ast::IntConstExpr>().getConstValue();
        case Ast::NodeKind::RealConstExpr:
            return vexpr->cref<Ast::RealConstExpr>().getConstValue();
        case Ast::NodeKind::CharConstExpr:
            return vexpr->cref<Ast::CharConstExpr>().getConstValue();
        default:
            throw LPPException(vexpr->getSrcLine(), "Las constantes de la sentencia 'caso' solo pueden ser entero, real o caracter");
    }
}

std::vector<LppInterp::AstVisitor::CaseLiteral> LppInterp::AstVisitor::getCaseLiterals(const Ast::NodeList &literal_list)
{
    int src_line = literal_list.getSrcLine();

    std::vector<CaseLiteral> values;
    for (const auto& lit : literal_list) {
        switch (lit->getKind()) {
            case Ast::NodeKind::IntConstExpr:
            case Ast::NodeKind::RealConstExpr:
            case Ast::NodeKind::CharConstExpr:
                values.emplace_back(getCaseValue(lit->cptr<Ast::Expr>()), LppVariant::Empty);
                break;
            case Ast::NodeKind::CaseStmtCondRangeValue: {
                const auto& crv = lit->cref<Ast::CaseStmt::CondRangeValue>();
                values.emplace_back(getCaseValue(crv.getValue1()->cptr<Ast::Expr>()),
                                    getCaseValue(crv.getValue2()->cptr<Ast::Expr>()));
                break;
            }
            default:
                throw LPPException(src_line, "Las constantes de la sentencia 'caso' solo pueden ser entero, real o caracter");
        }
    }

    return values;
}

void LppInterp::exec(const Ast::Node *prg_node)
{
    if (prg_node->getKind() != Ast::NodeKind::Program) {
        throw std::runtime_error("Invalid program node '" + prg_node->toString() + "'");
    }
    semAnalysis(prg_node);

    for (auto& vp : var_map.items()) {
        LppVarSPtr& var = vp.second;
        var->createValue();
    }

    const auto *prg = prg_node->cptr<Ast::Program>();

    term = std::make_unique<Terminal>();
    LppInterp::AstVisitor visitor(var_map, udt_map, proc_map, *term);

    for (const auto& stmt : prg->getStmts()) {
        visitor.visit(stmt.get());
    }
}

void LppInterp::semAnalysis(const Ast::Node *prg_node)
{
    if (prg_node->getKind() != Ast::NodeKind::Program) {
        throw std::runtime_error("Invalid program node '" + prg_node->toString() + "'");
    }
    const auto *prg = prg_node->cptr<Ast::Program>();

    LppInterp::SemAnalysisVisitor visitor(var_map, udt_map, proc_map);

    loadBuiltinProcs();
    for (const auto& td : prg->getTypeDefs()) {
        visitor.visit(td.get());
    }

    for (const auto& vd : prg->getVarDecls()) {
        visitor.visit(vd.get());
    }

    std::vector<const ProcInfo *> procs;
    for (const auto& pd : prg->getProcDecls()) {
        const Ast::ProcDef *proc_def = pd->cptr<Ast::ProcDef>();

        const ProcInfo* pi = visitor.visit(proc_def);
        procs.push_back(pi);
    }
    for (const auto pi : procs) {
        visitor.visitProcStmts(pi);
    }

    for (const auto& stmt : prg->getStmts()) {
        visitor.visit(stmt.get());
    }
}
