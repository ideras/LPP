#include "lpp_variant.h"
#include "lpp_string.h"
#include "lpp_array.h"
#include "lpp_record.h"
#include "../../semantic/lpp_type_info.h"
#include <stdexcept>

LppVariant::LppVariant() : data(std::monostate{}) {}
LppVariant::LppVariant(Lpp::Int val) : data(val) {}
LppVariant::LppVariant(Lpp::Real val) : data(val) {}
LppVariant::LppVariant(Lpp::Bool val) : data(val) {}
LppVariant::LppVariant(Lpp::Char val) : data(val) {}
LppVariant::LppVariant(ValPtr val) : data(val) {}
LppVariant::LppVariant(char *val) : data(val) {}
LppVariant::LppVariant(std::shared_ptr<LppObject> val) : data(val) {}
LppVariant::LppVariant(const std::string &val) : LppVariant(std::make_shared<LppString>(val)) {}

LppVariant LppVariant::fromString(const std::string &s)
{
    return LppVariant(std::make_shared<LppString>(s));
}

LppVariant::LppVariant(const LppVariant &other)
{
    if (auto *ptr = std::get_if<std::shared_ptr<LppObject>>(&other.data))
    {
        data = (*ptr)->clone();
    }
    else
    {
        data = other.data;
    }
}

LppVariant &LppVariant::operator=(const LppVariant &other)
{
    if (this != &other)
    {
        if (auto *ptr = std::get_if<std::shared_ptr<LppObject>>(&other.data))
        {
            data = (*ptr)->clone();
        }
        else
        {
            data = other.data;
        }
    }
    return *this;
}

LppVariant::Kind LppVariant::kind() const
{
    if (std::holds_alternative<std::monostate>(data))
        return Kind::Empty;
    if (std::holds_alternative<Lpp::Int>(data))
        return Kind::Int;
    if (std::holds_alternative<Lpp::Real>(data))
        return Kind::Real;
    if (std::holds_alternative<Lpp::Bool>(data))
        return Kind::Bool;
    if (std::holds_alternative<Lpp::Char>(data))
        return Kind::Char;
    if (std::holds_alternative<ValPtr>(data))
        return Kind::ValPtr;
    if (std::holds_alternative<Lpp::Char *>(data))
        return Kind::CharPtr;
    if (auto *ptr = std::get_if<std::shared_ptr<LppObject>>(&data))
    {
        switch ((*ptr)->kind())
        {
            case LppObjectKind::String:
                return Kind::String;
            case LppObjectKind::Array:
                return Kind::Array;
            case LppObjectKind::Record:
                return Kind::Record;
        }
    }

    return Kind::Empty;
}

LppVariant::Kind LppVariant::valueKind() const
{
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->valueKind();
    return kind();
}

bool LppVariant::isEmpty() const 
{ return kind() == Kind::Empty; }

bool LppVariant::isPtr() const
{ return std::holds_alternative<ValPtr>(data) || std::holds_alternative<char *>(data); }

bool LppVariant::isValPtr() const
{ return std::holds_alternative<ValPtr>(data); }

bool LppVariant::isInt() const
{
    if (std::holds_alternative<Lpp::Int>(data))
        return true;
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->isInt();

    return false;
}

bool LppVariant::isReal() const
{
    if (std::holds_alternative<Lpp::Real>(data))
        return true;
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->isReal();

    return false;
}

bool LppVariant::isNumber() const
{ return isInt() || isReal(); }

bool LppVariant::isBool() const
{
    if (std::holds_alternative<Lpp::Bool>(data))
        return true;
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->isBool();

    return false;
}

bool LppVariant::isChar() const
{
    if (std::holds_alternative<Lpp::Char>(data))
        return true;
    if (std::holds_alternative<Lpp::Char *>(data))
        return true;
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->isChar();

    return false;
}

bool LppVariant::isString() const
{
    if (auto *ptr = std::get_if<std::shared_ptr<LppObject>>(&data))
        return (*ptr)->kind() == LppObjectKind::String;
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->isString();

    return false;
}

bool LppVariant::isArray() const
{
    if (auto *ptr = std::get_if<std::shared_ptr<LppObject>>(&data))
        return (*ptr)->kind() == LppObjectKind::Array;
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->isArray();

    return false;
}

bool LppVariant::isRecord() const
{
    if (auto *ptr = std::get_if<std::shared_ptr<LppObject>>(&data))
        return (*ptr)->kind() == LppObjectKind::Record;
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->isRecord();

    return false;
}

Lpp::Int LppVariant::toInt() const
{
    if (auto *v = std::get_if<Lpp::Int>(&data))
        return *v;
    if (auto *v = std::get_if<Lpp::Real>(&data))
        return static_cast<Lpp::Int>(*v);
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->toInt();

    throw std::runtime_error("Not an int");
}

Lpp::Real LppVariant::toReal() const
{
    if (auto *v = std::get_if<Lpp::Real>(&data))
        return *v;
    if (auto *v = std::get_if<Lpp::Int>(&data))
        return static_cast<Lpp::Real>(*v);
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->toReal();

    throw std::runtime_error("Not a real");
}

Lpp::Bool LppVariant::toBool() const
{
    if (auto *v = std::get_if<Lpp::Bool>(&data))
        return *v;
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->toBool();

    throw std::runtime_error("Not a bool");
}

Lpp::Char LppVariant::toChar() const
{
    if (auto *v = std::get_if<Lpp::Char>(&data))
        return *v;
    if (auto *v = std::get_if<Lpp::Char *>(&data))
        return **v;
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->toChar();

    throw std::runtime_error("Not a char");
}

const std::string &LppVariant::stringCRef() const
{
    if (auto *ptr = std::get_if<std::shared_ptr<LppObject>>(&data))
    {
        if ((*ptr)->kind() == LppObjectKind::String)
        {
            return static_cast<LppString *>((*ptr).get())->get();
        }
    }
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->stringCRef();

    throw std::runtime_error("Not a string");
}

std::string &LppVariant::stringRef()
{
    if (auto *ptr = std::get_if<std::shared_ptr<LppObject>>(&data))
    {
        if ((*ptr)->kind() == LppObjectKind::String)
        {
            return static_cast<LppString *>((*ptr).get())->get();
        }
    }
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->stringRef();

    throw std::runtime_error("Not a string");
}

std::string LppVariant::toString() const
{
    if (auto *ptr = std::get_if<std::shared_ptr<LppObject>>(&data))
    {
        return (*ptr)->toString();
    }

    return "";
}

const std::vector<LppVariant> &LppVariant::arrayCRef() const
{
    if (auto *ptr = std::get_if<std::shared_ptr<LppObject>>(&data)) {
        if ((*ptr)->kind() == LppObjectKind::Array) {
            return static_cast<LppArray *>((*ptr).get())->getData();
        }
        else if ((*ptr)->kind() == LppObjectKind::Record) {
            return static_cast<LppRecord *>((*ptr).get())->getFields();
        }
    }
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->arrayCRef();

    throw std::runtime_error("Not an array or record");
}

std::vector<LppVariant> &LppVariant::arrayRef()
{
    if (auto *ptr = std::get_if<std::shared_ptr<LppObject>>(&data)) {
        if ((*ptr)->kind() == LppObjectKind::Array) {
            return static_cast<LppArray *>((*ptr).get())->getData();
        }
        else if ((*ptr)->kind() == LppObjectKind::Record) {
            return static_cast<LppRecord *>((*ptr).get())->getFields();
        }
    }
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->arrayRef();

    throw std::runtime_error("Not an array or record");
}

const std::vector<int> &LppVariant::getArrayDimensions() const
{
    if (auto *ptr = std::get_if<std::shared_ptr<LppObject>>(&data)) {
        if ((*ptr)->kind() == LppObjectKind::Array) {
            return static_cast<LppArray *>((*ptr).get())->dimensions();
        }
    }
    if (auto *v = std::get_if<ValPtr>(&data))
        return (*v)->getArrayDimensions();

    throw std::runtime_error("Not an array");
}

void LppVariant::initValue(const TypeInfo *type_info)
{
    if (type_info->is(TypeInfo::Kind::Int))
        *this = LppVariant(static_cast<Lpp::Int>(0));
    else if (type_info->is(TypeInfo::Kind::Real))
        *this = LppVariant(static_cast<Lpp::Real>(0.0));
    else if (type_info->is(TypeInfo::Kind::Char))
        *this = LppVariant(static_cast<Lpp::Char>('\0'));
    else if (type_info->is(TypeInfo::Kind::Bool))
        *this = LppVariant(static_cast<Lpp::Bool>(false));
    else if (type_info->is(TypeInfo::Kind::String)) {
        int size = type_info->byteSize();
        if (size > 0) {
            *this = LppVariant(std::string(size, '\0'));
        }
        else {
            *this = LppVariant(std::string(""));
        }
    }
    else if (type_info->is(TypeInfo::Kind::Array)) {
        const auto *ati = type_info->cptr<ArrayTypeInfo>();
        std::vector<LppVariant> elements(ati->flatSize());
        for (auto &el : elements)
            el.initValue(ati->elemType().get());
        *this = LppVariant(std::make_shared<LppArray>(std::move(elements), ati->dims()));
    }
    else if (type_info->is(TypeInfo::Kind::Record)) {
        const auto *rti = type_info->cptr<RecordTypeInfo>();
        std::vector<LppVariant> fields(rti->fields().size());
        for (const auto &f : rti->fields())
        {
            fields[f.index()].initValue(f.typeInfo().get());
        }
        *this = LppVariant(std::make_shared<LppRecord>(std::move(fields)));
    }
    else {
        data = std::monostate{};
    }
}

void LppVariant::setPointedValue(const LppVariant &val)
{
    if (auto *v = std::get_if<ValPtr>(&data)) {
        **v = val;
    }
    else if (auto *c = std::get_if<Lpp::Char *>(&data)) {
        **c = val.toChar();
    }
    else {
        *this = val;
    }
}

LppVariant LppVariant::getPointedValue() const
{
    if (auto *v = std::get_if<ValPtr>(&data))
        return **v;
    else if (auto *c = std::get_if<Lpp::Char *>(&data))
        return LppVariant(**c);

    return *this;
}

LppVariant LppVariant::makeArray(std::vector<LppVariant> &&varray, const std::vector<int> &dims)
{
    std::vector<int> dimensions = dims;

    if (dimensions.empty()) {
        dimensions.push_back(static_cast<int>(varray.size()));
    }

    return LppVariant(std::make_shared<LppArray>(std::move(varray), dimensions));
}

LppVariant LppVariant::makeRecord(std::vector<LppVariant> &&varray)
{
    return LppVariant(std::make_shared<LppRecord>(std::move(varray)));
}

bool operator< (const LppVariant& lhs, const LppVariant& rhs)
{
    if (lhs.isInt() && rhs.isInt())
        return lhs.toInt() < rhs.toInt();
    else if (lhs.isNumber() && rhs.isNumber())
        return lhs.toReal() < rhs.toReal();
    else if (lhs.isChar() && rhs.isChar())
        return lhs.toChar() < rhs.toChar();
    else if (lhs.isBool() && rhs.isBool())
        return lhs.toBool() < rhs.toBool();
    else if (lhs.isString() && rhs.isString())
        return lhs.stringCRef() < rhs.stringCRef();

    throw std::runtime_error("Invalid types in less than operator");
}

bool operator>(const LppVariant &lhs, const LppVariant &rhs)
{ return rhs < lhs; }

bool operator<=(const LppVariant &lhs, const LppVariant &rhs)
{ return !(rhs < lhs); }

bool operator>=(const LppVariant &lhs, const LppVariant &rhs)
{ return !(lhs < rhs); }

bool operator== (const LppVariant& lhs, const LppVariant& rhs)
{
    if (lhs.isInt() && rhs.isInt())
        return lhs.toInt() == rhs.toInt();
    else if (lhs.isNumber() && rhs.isNumber())
        return lhs.toReal() == rhs.toReal();
    else if (lhs.isChar() && rhs.isChar())
        return lhs.toChar() == rhs.toChar();
    else if (lhs.isBool() && rhs.isBool())
        return lhs.toBool() == rhs.toBool();
    else if (lhs.isString() && rhs.isString())
        return lhs.stringCRef() == rhs.stringCRef();

    throw std::runtime_error("Invalid types in equal operator");
}

bool operator!=(const LppVariant &lhs, const LppVariant &rhs)
{ return !(lhs == rhs); }
