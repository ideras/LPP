#include <stdexcept>
#include <iomanip>
#include <sstream>
#include "lpp_variant.h"

LppVariant LppVariant::Empty;

void LppVariant::init(Kind k)
{
    switch (k) {
        case Kind::String: new (&as_string) std::string(); break;
        case Kind::Array:
        case Kind::Record:
            new (&as_array) std::vector<LppVariant>();
            break;
        default:
            break;
    }
}

void LppVariant::destroy()
{
    switch (_kind) {
        case Kind::String: as_string.~basic_string(); break;
        case Kind::Array: as_array.~vector(); break;
        default:
            break;
    }
    _kind = Kind::Empty;
}

LppVariant& LppVariant::operator =(const LppVariant& other)
{
    if (kind() != other.kind()) {
        destroy();
    }
    copyFrom(other);

    return *this;
}

Lpp::Int LppVariant::toInt() const
{
    switch (_kind) {
        case Kind::Int: return as_int;
        case Kind::Real: return static_cast<Lpp::Int>(as_real);
        case Kind::ValPtr: return as_val_ptr->toInt();
        default:
            throw std::runtime_error("Invalid call LppVariant.toInt()");
    }
}

Lpp::Real LppVariant::toReal() const
{
    switch (_kind) {
        case Kind::Int: return static_cast<Lpp::Real>(as_int);
        case Kind::Real: return as_real;
        case Kind::ValPtr: return as_val_ptr->toReal();
        default:
            throw std::runtime_error("Invalid call LppVariant.toReal()");
    }
}

Lpp::Bool LppVariant::toBool() const
{
    switch (_kind) {
        case Kind::Bool: return as_bool;
        case Kind::ValPtr: return as_val_ptr->as_bool;
        default:
            throw std::runtime_error("Invalid call LppVariant.toBool()");
    }
}

Lpp::Char LppVariant::toChar() const
{
    switch (_kind) {
        case Kind::Char: return as_char;
        case Kind::CharPtr: return *as_char_ptr;
        case Kind::ValPtr: return as_val_ptr->as_char;
        default:
            throw std::runtime_error("Invalid call LppVariant.toChar()");
    }
}

void LppVariant::initValue(const TypeInfo *type_info)
{
    switch (type_info->kind()) {
        case TypeInfo::Kind::Int :
            _kind = Kind::Int;
            as_int = 0;
            break;
        case TypeInfo::Kind::Real :
            _kind = Kind::Real;
            as_real = 0.0;
            break;
        case TypeInfo::Kind::Bool :
            _kind = Kind::Bool;
            as_bool = false;
            break;
        case TypeInfo::Kind::Char :
            _kind = Kind::Char;
            as_char = '\0';
            break;
        case TypeInfo::Kind::File:
            _kind = Kind::Int;
            as_int = -1;
            break;
        case TypeInfo::Kind::String : {
            const StringTypeInfo *str_ti = type_info->cptr<StringTypeInfo>();

            _kind = Kind::String;
            if (str_ti->byteSize() > 0)
                new (&as_string) std::string(str_ti->byteSize(), '\0');
            else
                new (&as_string) std::string("");

            break;
        }
        case TypeInfo::Kind::Array : {
            const ArrayTypeInfo *arr_ti = type_info->cptr<ArrayTypeInfo>();

            _kind = Kind::Array;
            new (&as_array) std::vector<LppVariant>(arr_ti->flatSize());

            for (auto& itm : as_array) {
                itm.initValue(arr_ti->elemType().get());
            }
            break;
        }
        case TypeInfo::Kind::Record : {
            const RecordTypeInfo *rec_ti = type_info->cptr<RecordTypeInfo>();

            _kind = Kind::Record;
            new (&as_array) std::vector<LppVariant>(rec_ti->fields().size());

            for (const auto& fld : rec_ti->fields()) {
                    int index = fld.index();

                    as_array[index].initValue(fld.typeInfo().get());
            }
            break;
        }

        default:
            break;
    };
}

void LppVariant::setPointedValue(const LppVariant &val)
{
    switch(kind()) {
        case Kind::ValPtr:
            *as_val_ptr = val;
            break;
        case Kind::CharPtr:
            *as_char_ptr = val.toChar();
            break;
        default:
            throw std::runtime_error("No reference in LppVariant.setPointedValue");
            break;
    }
}

LppVariant LppVariant::getPointedValue() const
{
    switch(kind()) {
        case Kind::ValPtr:  return *as_val_ptr;
        case Kind::CharPtr: return *as_char_ptr;
        default:
            throw std::runtime_error("No reference in LppVariant.getPointedValue");
    }
}

void LppVariant::copyFrom(const LppVariant& rhs)
{
    if (isEmpty()) {
        init(rhs.kind());
    }
    _kind = rhs._kind;

    switch (_kind) {
        case Kind::Bool: as_bool = rhs.as_bool; break;
        case Kind::Int: as_int = rhs.as_int; break;
        case Kind::Char: as_char = rhs.as_char; break;
        case Kind::Real: as_real = rhs.as_real; break;
        case Kind::String: as_string = rhs.as_string; break;
        case Kind::Array:
        case Kind::Record:
            as_array = rhs.as_array;
            break;

        case Kind::ValPtr: as_val_ptr = rhs.as_val_ptr; break;
        case Kind::CharPtr: as_char_ptr = rhs.as_char_ptr; break;

        default:
            break;
    }
}

LppVariant LppVariant::makeArray(std::vector<LppVariant>&& varray)
{
    LppVariant val;

    val._kind = Kind::Array;
    new (&val.as_array) std::vector(std::move(varray));

    return val;
}

LppVariant LppVariant::makeRecord(std::vector<LppVariant>&& varray)
{
    LppVariant val;

    val._kind = Kind::Record;
    new (&val.as_array) std::vector(std::move(varray));

    return val;
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

bool operator> (const LppVariant& lhs, const LppVariant& rhs)
{
    return rhs < lhs;
}

bool operator<= (const LppVariant& lhs, const LppVariant& rhs)
{
    return !(operator> (lhs, rhs));
}
bool operator>= (const LppVariant& lhs, const LppVariant& rhs)
{
    return !(operator< (lhs, rhs));
}

bool operator!= (const LppVariant& lhs, const LppVariant& rhs)
{
    return !(operator== (lhs, rhs));
}

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
