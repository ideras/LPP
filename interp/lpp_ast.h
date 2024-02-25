#ifndef AST_H
#define AST_H

#include <vector>
#include <string>
#include <memory>
#include "lpp_variant.h"

namespace Ast
{

enum class NodeKind {
    Node,
    NodeList,
    StrList,
    Program,
    SubtypeDef,
    RecordDef,
    VarDecl,
    Type,
    IntType,
    RealType,
    BoolType,
    CharType,
    StringType,
    StringTypeSize,
    ArrayType,
    UserType,
    SeqFileType,
    BinFileType,
    Collection,
    ProcDef,
    ParamDef,
    Expr,
    BinaryExpr,
    RelExpr,
    LtExpr,
    GtExpr,
    EqExpr,
    NeqExpr,
    LteExpr,
    GteExpr,
    AddExpr,
    SubExpr,
    MultExpr,
    IDivExpr,
    DivExpr,
    ModExpr,
    PowExpr,
    OrExpr,
    AndExpr,
    NotExpr,
    NegExpr,
    PlusExpr,
    FuncCallExpr,
    LhsExpr,
    VarRef,
    SimpleVar,
    IndexVar,
    BoolConstExpr,
    StrConstExpr,
    CharConstExpr,
    IntConstExpr,
    RealConstExpr,
    Stmt,
    AssignStmt,
    CallStmt,
    IfStmt,
    IfStmtCondBlock,
    CaseStmt,
    CaseStmtCondBlock,
    CaseStmtCondRangeValue,
    WhileStmt,
    RepeatStmt,
    ForStmt,
    ReadStmt,
    WriteStmt,
    OpenFileStmt,
    ReadFileStmt,
    WriteFileStmt,
    CloseFileStmt,
    ReturnStmt,
};

class Node;

using NodeUPtr = std::unique_ptr<Node>;

class Node
{
public:
    Node(): src_line(0)
    {}

    virtual ~Node()
    {}

    void setSrcLine(int _src_line)
    { src_line = _src_line; }

    int getSrcLine() const
    { return src_line; }

    virtual std::string toString() const
    { return kindName(); }

    virtual NodeKind getKind() const
    { return NodeKind::Node; }

    std::string kindName() const;

    template<typename T>
    const T& cref() const
    { return *(reinterpret_cast<const T *>(this)); }

    template<typename T>
    T& ref()
    { return *(reinterpret_cast<T *>(this)); }

    template<typename T>
    const T* cptr() const
    { return reinterpret_cast<const T *>(this); }

    template<typename T>
    T* ptr()
    { return reinterpret_cast<T *>(this); }

private:
    int src_line;
};

template <NodeKind ckind, typename T>
class List: public Node
{
public:
    using Items = std::vector<T>;
    using iterator = typename Items::iterator;
    using const_iterator = typename Items::const_iterator;

    List(): _items()
    {}

    List(Items&& nodes)
        : _items(std::move(nodes))
    {}

    Items& items()
    { return _items; }

    const Items& items() const
    { return _items; }

    size_t getSize() const
    { return _items.size(); }

    bool isEmpty() const
    { return _items.empty(); }

    NodeKind getKind() const override
    { return ckind; }

    iterator begin()
    { return _items.begin(); }

    const_iterator begin() const
    { return _items.cbegin(); }

    iterator end()
    { return _items.end(); }

    const_iterator end() const
    { return _items.end(); }

private:
    Items _items;
};

using NodeList = List<NodeKind::NodeList, NodeUPtr>;
using StrList = List<NodeKind::StrList, std::string>;

class Program: public Node
{
public:
    Program(NodeUPtr&& type_defs, NodeUPtr&& var_decls, NodeUPtr&& proc_decls, NodeUPtr&& stmts)
      : type_defs(std::move(type_defs)),
        var_decls(std::move(var_decls)),
        proc_decls(std::move(proc_decls)),
        stmts(std::move(stmts))
    {}

    NodeKind getKind() const override
    { return NodeKind::Program; }

    const NodeList& getTypeDefs() const
    { return type_defs->cref<NodeList>(); }

    const NodeList& getVarDecls() const
    { return var_decls->cref<NodeList>(); }

    const NodeList& getProcDecls() const
    { return proc_decls->cref<NodeList>(); }

    const NodeList& getStmts() const
    { return stmts->cref<NodeList>(); }

private:
    NodeUPtr type_defs;
    NodeUPtr var_decls;
    NodeUPtr proc_decls;
    NodeUPtr stmts;
};

class SubtypeDef: public Node
{
public:
    SubtypeDef(const std::string& name, NodeUPtr&& type)
        : name(name), type(std::move(type))
    {}

    const Node* getType() const
    { return type.get(); }

    std::string getName() const
    { return name; }

    NodeKind getKind() const override
    { return NodeKind::SubtypeDef; }

private:
    std::string name;
    NodeUPtr type;
};

class RecordDef: public Node
{
public:
    RecordDef(const std::string& name, NodeUPtr&& field_defs)
        : name(name),
        field_defs(std::move(field_defs))
    {}

    std::string getName() const
    { return name; }

    const NodeList& getFieldDefs() const
    { return field_defs->cref<NodeList>(); }

    NodeKind getKind() const override
    { return NodeKind::RecordDef; }

private:
    std::string name;
    NodeUPtr field_defs;
};

class Type: public Node
{
public:
    NodeKind getKind() const override
    { return NodeKind::Type; }

protected:
    Type()
    {}
};

template<NodeKind k>
class PrimType: public Type
{
public:
    PrimType()
    {}

    NodeKind getKind() const override
    { return k; }
};

using IntType = PrimType<NodeKind::IntType>;
using RealType = PrimType<NodeKind::RealType>;
using BoolType = PrimType<NodeKind::BoolType>;
using CharType = PrimType<NodeKind::CharType>;

class StringType: public Type
{
public:
    class Size: public Node
    {
    public:
        Size(int value): value(value)
        {}

        NodeKind getKind() const override
        { return NodeKind::StringTypeSize; }

        int getValue() const
        { return value; }

    private:
        int value;
    };

    StringType(): size_n(nullptr)
    {}

    StringType(int size): size_n(new Size(size))
    {}

    StringType(NodeUPtr&& size_n)
        : size_n(std::move(size_n))
    {}

    NodeKind getKind() const override
    { return NodeKind::StringType; }

    const Size* getSize() const
    { return size_n->cptr<Size>(); }

private:
    NodeUPtr size_n;
};

class ArrayType: public Type
{
public:
    ArrayType(std::vector<int>&& dims, NodeUPtr&& elem_type)
        : dims(std::move(dims)),
        elem_type(std::move(elem_type))
    {}

    NodeKind getKind() const override
    { return NodeKind::ArrayType; }

    const std::vector<int>& getDims() const
    { return dims; }

    const Node* getElemType() const
    { return elem_type.get(); }

private:
    std::vector<int> dims;
    NodeUPtr elem_type;
};

class SeqFileType: public Type
{
public:
    SeqFileType()
    {}

    NodeKind getKind() const override
    { return NodeKind::SeqFileType; }
};

class BinFileType: public Type
{
public:
    BinFileType(NodeUPtr type)
        : type(std::move(type))
    {}

    NodeKind getKind() const override
    { return NodeKind::BinFileType; }

    const Node* getType() const
    { return type.get(); }

    template <typename T>
    const T* getElemType() const
    { return type->cptr<T>(); }

private:
    NodeUPtr type;
};

class UserType: public Type
{
public:
    UserType(const std::string& type_name)
        : type_name(type_name)
    {}

    NodeKind getKind() const override
    { return NodeKind::UserType; }

    std::string getTypename() const
    { return type_name; }

private:
    std::string type_name;
};

class VarDecl: public Node
{
public:
    VarDecl(NodeUPtr&& type, NodeUPtr&& idents)
        : type(std::move(type)),
        idents(std::move(idents))
    {}

    const Node* getType() const
    { return type.get(); }

    const StrList& getIdents() const
    { return idents->cref<StrList>(); }

    NodeKind getKind() const override
    { return NodeKind::VarDecl; }

private:
    NodeUPtr type;
    NodeUPtr idents;
};

class ProcDef: public Node
{
public:
    ProcDef(const std::string& name, NodeUPtr&& param_defs, NodeUPtr&& ret_type,
            NodeUPtr&& var_decls, NodeUPtr&& stmts)
      : name(name),
        param_defs(std::move(param_defs)),
        ret_type(std::move(ret_type)),
        var_decls(std::move(var_decls)),
        stmts(std::move(stmts))
    {}

    NodeKind getKind() const override
    { return NodeKind::ProcDef; }

    std::string getName() const
    { return name; }

    const NodeList& getParamDefs() const
    { return param_defs->cref<NodeList>(); }

    const Node* getRetType() const
    { return ret_type.get(); }

    const NodeList& getVarDecls() const
    { return var_decls->cref<NodeList>(); }

    const NodeList& getStmts() const
    { return stmts->cref<NodeList>(); }

private:
    std::string name;
    NodeUPtr ret_type;
    NodeUPtr param_defs;
    NodeUPtr var_decls;
    NodeUPtr stmts;
};

class ParamDef: public Node
{
public:
    ParamDef(bool is_byref, NodeUPtr&& type, const std::string& name)
        : is_byref(is_byref), type(std::move(type)), name(std::move(name))
    {}

    NodeKind getKind() const override
    { return NodeKind::ParamDef; }

    bool isByRef() const
    { return is_byref; }

    const Node* getType() const
    { return type.get(); }

    std::string getName() const
    { return name; }

private:
    bool is_byref;
    NodeUPtr type;
    std::string name;
};

class Expr: public Node
{
public:

    NodeKind getKind() const override
    { return NodeKind::Expr; }

    virtual bool isLValue() const
    { return false; }

    void setTypeInfo(const TypeInfoSPtr& _ti) const
    { type_info = _ti; }

    const TypeInfo* getTypeInfo() const
    { return type_info.get(); }

    const TypeInfoSPtr& getTypeInfoSPtr() const
    { return type_info; }

protected:
    Expr(): type_info(nullptr)
    {}

    mutable TypeInfoSPtr type_info;
};

class BinaryExpr: public Expr
{
public:
    BinaryExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : expr1(std::move(expr1)), expr2(std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::BinaryExpr; }

    const Node *getExpr1() const
    { return expr1.get(); }

    const Node *getExpr2() const
    { return expr2.get(); }  

    template <typename T>
    const T *getExpr1() const
    { return expr1->cptr<T>(); }

    template <typename T>
    const T *getExpr2() const
    { return expr2->cptr<T>(); }    

private:
    NodeUPtr expr1;
    NodeUPtr expr2;
};

class RelExpr: public BinaryExpr
{
public:
    RelExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : BinaryExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::RelExpr; }
};

class LtExpr: public RelExpr
{
public:
    LtExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : RelExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::LtExpr; }
};

class GtExpr: public RelExpr
{
public:
    GtExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : RelExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::GtExpr; }
};

class LteExpr: public RelExpr
{
public:
    LteExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : RelExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::LteExpr; }
};

class GteExpr: public RelExpr
{
public:
    GteExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : RelExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::GteExpr; }
};

class EqExpr: public RelExpr
{
public:
    EqExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : RelExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::EqExpr; }
};

class NeqExpr: public RelExpr
{
public:
    NeqExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : RelExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::NeqExpr; }
};

class AddExpr: public BinaryExpr
{
public:
    AddExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : BinaryExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::AddExpr; }
};

class SubExpr: public BinaryExpr
{
public:
    SubExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : BinaryExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::SubExpr; }
};

class MultExpr: public BinaryExpr
{
public:
    MultExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : BinaryExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::MultExpr; }
};

class IDivExpr: public BinaryExpr
{
public:
    IDivExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : BinaryExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::IDivExpr; }
};

class DivExpr: public BinaryExpr
{
public:
    DivExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : BinaryExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::DivExpr; }
};

class ModExpr: public BinaryExpr
{
public:
    ModExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : BinaryExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::ModExpr; }
};

class PowExpr: public BinaryExpr
{
public:
    PowExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : BinaryExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::PowExpr; }
};

class OrExpr: public BinaryExpr
{
public:
    OrExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : BinaryExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::OrExpr; }
};

class AndExpr: public BinaryExpr
{
public:
    AndExpr(NodeUPtr&& expr1, NodeUPtr&& expr2)
        : BinaryExpr(std::move(expr1), std::move(expr2))
    {}

    NodeKind getKind() const override
    { return NodeKind::AndExpr; }
};

template<NodeKind ekind>
class UnaryExpr: public Expr
{
public:
    UnaryExpr(NodeUPtr&& expr): expr(std::move(expr))
    {}

    NodeKind getKind() const override
    { return ekind; }

    template <typename T>
    const T* getExpr() const
    { return expr->cptr<T>(); }

    const Node* getExpr() const
    { return expr.get(); }

private:
    NodeUPtr expr;
};

using NegExpr = UnaryExpr<NodeKind::NegExpr>;
using PlusExpr = UnaryExpr<NodeKind::PlusExpr>;
using NotExpr = UnaryExpr<NodeKind::NotExpr>;

class FuncCallExpr: public Expr
{
public:
    FuncCallExpr(const std::string& name, NodeUPtr&& args)
        : name(name), args(std::move(args))
    {}

    NodeKind getKind() const override
    { return NodeKind::FuncCallExpr; }

    std::string getName() const
    { return name; }

    const NodeList& getArgs() const
    { return args->cref<NodeList>(); }

private:
    std::string name;
    NodeUPtr args;
};

class VarRef: public Expr
{
public:
    VarRef(): rec_ti(nullptr)
    {}

    NodeKind getKind() const override
    { return NodeKind::VarRef; }

    bool isLValue() const override
    { return true; }

    void setRecordTypeInfo(const RecordTypeInfo* _rec_ti) const
    { rec_ti = _rec_ti; }

    const RecordTypeInfo *getRecordTypeInfo() const
    { return rec_ti; }

    const LppVariant& getParentValue() const
    { return parent_value; }

    void setParentValue(const LppVariant& _val) const
    { parent_value = _val; }

private:
    mutable const RecordTypeInfo *rec_ti;
    mutable LppVariant parent_value;
};

class LhsExpr: public VarRef
{
public:
    LhsExpr(NodeUPtr&& index_vars)
        : index_vars(std::move(index_vars))
    {}

    NodeKind getKind() const override
    { return NodeKind::LhsExpr; }

    const NodeList& getIndexVars() const
    { return index_vars->cref<NodeList>(); }

private:
    NodeUPtr index_vars;
};

class SimpleVar: public VarRef
{
public:
    SimpleVar(const std::string& name): name(name)
    {}

    NodeKind getKind() const override
    { return NodeKind::SimpleVar; }

    std::string getName() const
    { return name; }

private:
    std::string name;
};

class IndexVar: public VarRef
{
public:
    IndexVar(NodeUPtr&& var_expr, NodeUPtr&& indexes)
        : var_expr(std::move(var_expr)), indexes(std::move(indexes))
    {}

    NodeKind getKind() const override
    { return NodeKind::IndexVar; }

    const Node* getVarExpr() const
    { return var_expr.get(); }

    template <typename T>
    const T* getVarExpr() const
    { return var_expr->cptr<T>(); }

    const NodeList& getIndexes() const
    { return indexes->cref<NodeList>(); }

private:
    NodeUPtr var_expr;
    NodeUPtr indexes;
};

template<NodeKind ekind, typename T>
class ConstExpr: public Expr
{
public:
    ConstExpr(T value): const_val(value)
    {}

    NodeKind getKind() const override
    { return ekind; }

    T getConstValue() const
    { return const_val; }

private:
    T const_val;
};

using BoolConstExpr = ConstExpr<NodeKind::BoolConstExpr, Lpp::Bool>;
using IntConstExpr = ConstExpr<NodeKind::IntConstExpr, Lpp::Int>;
using RealConstExpr = ConstExpr<NodeKind::RealConstExpr, Lpp::Real>;
using CharConstExpr = ConstExpr<NodeKind::CharConstExpr, Lpp::Char>;
using StrConstExpr = ConstExpr<NodeKind::StrConstExpr, std::string>;

class Stmt: public Node
{
public:
    NodeKind getKind() const override
    { return NodeKind::Stmt; }

protected:
    Stmt()
    {}
};

class AssignStmt: public Stmt
{
public:
    AssignStmt(NodeUPtr&& lhs, NodeUPtr&& rhs)
      : lhs(std::move(lhs)), rhs(std::move(rhs))
    {}

    NodeKind getKind() const override
    { return NodeKind::AssignStmt; }

    const Node* getLhs() const
    { return lhs.get(); }

    const Node* getRhs() const
    { return rhs.get(); }

    template <typename T>
    const T* getLhs() const
    { return lhs->cptr<T>(); }

    template <typename T>
    const T* getRhs() const
    { return rhs->cptr<T>(); }

private:
    NodeUPtr lhs;
    NodeUPtr rhs;
};

class CallStmt: public Stmt
{
public:
    CallStmt(NodeUPtr&& func_call)
        : func_call(std::move(func_call))
    {}

    const Node* getFuncCallExpr() const
    { return func_call.get(); }

    NodeKind getKind() const override
    { return NodeKind::CallStmt; }

private:
    NodeUPtr func_call;
};

class IfStmt: public Stmt
{
public:
    class CondBlock: public Node
    {
    public:
        CondBlock(NodeUPtr&& cond, NodeUPtr&& stmts)
          : cond(std::move(cond)), stmts(std::move(stmts))
        {}

        NodeKind getKind() const override
        { return NodeKind::IfStmtCondBlock; }

        const Node* getCond() const
        { return cond.get(); }

        template <typename T>
        const T* getCond() const
        { return cond->cptr<T>(); }

        const NodeList& getStmts() const
        { return stmts->cref<NodeList>(); }

    private:
        NodeUPtr cond;
        NodeUPtr stmts;
    };

    IfStmt(NodeUPtr&& cond_blocks, NodeUPtr&& else_block)
        : cond_blocks(std::move(cond_blocks)), else_stmts(std::move(else_block))
    {}

    NodeKind getKind() const override
    { return NodeKind::IfStmt; }

    bool hasElseBlock() const
    { return else_stmts != nullptr; }

    const NodeList& getCondBlocks() const
    { return cond_blocks->cref<NodeList>(); }

    const NodeList& getElseStmts() const
    { return else_stmts->cref<NodeList>(); }

private:
    NodeUPtr cond_blocks;
    NodeUPtr else_stmts;
};

class CaseStmt: public Stmt
{
public:
    class CondBlock: public Node
    {
    public:
        CondBlock(NodeUPtr&& cond_values, NodeUPtr&& stmts)
          : cond_values(std::move(cond_values)), stmts(std::move(stmts))
        {}

        NodeKind getKind() const override
        { return NodeKind::CaseStmtCondBlock; }
        
        const NodeList& getCondValues() const
        { return cond_values->cref<NodeList>(); }

        const NodeList& getStmts() const
        { return stmts->cref<NodeList>(); }

    private:
        NodeUPtr cond_values;
        NodeUPtr stmts;
    };

    class CondRangeValue: public Expr
    {
    public:
        CondRangeValue(NodeUPtr&& value1, NodeUPtr&& value2)
          : value1(std::move(value1)), value2(std::move(value2))
        {}

        NodeKind getKind() const override
        { return NodeKind::CaseStmtCondRangeValue; }

        const Node* getValue1() const
        { return value1.get(); }

        const Node* getValue2() const
        { return value2.get(); }

        template <typename T>
        const T* getValue1() const
        { return value1->cptr<T>(); }

        template <typename T>
        const T* getValue2() const
        { return value2->cptr<T>(); }

    private:
        NodeUPtr value1;
        NodeUPtr value2;
    };

    CaseStmt(NodeUPtr&& var_expr, NodeUPtr&& cond_blocks, NodeUPtr&& else_stmts)
        : var_expr(std::move(var_expr)),
          cond_blocks(std::move(cond_blocks)),
          else_stmts(std::move(else_stmts))
    {}

    NodeKind getKind() const override
    { return NodeKind::CaseStmt; }

    bool hasElseBlock() const
    { return else_stmts != nullptr; }

    const Node* getVarExpr() const
    { return var_expr.get(); }

    template <typename T>
    const T* getVarExpr() const
    { return var_expr->cptr<T>(); }

    const NodeList& getCondBlocks() const
    { return cond_blocks->cref<NodeList>(); }

    const NodeList& getElseStmts() const
    { return else_stmts->cref<NodeList>(); }

private:
    NodeUPtr var_expr;
    NodeUPtr cond_blocks;
    NodeUPtr else_stmts;
};

class WhileStmt: public Stmt
{
public:
    WhileStmt(NodeUPtr&& cond, NodeUPtr&& stmts)
      : cond(std::move(cond)), stmts(std::move(stmts))
    {}

    NodeKind getKind() const override
    { return NodeKind::WhileStmt; }

    const Node* getCond() const
    { return cond.get(); }

    template<typename T>
    const T* getCond() const
    { return cond->cptr<T>(); }

    const NodeList& getStmts() const
    { return stmts->cref<NodeList>(); }

private:
    NodeUPtr cond;
    NodeUPtr stmts;
};

class RepeatStmt: public Stmt
{
public:
    RepeatStmt(NodeUPtr&& cond, NodeUPtr&& stmts)
      : cond(std::move(cond)), stmts(std::move(stmts))
    {}

    NodeKind getKind() const override
    { return NodeKind::RepeatStmt; }

    const Node* getCond() const
    { return cond.get(); }

    template<typename T>
    const T* getCond() const
    { return cond->cptr<T>(); }

    const NodeList& getStmts() const
    { return stmts->cref<NodeList>(); }

private:
    NodeUPtr cond;
    NodeUPtr stmts;
};

class ForStmt: public Stmt
{
public:
    ForStmt(NodeUPtr&& var, NodeUPtr&& expr1, NodeUPtr&& expr2, NodeUPtr&& stmts)
      : var(std::move(var)), expr1(std::move(expr1)), expr2(std::move(expr2)), stmts(std::move(stmts))
    {}

    NodeKind getKind() const override
    { return NodeKind::ForStmt; }

    const Node* getVar() const
    { return var.get(); }

    const Node* getExpr1() const
    { return expr1.get(); }

    const Node* getExpr2() const
    { return expr2.get(); }

    template <typename T>
    const T* getVar() const
    { return var->cptr<T>(); }

    template <typename T>
    const T* getExpr1() const
    { return expr1->cptr<T>(); }

    template <typename T>
    const T* getExpr2() const
    { return expr2->cptr<T>(); }

    const NodeList& getStmts() const
    { return stmts->cref<NodeList>(); }

private:
    NodeUPtr var;
    NodeUPtr expr1;
    NodeUPtr expr2;
    NodeUPtr stmts;
};

class ReadStmt: public Stmt
{
public:
    ReadStmt(NodeUPtr&& lvalues): lvalue_list(std::move(lvalues))
    {}

    NodeKind getKind() const override
    { return NodeKind::ReadStmt; }

    const NodeList& getLValueList() const
    { return lvalue_list->cref<NodeList>(); }

private:
    NodeUPtr lvalue_list;
};

class WriteStmt: public Stmt
{
public:
    WriteStmt(NodeUPtr&& expr_list): expr_list(std::move(expr_list))
    {}
    
    NodeKind getKind() const override
    { return NodeKind::WriteStmt; }

    const NodeList& getExprList() const
    { return expr_list->cref<NodeList>(); }

private:
    NodeUPtr expr_list;
};

class FileStmt: public Stmt
{
public:
    enum class FileType { Text, Binary };

    void setFileType(FileType f_type) const
    { file_type = f_type; }

    FileType getFileType() const
    { return file_type; }

private:
    mutable FileType file_type;
};

class OpenFileStmt: public FileStmt
{
public:
    enum class Flags { Read, Write, ReadWrite };

    OpenFileStmt(NodeUPtr&& fn_expr, NodeUPtr&& fh_var, Flags oflags)
        : fn_expr(std::move(fn_expr)),
        fh_var(std::move(fh_var)),
        oflags(oflags)
    {}

    NodeKind getKind() const override
    { return NodeKind::OpenFileStmt; }

    const Node* getFileNameExpr() const
    { return fn_expr.get(); }

    const Node* getFileHandleVar() const
    { return fh_var.get(); }

    template <typename T>
    const T* getFileNameExpr() const
    { return fn_expr->cptr<T>(); }

    template <typename T>
    const T* getFileHandleVar() const
    { return fh_var->cptr<T>(); }

    Flags getOpenFlags() const
    { return oflags; }

private:
    NodeUPtr fn_expr;
    NodeUPtr fh_var;
    Flags oflags;
};

class ReadFileStmt: public FileStmt
{
public:
    ReadFileStmt(NodeUPtr&& lval_lst)
        : lvalue_list(std::move(lval_lst))
    {}

    NodeKind getKind() const override
    { return NodeKind::ReadFileStmt; }

    const NodeList& getLValueList() const
    { return lvalue_list->cref<NodeList>(); }

private:
    NodeUPtr lvalue_list;
};

class WriteFileStmt: public FileStmt
{
public:
    WriteFileStmt(NodeUPtr&& expr_lst)
        : expr_list(std::move(expr_lst))
    {}

    NodeKind getKind() const override
    { return NodeKind::WriteFileStmt; }

    const NodeList& getExprList() const
    { return expr_list->cref<NodeList>(); }

private:
    NodeUPtr expr_list;
};

class CloseFileStmt: public FileStmt
{
public:
    CloseFileStmt(NodeUPtr&& var): var(std::move(var))
    {}

    NodeKind getKind() const override
    { return NodeKind::CloseFileStmt; }

    const Node* getVarExpr() const
    { return var.get(); }

    template <typename T>
    const T* getVarExpr() const
    { return var->cptr<T>(); }

private:
    NodeUPtr var;
};

class ReturnStmt: public Stmt
{
public:
    ReturnStmt(): expr(nullptr)
    {}

    ReturnStmt(NodeUPtr&& expr): expr(std::move(expr))
    {}
    
    NodeKind getKind() const override
    { return NodeKind::ReturnStmt; }

    const Node* getExpr() const
    { return expr.get(); }

    template <typename T>
    const T* getExpr() const
    { return expr->cptr<T>(); }

private:
    NodeUPtr expr;
};

} // namespace Ast

#endif // AST_H
