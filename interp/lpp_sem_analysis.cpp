#include <stdexcept>
#include <unordered_set>
#include "lpp_ast.h"
#include "lpp_interp.h"
#include "lpp_exception.h"

#define HANDLE_NODE(TNode, node) \
        case Ast::NodeKind::TNode :  \
            return visit(node->cptr<Ast::TNode>())

// Semantic analysis
void LppInterp::SemAnalysisVisitor::visit(const Ast::Node *root)
{
    switch (root->getKind()) {
        HANDLE_NODE(SubtypeDef, root);
        HANDLE_NODE(RecordDef, root);
        HANDLE_NODE(VarDecl, root);

        // Statements
        HANDLE_NODE(AssignStmt, root);
        HANDLE_NODE(IfStmt, root);
        HANDLE_NODE(CallStmt, root);
        HANDLE_NODE(CaseStmt, root);
        HANDLE_NODE(WhileStmt, root);
        HANDLE_NODE(RepeatStmt, root);
        HANDLE_NODE(ForStmt, root);
        HANDLE_NODE(ReadStmt, root);
        HANDLE_NODE(WriteStmt, root);
        HANDLE_NODE(OpenFileStmt, root);
        HANDLE_NODE(ReadFileStmt, root);
        HANDLE_NODE(WriteFileStmt, root);
        HANDLE_NODE(CloseFileStmt, root);
        HANDLE_NODE(ReturnStmt, root);
        
        // Expressions
        HANDLE_NODE(LtExpr, root);
        HANDLE_NODE(GtExpr, root);
        HANDLE_NODE(LteExpr, root);
        HANDLE_NODE(GteExpr, root);
        HANDLE_NODE(EqExpr, root);
        HANDLE_NODE(NeqExpr, root);
        HANDLE_NODE(AddExpr, root);
        HANDLE_NODE(SubExpr, root);
        HANDLE_NODE(MultExpr, root);
        HANDLE_NODE(IDivExpr, root);
        HANDLE_NODE(DivExpr, root);
        HANDLE_NODE(ModExpr, root);
        HANDLE_NODE(PowExpr, root);
        HANDLE_NODE(OrExpr, root);
        HANDLE_NODE(AndExpr, root);
        HANDLE_NODE(NotExpr, root);
        HANDLE_NODE(NegExpr, root);
        HANDLE_NODE(PlusExpr, root);
        HANDLE_NODE(FuncCallExpr, root);
        HANDLE_NODE(LhsExpr, root);
        HANDLE_NODE(IndexVar, root);
        HANDLE_NODE(SimpleVar, root);
        HANDLE_NODE(BoolConstExpr, root);
        HANDLE_NODE(StrConstExpr, root);
        HANDLE_NODE(CharConstExpr, root);
        HANDLE_NODE(IntConstExpr, root);
        HANDLE_NODE(RealConstExpr, root);
        
        case Ast::NodeKind::CaseStmtCondRangeValue:
            return visit(root->cptr<Ast::CaseStmt::CondRangeValue>());

        default:
            throw std::runtime_error("Invalid node kind '" + root->kindName() + "' in SemAnalysisVisitor");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::SubtypeDef *sd)
{
    if (udts.contains(sd->getName())) {
        throw LPPException(sd->getSrcLine(), "Ya existe un tipo definido con el nombre '" + sd->getName() + "'");
    }
    TypeInfoSPtr alias_type = visit(sd->getType()->cptr<Ast::Type>());
    if (alias_type->is(TIKind::Alias)) {
        alias_type = alias_type->cptr<AliasTypeInfo>()->aliasType();
    }

    TypeInfoSPtr ati = std::make_shared<AliasTypeInfo>(sd->getName(), alias_type);
    udts.add(sd->getName(), ati);
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::RecordDef *rd)
{
    if (udts.contains(rd->getName())) {
        throw LPPException(rd->getSrcLine(), "Ya existe un tipo definido con el nombre '" + rd->getName() + "'");
    }

    const Ast::NodeList& fldds = rd->getFieldDefs();

    std::vector<RecordTypeInfo::FieldInfo> fldi_v;
    std::unordered_set<std::string> fld_names;

    for (const auto& fd : fldds) {
        const Ast::VarDecl *vd = fd->cptr<Ast::VarDecl>();
        TypeInfoSPtr ti = visit(vd->getType()->cptr<Ast::Type>());

        for (const auto& id : vd->getIdents()) {
            if (fld_names.count(id) != 0) {
                throw LPPException(vd->getSrcLine(), "El campo '" + id + "' duplicado en registro '" + rd->getName() + "'");
            }

            fld_names.insert(id);
            fldi_v.emplace_back(id, ti);
        }
    }

    TypeInfoSPtr rti = std::make_shared<RecordTypeInfo>(rd->getName(), std::move(fldi_v));

    udts.add(rd->getName(), rti);
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::VarDecl *vd)
{
    const Ast::StrList& idents = vd->getIdents();

    TypeInfoSPtr ti = visit(vd->getType()->cptr<Ast::Type>());
    for (const auto& id : idents) {
        if (gbl_vars.contains(id)) {
            throw LPPException(vd->getSrcLine(), "Variable '" + id + "' already declared");
        }

        std::unique_ptr<LppVar> var = std::make_unique<LppVar>(id, ti);

        gbl_vars.add(id, std::move(var));
    }
}

ProcInfo *LppInterp::SemAnalysisVisitor::visit(const Ast::ProcDef *pd)
{
    if (procs.contains(pd->getName())) {
        throw LPPException(pd->getSrcLine(), "El procedimiento '" + pd->getName() + "' ya fue declarado");
    }

    // Procedure parameters
    std::vector<ProcInfo::Param> params;
    std::unordered_set<std::string> prm_names;
    for (const auto& prmn : pd->getParamDefs()) {
        const auto& prmd = prmn->cref<Ast::ParamDef>();

        if (prm_names.count(prmd.getName()) != 0) {
            throw LPPException(pd->getSrcLine(), "La declaracion del parametro '" + prmd.getName() + "'"
                                                 " esta duplicado en el procedimiento '" + pd->getName() + "'");
        }
        TypeInfoSPtr type = visit(prmd.getType()->cptr<Ast::Type>());

        params.emplace_back(prmd.getName(), type, prmd.isByRef());
    }

    // Procedure variables
    std::vector<ProcInfo::Variable> vars;
    std::unordered_set<std::string> var_names;
    for (const auto& varn : pd->getVarDecls()) {
        const auto& vard = varn->cref<Ast::VarDecl>();

        TypeInfoSPtr type = visit(vard.getType()->cptr<Ast::Type>());
        for (const auto& id : vard.getIdents()) {
            if (var_names.count(id) != 0) {
                throw LPPException(pd->getSrcLine(), "La declaracion de la variable '" + id + "'"
                                                     " esta duplicado en el procedimiento '" + pd->getName() + "'");
            }
            vars.emplace_back(id, type);
        }
    }

    TypeInfoSPtr rt(nullptr);
    if (pd->getRetType() != nullptr) {
        rt = visit(pd->getRetType()->cptr<Ast::Type>());
    }

    auto pi = std::make_shared<ProcInfo>(pd->getName(), std::move(params), std::move(vars), rt);
    procs.add(pi->name(), pi);
   
    // Statements
    std::vector<const Ast::Stmt *> stmts;
    for (const auto& s : pd->getStmts()) {
        stmts.push_back(s->cptr<Ast::Stmt>());
    }
    pi->setStatements(std::move(stmts));

    return pi.get();
}

void LppInterp::SemAnalysisVisitor::visitProcStmts(const ProcInfo *pi)
{
    for (const auto& p : pi->params()) {
        local_vars.add(p.name(), std::make_shared<LppVar>(p.name(), p.type()));
    }
    for (const auto& v : pi->variables()) {
        local_vars.add(v.name(), std::make_shared<LppVar>(v.name(), v.type()));
    }
    curr_proc = pi;
    const std::vector<const Ast::Stmt *>& stmts = pi->stmts();
    for (const auto& s : stmts) {
        visit(s->cptr<Ast::Node>());
    }
    local_vars.clear();
    curr_proc = nullptr;
}

TypeInfoSPtr LppInterp::SemAnalysisVisitor::visit(const Ast::Type *tn)
{
    switch (tn->getKind()) {
        HANDLE_NODE(IntType, tn);
        HANDLE_NODE(RealType, tn);
        HANDLE_NODE(BoolType, tn);
        HANDLE_NODE(CharType, tn);
        HANDLE_NODE(StringType, tn);
        HANDLE_NODE(ArrayType, tn);
        HANDLE_NODE(UserType, tn);
        HANDLE_NODE(SeqFileType, tn);
        HANDLE_NODE(BinFileType, tn);
        default:
            throw std::runtime_error("Invalid type node '" + tn->toString() + "'");
    }
}

TypeInfoSPtr LppInterp::SemAnalysisVisitor::visit(const Ast::IntType *tn)
{
    return TypeInfo::Int;
}

TypeInfoSPtr LppInterp::SemAnalysisVisitor::visit(const Ast::RealType *tn)
{
    return TypeInfo::Real;
}

TypeInfoSPtr LppInterp::SemAnalysisVisitor::visit(const Ast::BoolType *tn)
{
    return TypeInfo::Bool;
}

TypeInfoSPtr LppInterp::SemAnalysisVisitor::visit(const Ast::CharType *tn)
{
    return TypeInfo::Char;
}

TypeInfoSPtr LppInterp::SemAnalysisVisitor::visit(const Ast::StringType *tn)
{
    return TypeInfo::String(tn->getSize()? tn->getSize()->getValue() : 0);
}

TypeInfoSPtr LppInterp::SemAnalysisVisitor::visit(const Ast::ArrayType *tn)
{
    return TypeInfo::Array(tn->getDims(), visit(tn->getElemType()->cptr<Ast::Type>()));
}

TypeInfoSPtr LppInterp::SemAnalysisVisitor::visit(const Ast::UserType *tn)
{
    TypeInfoSPtr udt = udts.get(tn->getTypename());
    if (udt == nullptr) {
        throw LPPException(tn->getSrcLine(), "El tipo de datos '" + tn->getTypename() + "' no ha sido declarado");
    }

    return (udt->is(TIKind::Alias))? udt->cptr<AliasTypeInfo>()->aliasType() : udt;
}

TypeInfoSPtr LppInterp::SemAnalysisVisitor::visit(const Ast::SeqFileType *tn)
{
    return TypeInfo::TextFile;
}

TypeInfoSPtr LppInterp::SemAnalysisVisitor::visit(const Ast::BinFileType *tn)
{
    TypeInfoSPtr elem_type = visit(tn->getElemType<Ast::Type>());

    if (!elem_type->isFixedSize()) {
        throw LPPException(tn->getSrcLine(), "Los archivos binarios requieren tipos de datos de tamaño fijo.");
    }

    return TypeInfo::BinaryFile(elem_type);
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::RelExpr *expr)
{
    visit(expr->getExpr1());
    visit(expr->getExpr2());
    const TypeInfo* ti1 = expr->getExpr1<Ast::Expr>()->getTypeInfo();
    const TypeInfo* ti2 = expr->getExpr2<Ast::Expr>()->getTypeInfo();

    if (!ti1->isEquiv(ti2)) {
        throw LPPException(expr->getSrcLine(), "Tipos de datos no compatibles en operacion relacional");
    }
    
    if (!ti1->isPrimType() && !ti1->is(TIKind::String)) {
            throw LPPException(expr->getSrcLine(),
                               "Las operaciones relacionales son validas para valores enteros, reales, caracter, booleano y cadena");
    }

    expr->setTypeInfo(TypeInfo::Bool);
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::AddExpr *expr)
{
    visit(expr->getExpr1());
    visit(expr->getExpr2());
    const TypeInfo* ti1 = expr->getExpr1<Ast::Expr>()->getTypeInfo();
    const TypeInfo* ti2 = expr->getExpr2<Ast::Expr>()->getTypeInfo();

    if (!ti1->isEquiv(ti2)) {
        throw LPPException(expr->getSrcLine(), "Tipos de datos no compatibles en operacion suma");
    }

    if (ti1->is(TIKind::Int) && ti2->is(TIKind::Int)) {
        expr->setTypeInfo(TypeInfo::Int);
    } else if ((ti1->is(TIKind::Int) && ti2->is(TIKind::Real))
                || (ti1->is(TIKind::Real) && ti2->is(TIKind::Int))
                || (ti1->is(TIKind::Real) && ti2->is(TIKind::Real))
                ) {
        expr->setTypeInfo(TypeInfo::Real);
    } else if ((ti1->is(TIKind::String) && ti2->is(TIKind::String))
                || (ti1->is(TIKind::Char) && ti2->is(TIKind::String))
                || (ti1->is(TIKind::String) && ti2->is(TIKind::Char))
                ) {
        expr->setTypeInfo(TypeInfo::String(0));
    } else {
        throw LPPException(expr->getSrcLine(), "La operacion de adicion solo es valida para valores enteros, reales y cadena");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::SubExpr *expr)
{
    visit(expr->getExpr1());
    visit(expr->getExpr2());
    const TypeInfo* ti1 = expr->getExpr1<Ast::Expr>()->getTypeInfo();
    const TypeInfo* ti2 = expr->getExpr2<Ast::Expr>()->getTypeInfo();

    if (!ti1->isEquiv(ti2)) {
        throw LPPException(expr->getSrcLine(), "Tipos de datos no compatibles en operacion suma");
    }

    if (ti1->is(TIKind::Int) && ti2->is(TIKind::Int)) {
        expr->setTypeInfo(TypeInfo::Int);
    } else if ((ti1->is(TIKind::Int) && ti2->is(TIKind::Real))
                || (ti1->is(TIKind::Real) && ti2->is(TIKind::Int))
                || (ti1->is(TIKind::Real) && ti2->is(TIKind::Real))
                ) {
        expr->setTypeInfo(TypeInfo::Real);
    } else {
        throw LPPException(expr->getSrcLine(), "La operacion de adicion solo es valida para valores enteros y reales");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::MultExpr *expr)
{
    visit(expr->getExpr1());
    visit(expr->getExpr2());
    const TypeInfo* ti1 = expr->getExpr1<Ast::Expr>()->getTypeInfo();
    const TypeInfo* ti2 = expr->getExpr2<Ast::Expr>()->getTypeInfo();

    if (!ti1->isEquiv(ti2)) {
        throw LPPException(expr->getSrcLine(), "Tipos de datos no compatibles en operacion suma");
    }

    if (ti1->is(TIKind::Int) && ti2->is(TIKind::Int)) {
        expr->setTypeInfo(TypeInfo::Int);
    } else if ((ti1->is(TIKind::Int) && ti2->is(TIKind::Real))
                || (ti1->is(TIKind::Real) && ti2->is(TIKind::Int))
                || (ti1->is(TIKind::Real) && ti2->is(TIKind::Real))
                ) {
        expr->setTypeInfo(TypeInfo::Real);
    } else {
        throw LPPException(expr->getSrcLine(), "La operacion de multiplicacion solo es valida para valores enteros y reales");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::IDivExpr *expr)
{
    visit(expr->getExpr1());
    visit(expr->getExpr2());
    const TypeInfo* ti1 = expr->getExpr1<Ast::Expr>()->getTypeInfo();
    const TypeInfo* ti2 = expr->getExpr2<Ast::Expr>()->getTypeInfo();

    if (!ti1->isEquiv(ti2)) {
        throw LPPException(expr->getSrcLine(), "Tipos de datos no compatibles en operacion suma");
    }
    if ((ti1->is(TIKind::Int) && ti2->is(TIKind::Int))
        || (ti1->is(TIKind::Int) && ti2->is(TIKind::Real))
        || (ti1->is(TIKind::Real) && ti2->is(TIKind::Int))
        || (ti1->is(TIKind::Real) && ti2->is(TIKind::Real))
        ) {
        expr->setTypeInfo(TypeInfo::Int);
    } else {
        throw LPPException(expr->getSrcLine(), "La operacion de division solo es valida para valores enteros y reales");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::DivExpr *expr)
{
    visit(expr->getExpr1());
    visit(expr->getExpr2());
    const TypeInfo* ti1 = expr->getExpr1<Ast::Expr>()->getTypeInfo();
    const TypeInfo* ti2 = expr->getExpr2<Ast::Expr>()->getTypeInfo();

    if (!ti1->isEquiv(ti2)) {
        throw LPPException(expr->getSrcLine(), "Tipos de datos no compatibles en operacion suma");
    }
    if ((ti1->is(TIKind::Int) && ti2->is(TIKind::Int))
        || (ti1->is(TIKind::Int) && ti2->is(TIKind::Real))
        || (ti1->is(TIKind::Real) && ti2->is(TIKind::Int))
        || (ti1->is(TIKind::Real) && ti2->is(TIKind::Real))
        ) {
        return expr->setTypeInfo(TypeInfo::Real);
    } else {
        throw LPPException(expr->getSrcLine(), "La operacion de division solo es valida para valores enteros y reales");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::ModExpr *expr)
{
    visit(expr->getExpr1());
    visit(expr->getExpr2());
    const TypeInfo* ti1 = expr->getExpr1<Ast::Expr>()->getTypeInfo();
    const TypeInfo* ti2 = expr->getExpr2<Ast::Expr>()->getTypeInfo();

    if (!ti1->isEquiv(ti2)) {
        throw LPPException(expr->getSrcLine(), "Tipos de datos no compatibles en operacion suma");
    }
    if ((ti1->is(TIKind::Int) && ti2->is(TIKind::Int))
        || (ti1->is(TIKind::Int) && ti2->is(TIKind::Real))
        || (ti1->is(TIKind::Real) && ti2->is(TIKind::Int))
        || (ti1->is(TIKind::Real) && ti2->is(TIKind::Real))
        ) {
        expr->setTypeInfo(TypeInfo::Int);
    } else {
        throw LPPException(expr->getSrcLine(), "La operacion cociente solo es valida para valores enteros y reales");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::PowExpr *expr)
{
    visit(expr->getExpr1());
    visit(expr->getExpr2());
    const TypeInfo* ti1 = expr->getExpr1<Ast::Expr>()->getTypeInfo();
    const TypeInfo* ti2 = expr->getExpr2<Ast::Expr>()->getTypeInfo();

    if (!ti1->isEquiv(ti2)) {
        throw LPPException(expr->getSrcLine(), "Tipos de datos no compatibles en operacion suma");
    }

    if (ti1->is(TIKind::Int) && ti2->is(TIKind::Int)) {
        expr->setTypeInfo(TypeInfo::Int);
    } else if ((ti1->is(TIKind::Int) && ti2->is(TIKind::Real))
                || (ti1->is(TIKind::Real) && ti2->is(TIKind::Int))
                || (ti1->is(TIKind::Real) && ti2->is(TIKind::Real))
                ) {
        expr->setTypeInfo(TypeInfo::Real);
    } else {
        throw LPPException(expr->getSrcLine(), "La operacion de potencia solo es valida para valores enteros y reales");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::OrExpr *expr)
{
    visit(expr->getExpr1());
    visit(expr->getExpr2());
    const TypeInfo* ti1 = expr->getExpr1<Ast::Expr>()->getTypeInfo();
    const TypeInfo* ti2 = expr->getExpr2<Ast::Expr>()->getTypeInfo();

    if (!ti1->isEquiv(ti2)) {
        throw LPPException(expr->getSrcLine(), "Tipos de datos no compatibles en operacion suma");
    }

    if (ti1->is(TIKind::Bool) && ti2->is(TIKind::Bool)) {
        expr->setTypeInfo(TypeInfo::Bool);
    } else if (ti1->is(TIKind::Int) && ti2->is(TIKind::Int)) {
        expr->setTypeInfo(TypeInfo::Int);
    } else {
        throw LPPException(expr->getSrcLine(), "La operacion booleana 'o' solo es valida para valores booleanos y enteros");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::AndExpr *expr)
{
    visit(expr->getExpr1());
    visit(expr->getExpr2());
    const TypeInfo* ti1 = expr->getExpr1<Ast::Expr>()->getTypeInfo();
    const TypeInfo* ti2 = expr->getExpr2<Ast::Expr>()->getTypeInfo();

    if (!ti1->isEquiv(ti2)) {
        throw LPPException(expr->getSrcLine(), "Tipos de datos no compatibles en operacion suma");
    }

    if (ti1->is(TIKind::Bool) && ti2->is(TIKind::Bool)) {
        expr->setTypeInfo(TypeInfo::Bool);
    } else if (ti1->is(TIKind::Int) && ti2->is(TIKind::Int)) {
        expr->setTypeInfo(TypeInfo::Int);
    } else {
        throw LPPException(expr->getSrcLine(), "La operacion booleana 'y' solo es valida para valores booleanos y enteros");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::NotExpr *expr)
{
    visit(expr->getExpr());
    const TypeInfo* ti = expr->getExpr<Ast::Expr>()->getTypeInfo();

    if (ti->is(TIKind::Bool)) {
        expr->setTypeInfo(TypeInfo::Bool);
    } else if (ti->is(TIKind::Int)) {
        expr->setTypeInfo(TypeInfo::Int);
    } else {
        throw LPPException(expr->getSrcLine(), "La operacion booleana 'no' solo es valida para valores booleanos y enteros");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::NegExpr *expr)
{
    visit(expr->getExpr());
    const TypeInfo* ti = expr->getExpr<Ast::Expr>()->getTypeInfo();

    if (ti->is(TIKind::Int)) {
        expr->setTypeInfo(TypeInfo::Int);
    } else if (ti->is(TIKind::Real)) {
        expr->setTypeInfo(TypeInfo::Real);
    } else {
        throw LPPException(expr->getSrcLine(), "La operacion unaria de negacion solo es valida para valores numericos");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::PlusExpr *expr)
{
    visit(expr->getExpr());
    const TypeInfo* ti = expr->getExpr<Ast::Expr>()->getTypeInfo();

    if (ti->is(TIKind::Int)) {
        expr->setTypeInfo(TypeInfo::Int);
    } else if (ti->is(TIKind::Real)) {
        expr->setTypeInfo(TypeInfo::Real);
    } else {
        throw LPPException(expr->getSrcLine(), "La operacion unaria de adicion solo es valida para valores numericos");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::FuncCallExpr *expr)
{
    ProcInfoSPtr fi = procs.get(expr->getName());

    if (fi == nullptr) {
        throw LPPException(expr->getSrcLine(), "El subprograma '" + expr->getName() + "' no ha sido declarada");
    }
    if (fi->params().size() != expr->getArgs().getSize()) {
        throw LPPException(expr->getSrcLine(), "Cantidad incorrecta de argumentos en llamada a subprograma '" + expr->getName() + "'. "
                                                "Se esperaban " + std::to_string(fi->params().size()) +
                                                " y se encontraron " + std::to_string(expr->getArgs().getSize()));
    }

    const auto& params = fi->params();
    int index = 0;

    for (const auto& arg : expr->getArgs()) {
        visit(arg.get());
        const Ast::Expr *arg_expr = arg->cptr<Ast::Expr>();
        const TypeInfo* ati = arg_expr->getTypeInfo();

        if (!params[index].type()->isEquiv(ati)) {
            throw LPPException(expr->getSrcLine(), "Tipo de dato no compatible en llamada a subprograma '" + expr->getName() + "'. "
                                                   "Argumento en la posicion " + std::to_string(index + 1));
        }
        if (params[index].isByref() && !arg_expr->isLValue()) {
            throw LPPException(expr->getSrcLine(), "No se pude pasar una expresion a un parametro por referencia. "
                                                   "Subprograma '" + expr->getName() + "'. Argumento en la posicion " + std::to_string(index + 1));
        }
        index++;
    }

    expr->setTypeInfo(fi->retType());
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::LhsExpr *expr)
{
    auto it = expr->getIndexVars().begin();
    const auto& v = *it;

    visit(v.get());
    TypeInfoSPtr lti = v->cptr<Ast::Expr>()->getTypeInfoSPtr();

    it++;
    while (it != expr->getIndexVars().end()) {
        if (!lti->is(TIKind::Record)) {
            throw LPPException(expr->getSrcLine(), "La operacion requiere de un tipo 'registro'");
        }
        const auto& v = *it;

        v->cptr<Ast::VarRef>()->setRecordTypeInfo(lti->cptr<RecordTypeInfo>());
        visit(v.get());
        TypeInfoSPtr rti = v->cptr<Ast::Expr>()->getTypeInfoSPtr();
        
        it ++;
        lti = rti;
    }

    expr->setTypeInfo(lti);
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::IndexVar *expr)
{
    expr->getVarExpr<Ast::VarRef>()->setRecordTypeInfo(expr->getRecordTypeInfo());

    visit(expr->getVarExpr());
    const TypeInfo* ti = expr->getVarExpr<Ast::Expr>()->getTypeInfo();

    if (ti->is(TIKind::Array)) {
        expr->setTypeInfo(ti->cptr<ArrayTypeInfo>()->elemType());
    } else if (ti->is(TIKind::String)) {
        expr->setTypeInfo(TypeInfo::Char);
    } else {
        throw LPPException(expr->getSrcLine(), "Variable con indizacion debe ser de tipo arreglo o cadena");
    }

    for (const auto& eidx : expr->getIndexes()) {
        visit(eidx.get());
        const TypeInfo* eti = eidx->cptr<Ast::Expr>()->getTypeInfo();

        if (!eti->is(TIKind::Int, TIKind::Real)) {
            throw LPPException(expr->getSrcLine(), "La expresion de indice de arreglo debe ser entero o real");
        }
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::SimpleVar *expr)
{
    if (expr->getRecordTypeInfo()) {
        const RecordTypeInfo* rti = expr->getRecordTypeInfo();
        const RecordTypeInfo::FieldInfo* fldi = rti->field(expr->getName());

        if (!fldi) {
            throw LPPException(expr->getSrcLine(), "El campo '" + expr->getName() + "'"
                                                " no es parte del registro '" + rti->name() + "'");
        }
        expr->setTypeInfo(fldi->typeInfo());
    } else {
        LppVarSPtr var = local_vars.get(expr->getName());

        if (!var) {
            var = gbl_vars.get(expr->getName());
        }
        if (!var) {
            throw LPPException(expr->getSrcLine(), "Variable '" + expr->getName() + "' no ha sido declarada");
        }

        expr->setTypeInfo(var->typeInfo());
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::BoolConstExpr *expr)
{
    expr->setTypeInfo(TypeInfo::Bool);
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::StrConstExpr *expr)
{
    expr->setTypeInfo(TypeInfo::String(0));
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::CharConstExpr *expr)
{
    expr->setTypeInfo(TypeInfo::Char);
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::IntConstExpr *expr)
{
    expr->setTypeInfo(TypeInfo::Int);
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::RealConstExpr *expr)
{
    expr->setTypeInfo(TypeInfo::Real);
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::AssignStmt *stmt)
{
    visit(stmt->getLhs());
    visit(stmt->getRhs());

    const TypeInfo* lti = stmt->getLhs<Ast::Expr>()->getTypeInfo();
    const TypeInfo* rti = stmt->getRhs<Ast::Expr>()->getTypeInfo();

    if (lti->is(TypeInfo::Kind::File) || rti->is(TypeInfo::Kind::File)) {
        throw LPPException(stmt->getSrcLine(), "No se pueden asignar variables de tipo archivo");
    }

    if (!lti->isEquiv(rti)) {
        throw LPPException(stmt->getSrcLine(), "Tipos de datos no compatibles en asignacion");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::IfStmt *stmt)
{
    for (const auto& blk : stmt->getCondBlocks()) {
        const auto& cblk = blk->cref<Ast::IfStmt::CondBlock>();

        visit(cblk.getCond());

        const TypeInfo* ti = cblk.getCond<Ast::Expr>()->getTypeInfo();
        if (!ti->is(TIKind::Bool)) {
            throw LPPException(blk->getSrcLine(), "La condicion de la sentencia 'si' debe ser booleana");
        }
        for (const auto& s : cblk.getStmts()) {
            visit(s.get());
        }
    }
    if (stmt->hasElseBlock()) {
        for (const auto& s : stmt->getElseStmts()) {
            visit(s.get());
        }
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::CallStmt *stmt)
{
    const Ast::Expr* func_call = stmt->getFuncCallExpr()->cptr<Ast::Expr>();
    visit(func_call);
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::CaseStmt::CondRangeValue* rangev)
{
    visit(rangev->getValue1());
    visit(rangev->getValue2());
    const TypeInfo* t1 = rangev->getValue1<Ast::Expr>()->getTypeInfo();
    const TypeInfo* t2 = rangev->getValue2<Ast::Expr>()->getTypeInfo();
    
    if (!t1->isEquiv(t2)) {
        throw LPPException(rangev->getSrcLine(), "Tipo de datos no compatible en rango de sentencia 'caso'");   
    }
    rangev->setTypeInfo(rangev->getValue1<Ast::Expr>()->getTypeInfoSPtr());
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::CaseStmt *stmt)
{
    visit(stmt->getVarExpr());

    const TypeInfo* lti = stmt->getVarExpr<Ast::Expr>()->getTypeInfo();
    if (!lti->is(TIKind::Int, TIKind::Real, TIKind::Char)) {
        throw LPPException(stmt->getSrcLine(), "La expression de la sentencia 'caso' debe ser de tipo entero, real o caracter");
    }

    for (const auto& blk : stmt->getCondBlocks()) {
        const auto& cblk = blk->cref<Ast::CaseStmt::CondBlock>();

        for (const auto& cl : cblk.getCondValues()) {
            visit(cl.get());

            const TypeInfo* clti = cl->cptr<Ast::Expr>()->getTypeInfo();            
            if (!lti->isEquiv(clti)) {
                throw LPPException(cl->getSrcLine(), "Tipo de datos no es compatible con la variable de la sentencia 'caso'");
            }
        }

        for (const auto& s : cblk.getStmts()) {
            visit(s.get());
        }
    }
    if (stmt->hasElseBlock()) {
        for (const auto& s : stmt->getElseStmts()) {
            visit(s.get());
        }
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::WhileStmt *stmt)
{
    visit(stmt->getCond());

    const TypeInfo* ti = stmt->getCond<Ast::Expr>()->getTypeInfo();
    if (!ti->is(TIKind::Bool)) {
        throw LPPException(stmt->getSrcLine(), "La expresion del ciclo 'mientras' debe ser booleana");
    }
    for (const auto& ss : stmt->getStmts()) {
        visit(ss.get());
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::RepeatStmt *stmt)
{
    visit(stmt->getCond());

    const TypeInfo* ti = stmt->getCond<Ast::Expr>()->getTypeInfo();
    if (!ti->is(TIKind::Bool)) {
        throw LPPException(stmt->getSrcLine(), "La expresion del ciclo 'repita' debe ser booleana");
    }
    for (const auto& ss : stmt->getStmts()) {
        visit(ss.get());
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::ForStmt *stmt)
{
    visit(stmt->getVar());
    visit(stmt->getExpr1());

    const TypeInfo* lti = stmt->getVar<Ast::Expr>()->getTypeInfo();
    const TypeInfo* ti1 = stmt->getExpr1<Ast::Expr>()->getTypeInfo();

    if (!stmt->getVar()->cptr<Ast::Expr>()->isLValue()) {
        throw LPPException(stmt->getSrcLine(), "La variable del ciclo para debe ser asignable");
    }
    if (!lti->isEquiv(ti1)) {
        throw LPPException(stmt->getSrcLine(), "Tipos de datos no compatibles en la primera expresion del ciclo 'para'");
    }

    if (!lti->is(TIKind::Int)) {
        throw LPPException(stmt->getSrcLine(), "La variable del ciclo deber ser de tipo entero");
    }

    visit(stmt->getExpr2());

    const TypeInfo* ti2 = stmt->getExpr1<Ast::Expr>()->getTypeInfo();
    if (!lti->isEquiv(ti2)) {
        throw LPPException(stmt->getSrcLine(), "Tipos de datos no compatibles en la segunda expresion del ciclo 'para'");
    }
    
    for (const auto& s : stmt->getStmts()) {
        visit(s.get());
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::ReadStmt *stmt)
{
    for (const auto& lexpr : stmt->getLValueList()) {
        visit(lexpr.get());

        const TypeInfo* ti = lexpr->cptr<Ast::EqExpr>()->getTypeInfo();
        if (!ti->is(TIKind::Int, TIKind::Real, TIKind::Char, TIKind::Bool, TIKind::String)) {
            throw LPPException(stmt->getSrcLine(), "No se pueden leer variable de este tipo");
        }
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::WriteStmt *stmt)
{
    for (const auto& expr : stmt->getExprList()) {
        visit(expr.get());

        const TypeInfo* ti = expr->cptr<Ast::EqExpr>()->getTypeInfo();
        if (!ti->is(TIKind::Int, TIKind::Real, TIKind::Char, TIKind::Bool, TIKind::String)) {
            throw LPPException(stmt->getSrcLine(), "No se puede escribir variables de tipo " + ti->kindName());
        }
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::OpenFileStmt *stmt)
{
    visit(stmt->getFileNameExpr());
    const TypeInfo* fnti = stmt->getFileNameExpr<Ast::Expr>()->getTypeInfo();

    if (!fnti->is(TIKind::String)) {
        throw LPPException(stmt->getSrcLine(), "La expresion para el nombre del archivo debe ser de tipo cadena");
    }

    visit(stmt->getFileHandleVar());
    const TypeInfo* vti = stmt->getFileHandleVar<Ast::Expr>()->getTypeInfo();

    if (vti->is(TIKind::File)) {
        const auto* fti = vti->cptr<FileTypeInfo>();
        if (fti->isText()) {
            stmt->setFileType(Ast::FileStmt::FileType::Text);
        } else {
            stmt->setFileType(Ast::FileStmt::FileType::Binary);
        }
    } else {
        throw LPPException(stmt->getSrcLine(), "La sentencia 'abrir archivo' necesita una variable de tipo archivo");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::ReadFileStmt *stmt)
{
    auto visit_fhvar = [stmt, this](const Ast::NodeUPtr& n_fhvar) {
        visit(n_fhvar.get());
        const TypeInfo* vti = n_fhvar->cptr<Ast::Expr>()->getTypeInfo();

        if (vti->is(TIKind::File)) {
            const auto* fti = vti->cptr<FileTypeInfo>();
            if (fti->isText()) {
                stmt->setFileType(Ast::FileStmt::FileType::Text);
            } else {
                stmt->setFileType(Ast::FileStmt::FileType::Binary);
            }
        } else {
            throw LPPException(stmt->getSrcLine(), "La sentencia 'leer' necesita una variable de tipo archivo");
        }
    };

    bool first = true;
    for (auto& n_var : stmt->getLValueList()) {
        if (first) {
            first = false;
            visit_fhvar(n_var);
        } else {
            visit(n_var.get());
            const TypeInfo* ti = n_var->cptr<Ast::Expr>()->getTypeInfo();

            if (!ti->isPrimType() && !ti->is(TIKind::String, TIKind::Array, TIKind::Record)) {
                throw LPPException(stmt->getSrcLine(), "No se puede leer variable de tipo '" + ti->kindName() + "'");
            }
        }
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::WriteFileStmt *stmt)
{ 
    auto visit_fhvar = [stmt, this](const Ast::NodeUPtr& n_fhvar) {
        visit(n_fhvar.get());
        const TypeInfo* vti = n_fhvar->cptr<Ast::Expr>()->getTypeInfo();

        if (vti->is(TIKind::File)) {
            const auto* fti = vti->cptr<FileTypeInfo>();
            if (fti->isText()) {
                stmt->setFileType(Ast::FileStmt::FileType::Text);
            } else {
                stmt->setFileType(Ast::FileStmt::FileType::Binary);
            }
        } else {
            throw LPPException(stmt->getSrcLine(), "La sentencia 'escribir' necesita una variable de tipo archivo");
        }
    };

    bool first = true;
    for (auto& n_var : stmt->getExprList()) {
        if (first) {
            first = false;
            visit_fhvar(n_var);
        } else {
            visit(n_var.get());
            const TypeInfo* ti = n_var->cptr<Ast::Expr>()->getTypeInfo();

            if (!ti->isPrimType() && !ti->is(TIKind::String, TIKind::Array, TIKind::Record)) {
                throw LPPException(stmt->getSrcLine(), "No se puede escribir variable de tipo '" + ti->kindName() + "'");
            }
        }
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::CloseFileStmt *stmt)
{
    visit(stmt->getVarExpr());
    const TypeInfo* vti = stmt->getVarExpr<Ast::Expr>()->getTypeInfo();

    if (vti->is(TIKind::File)) {
        const auto* fti = vti->cptr<FileTypeInfo>();
        if (fti->isText()) {
            stmt->setFileType(Ast::FileStmt::FileType::Text);
        } else {
            stmt->setFileType(Ast::FileStmt::FileType::Binary);
        }
    } else {
        throw LPPException(stmt->getSrcLine(), "La sentencia 'cerrar' necesita una variable de tipo archivo");
    }
}

void LppInterp::SemAnalysisVisitor::visit(const Ast::ReturnStmt *stmt)
{
    if (!curr_proc) {
        throw LPPException(stmt->getSrcLine(), "La sentencia 'retorne' solo puede aparecer dentro de una funcion o procedimiento");
    }

    if (stmt->getExpr() != nullptr) {
        if (curr_proc->retType() == nullptr) {
            throw LPPException(stmt->getSrcLine(), "Un procedimiento no puede retornar una valor");
        }
        visit(stmt->getExpr());

        const TypeInfo* rtti = stmt->getExpr<Ast::Expr>()->getTypeInfo();
        if (!rtti->isEquiv(curr_proc->retType().get())) {
            throw LPPException(stmt->getSrcLine(), "El tipo de datos de la expresion de retorno no es compatible con el tipo de la funcion");
        }
    } else {
        if (curr_proc->retType() != nullptr) {
            throw LPPException(stmt->getSrcLine(), "Una funcion debe retornar una valor");
        }
    }
}
