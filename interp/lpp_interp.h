#ifndef LPPINTERP_H
#define LPPINTERP_H

#include <string>
#include <cctype>
#include <algorithm>
#include <unordered_map>
#include <tuple>
#include <memory>
#include "lpp_ast.h"
#include "lpp_proc_info.h"
#include "lpp_variant.h"
#include "lpp_type_info.h"
#include "lpp_symb_table.h"
#include "lpp_runtime.h"
#include "lpp_filemanager.h"
#include "lpp_terminal.h"

class LppInterp
{
public:
    LppInterp()
      : var_map(), udt_map(), proc_map(), term(nullptr)
    {}

    void exec(const Ast::Node* prg_node);
    void semAnalysis(const Ast::Node* prg_node);

private:
    class SemAnalysisVisitor
    {
        friend class LppInterp;
        using TIKind = TypeInfo::Kind;
    
    public:
        SemAnalysisVisitor(SymbolTable<LppVar>& vars, SymbolTable<TypeInfo>& udts,
                   SymbolTable<ProcInfo>& procs)
            : gbl_vars(vars), udts(udts), procs(procs)
        {}

        void visit(const Ast::Node *root);

    private:
        // Ast declaration visitor       
        void visit(const Ast::SubtypeDef *sd);
        void visit(const Ast::RecordDef *rd);
        void visit(const Ast::VarDecl *vd);
        ProcInfo *visit(const Ast::ProcDef *pd);
        void visitProcStmts(const ProcInfo *pi);

        // Ast Type visitor
        TypeInfoSPtr visit(const Ast::Type *tn);
        TypeInfoSPtr visit(const Ast::IntType *tn);
        TypeInfoSPtr visit(const Ast::RealType *tn);
        TypeInfoSPtr visit(const Ast::BoolType *tn);
        TypeInfoSPtr visit(const Ast::CharType *tn);
        TypeInfoSPtr visit(const Ast::StringType *tn);
        TypeInfoSPtr visit(const Ast::ArrayType *tn);
        TypeInfoSPtr visit(const Ast::UserType *tn);
        TypeInfoSPtr visit(const Ast::SeqFileType *tn);
        TypeInfoSPtr visit(const Ast::BinFileType *tn);

        // Ast Expression visitor
        void visit(const Ast::RelExpr *expr);
        void visit(const Ast::AddExpr *expr);
        void visit(const Ast::SubExpr *expr);
        void visit(const Ast::MultExpr *expr);
        void visit(const Ast::IDivExpr *expr);
        void visit(const Ast::DivExpr *expr);
        void visit(const Ast::ModExpr *expr);
        void visit(const Ast::PowExpr *expr);
        void visit(const Ast::OrExpr *expr);
        void visit(const Ast::AndExpr *expr);
        void visit(const Ast::NotExpr *expr);
        void visit(const Ast::NegExpr *expr);
        void visit(const Ast::PlusExpr *expr);
        void visit(const Ast::FuncCallExpr *expr);
        void visit(const Ast::LhsExpr *expr);
        void visit(const Ast::IndexVar *expr);
        void visit(const Ast::SimpleVar *expr);
        void visit(const Ast::BoolConstExpr *expr);
        void visit(const Ast::StrConstExpr *expr);
        void visit(const Ast::CharConstExpr *expr);
        void visit(const Ast::IntConstExpr *expr);
        void visit(const Ast::RealConstExpr *expr);
        void visit(const Ast::CaseStmt::CondRangeValue* rangev);

        // Ast Statement visitor
        void visit(const Ast::AssignStmt *stmt);
        void visit(const Ast::IfStmt *stmt);
        void visit(const Ast::CallStmt *stmt);
        void visit(const Ast::CaseStmt *stmt);
        void visit(const Ast::WhileStmt *stmt);
        void visit(const Ast::RepeatStmt *stmt);
        void visit(const Ast::ForStmt *stmt);
        void visit(const Ast::ReadStmt *stmt);
        void visit(const Ast::WriteStmt *stmt);
        void visit(const Ast::OpenFileStmt *stmt);
        void visit(const Ast::ReadFileStmt *stmt);
        void visit(const Ast::WriteFileStmt *stmt);
        void visit(const Ast::CloseFileStmt *stmt);
        void visit(const Ast::ReturnStmt *stmt);

    private:
        SymbolTable<LppVar> local_vars;
        SymbolTable<LppVar>& gbl_vars;
        SymbolTable<TypeInfo>& udts;
        SymbolTable<ProcInfo>& procs;
        const ProcInfo *curr_proc;
    };

    class AstVisitor
    {
    public:
        using CaseLiteral = std::pair<LppVariant, LppVariant>;

        AstVisitor(SymbolTable<LppVar>& vars, SymbolTable<TypeInfo>& udts,
                   SymbolTable<ProcInfo>& procs, Terminal& term)
            : vars(vars), udts(udts), procs(procs), term(term), lpp_rt(term, file_manager)
        {}

        LppVariant visit(const Ast::Node *root);

    private:
        LppVariant getCaseValue(const Ast::Expr *vexpr);
        std::vector<CaseLiteral> getCaseLiterals(const Ast::NodeList& literal_list);
        
        // Ast Expression visitor
        std::tuple<LppVariant, LppVariant> visit(const Ast::BinaryExpr *expr);
        LppVariant visit(const Ast::VarRef *expr, LppVariant& parent_val);
        LppVariant visit(const Ast::RelExpr *expr);
        LppVariant visit(const Ast::AddExpr *expr);
        LppVariant visit(const Ast::SubExpr *expr);
        LppVariant visit(const Ast::MultExpr *expr);
        LppVariant visit(const Ast::IDivExpr *expr);
        LppVariant visit(const Ast::DivExpr *expr);
        LppVariant visit(const Ast::ModExpr *expr);
        LppVariant visit(const Ast::PowExpr *expr);
        LppVariant visit(const Ast::OrExpr *expr);
        LppVariant visit(const Ast::AndExpr *expr);
        LppVariant visit(const Ast::NotExpr *expr);
        LppVariant visit(const Ast::NegExpr *expr);
        LppVariant visit(const Ast::PlusExpr *expr);
        LppVariant visit(const Ast::FuncCallExpr *expr);
        LppVariant visit(const Ast::LhsExpr *expr);
        LppVariant visit(const Ast::IndexVar *expr, LppVariant& parent_val);
        LppVariant visit(const Ast::SimpleVar *expr, LppVariant& parent_val);
        LppVariant visit(const Ast::BoolConstExpr *expr);
        LppVariant visit(const Ast::StrConstExpr *expr);
        LppVariant visit(const Ast::CharConstExpr *expr);
        LppVariant visit(const Ast::IntConstExpr *expr);
        LppVariant visit(const Ast::RealConstExpr *expr);

        // Ast Statement visitor
        void visit(const Ast::AssignStmt *stmt);
        void visit(const Ast::IfStmt *stmt);
        void visit(const Ast::CallStmt *stmt);
        void visit(const Ast::CaseStmt *stmt);
        void visit(const Ast::WhileStmt *stmt);
        void visit(const Ast::RepeatStmt *stmt);
        void visit(const Ast::ForStmt *stmt);
        void visit(const Ast::ReadStmt *stmt);
        void visit(const Ast::WriteStmt *stmt);
        void visit(const Ast::OpenFileStmt *stmt);
        void visit(const Ast::ReadFileStmt *stmt);
        void visit(const Ast::WriteFileStmt *stmt);
        void visit(const Ast::CloseFileStmt *stmt);
        void visit(const Ast::ReturnStmt *stmt);

    private:
        SymbolTable<LppVar>& vars;
        SymbolTable<TypeInfo>& udts;
        SymbolTable<ProcInfo>& procs;
        std::vector<ProcFrameUPtr> call_stack;
        LppRuntime lpp_rt;
        LppFileManager file_manager;
        Terminal& term;
    };

private:
    void loadBuiltinProcs();

private:
    SymbolTable<TypeInfo> udt_map;
    SymbolTable<LppVar> var_map;
    SymbolTable<ProcInfo> proc_map;
    std::unique_ptr<Terminal> term;
};

#endif // LPPINTERP_H
