#ifndef LPP_SEMANTICS_H
#define LPP_SEMANTICS_H

#include "lpp_ast.h"
#include "lpp_symb_table.h"
#include "lpp_type_info.h"
#include "lpp_proc_info.h"
#include "lpp_variant.h"

class LppSemantics
{
public:
    LppSemantics(SymbolTable<LppVar>& vars, SymbolTable<TypeInfo>& udts, SymbolTable<ProcInfo>& procs);
    
    void analyze(const Ast::Node* root);
    void analyzeProcStmts(const ProcInfo* pi);

private:
    class SemAnalysisVisitor; // Forward declaration

    SymbolTable<LppVar>& vars;
    SymbolTable<TypeInfo>& udts;
    SymbolTable<ProcInfo>& procs;
};

#endif // LPP_SEMANTICS_H
