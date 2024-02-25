#ifndef LPPVARIANT_H
#define LPPVARIANT_H

#include <string>
#include <vector>
#include <memory>
#include "lpp_type_info.h"
#include "lpp_types.h"

class LppVariant;
using LppVariantSPtr = std::shared_ptr<LppVariant>;

class LppVariant
{
public:
    static LppVariant Empty;

    enum class Kind
    { Int, Real, Char, Bool, String, Array, Record, ValPtr, CharPtr, Empty };

    LppVariant(): LppVariant(Kind::Empty)
    {}

    LppVariant(Lpp::Int ival): LppVariant(Kind::Int)
    { as_int = ival; }

    LppVariant(Lpp::Real rval): LppVariant(Kind::Real)
    { as_real = rval; }

    LppVariant(Lpp::Char ch): LppVariant(Kind::Char)
    { as_char = ch; }

    LppVariant(Lpp::Bool val): LppVariant(Kind::Bool)
    { as_bool = val; }

    LppVariant(const std::string& str): LppVariant(Kind::String)
    { new (&as_string) std::string(str); }

    LppVariant(LppVariant *val_ptr): LppVariant(Kind::ValPtr)
    { as_val_ptr = val_ptr; }

    LppVariant(char *char_ptr): LppVariant(Kind::CharPtr)
    { as_char_ptr = char_ptr; }

    LppVariant(const LppVariant& other): _kind(Kind::Empty)
    { copyFrom(other); }

    ~LppVariant()
    { destroy(); }

    LppVariant& operator= (const LppVariant& other);

    Kind kind() const
    { return _kind; }

    Kind valueKind() const
    { return (isValPtr()? as_val_ptr->_kind : (isCharPtr()? Kind::Char : _kind)); }

    bool isEmpty() const
    { return _kind == Kind::Empty; }

    bool isNumber() const
    { return isInt() || isReal(); }

    bool isInt() const
    { return (_kind == Kind::Int) || (isValPtr() && as_val_ptr->isInt()) ; }

    bool isReal() const
    { return (_kind == Kind::Real) || (isValPtr() && as_val_ptr->isReal()); }

    bool isChar() const
    {
        return (_kind == Kind::Char)
               || (_kind == Kind::CharPtr)
               || (isValPtr() && as_val_ptr->isChar());
    }

    bool isBool() const
    { return (_kind == Kind::Bool) || (isValPtr() && as_val_ptr->isBool()); }

    bool isString() const
    { return (_kind == Kind::String) || (isValPtr() && as_val_ptr->isString()); }

    bool isArray() const
    { return (_kind == Kind::Array) || (isValPtr() && as_val_ptr->isArray()); }

    bool isRecord() const
    { return (_kind == Kind::Record) || (isValPtr() && as_val_ptr->isRecord()); }

    bool isPtr() const
    { return (_kind == Kind::ValPtr) || (_kind == Kind::CharPtr); }

    bool isValPtr() const
    { return (_kind == Kind::ValPtr); }

    bool isCharPtr() const
    { return (_kind == Kind::CharPtr); }

    Lpp::Int    toInt() const;
    Lpp::Real   toReal() const;
    Lpp::Bool   toBool() const;
    Lpp::Char   toChar() const;

    explicit operator Lpp::Int& ()
    { return isValPtr()? as_val_ptr->as_int : as_int; }

    explicit operator Lpp::Real& ()
    { return isValPtr()? as_val_ptr->as_real : as_real; }

    explicit operator Lpp::Bool& ()
    { return isValPtr()? as_val_ptr->as_bool : as_bool; }

    explicit operator Lpp::Char& ()
    { return isValPtr()? as_val_ptr->as_char : (isCharPtr()? *as_char_ptr : as_char); }

    explicit operator std::string& ()
    { return isValPtr()? as_val_ptr->as_string : as_string; }

    explicit operator std::vector<LppVariant>& ()
    { return isValPtr()? as_val_ptr->as_array : as_array; }

    std::string& stringRef()
    { return isValPtr()? as_val_ptr->as_string : as_string; }

    const std::string& stringCRef() const
    { return isValPtr()? as_val_ptr->as_string : as_string; }

    std::vector<LppVariant>& arrayRef()
    { return isValPtr()? as_val_ptr->as_array : as_array; }

    const std::vector<LppVariant>& arrayCRef() const
    { return isValPtr()? as_val_ptr->as_array : as_array; }

    void initValue(const TypeInfo *type_info);
    void setPointedValue(const LppVariant& val);
    LppVariant getPointedValue() const;

    static LppVariant makeArray(std::vector<LppVariant>&& varray);
    static LppVariant makeRecord(std::vector<LppVariant>&& varray);

private:
    LppVariant(Kind _type): _kind(_type)
    {}

    void init(Kind k);
    void copyFrom(const LppVariant& val);
    void destroy();

private:
    Kind _kind;

    union {
        Lpp::Int    as_int;
        Lpp::Real   as_real;
        Lpp::Bool   as_bool;
        Lpp::Char   as_char;
        std::string as_string;
        std::vector<LppVariant> as_array;
        LppVariant  *as_val_ptr;
        Lpp::Char   *as_char_ptr;
    };
};

bool operator< (const LppVariant& lhs, const LppVariant& rhs);
bool operator> (const LppVariant& lhs, const LppVariant& rhs);
bool operator<= (const LppVariant& lhs, const LppVariant& rhs);
bool operator>= (const LppVariant& lhs, const LppVariant& rhs);
bool operator!= (const LppVariant& lhs, const LppVariant& rhs);
bool operator== (const LppVariant& lhs, const LppVariant& rhs);

#endif // LPPVARIANT_H
