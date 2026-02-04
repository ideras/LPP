#ifndef LPP_VARIANT_H
#define LPP_VARIANT_H

#include <variant>
#include <memory>
#include <string>
#include <vector>
#include "../../utils/lpp_types.h"
#include "lpp_object.h"

class TypeInfo;

class LppVariant
{
public:
    using ValPtr = LppVariant *;

    enum class Kind
    {
        Empty,
        Int,
        Real,
        Bool,
        Char,
        ValPtr,
        CharPtr,
        String,
        Array,
        Record
    };

    using Value = std::variant<
        std::monostate,
        Lpp::Int,
        Lpp::Real,
        Lpp::Bool,
        Lpp::Char,
        ValPtr,
        Lpp::Char *,
        std::shared_ptr<LppObject>>;

    LppVariant();
    LppVariant(Lpp::Int val);
    LppVariant(Lpp::Real val);
    LppVariant(Lpp::Bool val);
    LppVariant(Lpp::Char val);
    LppVariant(ValPtr val);
    LppVariant(Lpp::Char *val);
    LppVariant(std::shared_ptr<LppObject> val);
    LppVariant(const std::string &val);

    // Explicit string constructor helper (creates LppString)
    static LppVariant fromString(const std::string &s);

    // Copy semantics (Deep Copy)
    LppVariant(const LppVariant &other);
    LppVariant &operator=(const LppVariant &other);

    // Move semantics (Default)
    LppVariant(LppVariant &&) = default;
    LppVariant &operator=(LppVariant &&) = default;

    ~LppVariant() = default;

    Kind kind() const;
    Kind valueKind() const;

    // Accessors
    bool isEmpty() const;
    bool isInt() const;
    bool isReal() const;
    bool isNumber() const;
    bool isBool() const;
    bool isChar() const;
    bool isString() const;
    bool isArray() const;
    bool isRecord() const;
    bool isPtr() const;
    bool isValPtr() const;

    Lpp::Int toInt() const;
    Lpp::Real toReal() const;
    Lpp::Bool toBool() const;
    Lpp::Char toChar() const;
    std::string toString() const; // For debugging/printing? Or use Serializer?

    // Reference accessors
    const std::string &stringCRef() const;
    std::string &stringRef();

    const std::vector<LppVariant> &arrayCRef() const;
    std::vector<LppVariant> &arrayRef();
    const std::vector<int> &getArrayDimensions() const;

    void initValue(const TypeInfo *type_info);
    void setPointedValue(const LppVariant &val);
    LppVariant getPointedValue() const;

    static LppVariant makeArray(std::vector<LppVariant> &&varray, const std::vector<int> &dims = {});
    static LppVariant makeRecord(std::vector<LppVariant> &&varray);

private:
    Value data;
};

bool operator<(const LppVariant &lhs, const LppVariant &rhs);
bool operator>(const LppVariant &lhs, const LppVariant &rhs);
bool operator<=(const LppVariant &lhs, const LppVariant &rhs);
bool operator>=(const LppVariant &lhs, const LppVariant &rhs);
bool operator!=(const LppVariant &lhs, const LppVariant &rhs);
bool operator==(const LppVariant &lhs, const LppVariant &rhs);

#endif // LPP_VARIANT_H
