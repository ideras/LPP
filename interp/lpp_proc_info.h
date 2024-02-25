#ifndef PROCINFO_H
#define PROCINFO_H

#include <string>
#include <vector>
#include <memory>
#include "lpp_type_info.h"
#include "lpp_symb_table.h"
#include "lpp_ast.h"

class ProcInfo;
class ProcFrame;
using ProcInfoSPtr = std::shared_ptr<ProcInfo>;
using ProcFrameUPtr = std::unique_ptr<ProcFrame>;

class ProcFrame
{
    friend class ProcInfo;

public:
    ProcFrame(const TypeInfoSPtr& ret_type)
        : ret_type(ret_type)
    {}

    LppVarSPtr getVar(const std::string& name)
    { return _vars.get(name); }

    TypeInfoSPtr retType() const
    { return ret_type; }

    void addVar(const std::string& name, const TypeInfoSPtr& type);
    void addVar(const std::string &name, const TypeInfoSPtr &type, const LppVariant &val);

private:
    SymbolTable<LppVar> _vars;
    TypeInfoSPtr ret_type;
};

class ProcInfo
{
public:
    class Variable
    {
    public:
        Variable(const std::string& _name, const TypeInfoSPtr& _type)
            : _name(_name), _type(_type)
        {}

        std::string name() const
        { return _name; }

        TypeInfoSPtr type() const
        { return _type; }

    private:
        const std::string _name;
        TypeInfoSPtr _type;
    };

    class Param: public Variable
    {
    public:
        Param(const std::string& _name, const TypeInfoSPtr& _type, bool is_byref = false)
            : Variable(_name, _type), is_byref(is_byref)
        {}

        bool isByref() const
        { return is_byref; }

    private:
        bool is_byref;
    };

    ProcInfo(const std::string& _name, std::vector<Param>&& _params, TypeInfoSPtr ret_type)
        : _name(_name), _params(std::move(_params)), _vars(),
          ret_type(ret_type), _stmts(), is_builtin(true)
    {}

    ProcInfo(const std::string& _name, std::vector<Param>&& _params,
             std::vector<Variable>&& _vars, TypeInfoSPtr ret_type)
        : _name(_name), _params(std::move(_params)),
          _vars(std::move(_vars)), ret_type(ret_type),
          _stmts(), is_builtin(false)
    {}

    std::string name() const
    { return _name; }

    const std::vector<Param>& params() const
    { return _params; }

    const std::vector<Variable> variables() const
    { return _vars; }

    TypeInfoSPtr retType() const
    { return ret_type; }

    void setStatements(std::vector<const Ast::Stmt *> a_stmts)
    { _stmts = std::move(a_stmts); }

    const std::vector<const Ast::Stmt *>& stmts() const
    { return _stmts; }

    bool isBuiltin() const
    { return is_builtin; }

    ProcFrameUPtr makeProcFrame(const std::vector<LppVariant> &arg_vals);

    static ProcInfoSPtr create(const std::string& name, const std::initializer_list<Param>& params, const TypeInfoSPtr& rt_type);

private:
    std::string _name;
    std::vector<Param> _params;
    std::vector<Variable> _vars;
    TypeInfoSPtr ret_type;
    std::vector<const Ast::Stmt *> _stmts;
    bool is_builtin;
};

#endif // PROCINFO_H
