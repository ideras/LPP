#include <algorithm>
#include "lpp_type_info.h"
#include "str_util.h"

TypeInfoSPtr TypeInfo::Int(new IntTypeInfo);
TypeInfoSPtr TypeInfo::Real(new RealTypeInfo);
TypeInfoSPtr TypeInfo::Char(new CharTypeInfo);
TypeInfoSPtr TypeInfo::Bool(new BoolTypeInfo);
TypeInfoSPtr TypeInfo::TextFile(new FileTypeInfo);
TypeInfoSPtr TypeInfo::File(new FileTypeInfo);

const RecordTypeInfo::FieldInfo *RecordTypeInfo::field(const std::string &f_name) const
{
    auto it = std::find_if(_fields.begin(), _fields.end(),
                           [&f_name](const FieldInfo& fi) {
                               return str::iequals()(fi.name(), f_name);
                           });

    return (it != _fields.end())? std::addressof(*it) : nullptr;
}

TypeInfoSPtr RecordTypeInfo::createShared(const std::string &_name, std::vector<FieldInfo> &&_fields)
{
    return std::make_shared<RecordTypeInfo>(_name, std::move(_fields));
}

void RecordTypeInfo::updateRecordInfo()
{
    int index = 0;

    byte_size = 0;
    is_fixed_size = true;
    for (auto& fld : _fields) {
        fld._index = index++;

        byte_size += fld.typeInfo()->byteSize();
        is_fixed_size = is_fixed_size && fld.typeInfo()->isFixedSize();
    }
}

bool ArrayTypeInfo::isEquiv(const TypeInfo *rhs) const
{
    if (!rhs->is(Kind::Array)) {
        return false;
    }
    const ArrayTypeInfo *ati = rhs->cptr<ArrayTypeInfo>();

    return (_dims == ati->dims()) && (elem_type->isEquiv(ati->elemType().get()));
}

int ArrayTypeInfo::flatIndex(const std::vector<int> &idxs) const
{
    int flat_idx = 0, m = 1;

    auto itd = _dims.crbegin();
    for (auto itr = idxs.crbegin(); itr != idxs.crend(); itr++) {
        flat_idx += (*itr) * m;
        m *= *itd++;
    }

    return flat_idx;
}

void ArrayTypeInfo::updateSize()
{
    flat_size = 1;
    for (auto n : _dims) {
        flat_size *= n;
    }
    byte_size = flat_size * elem_type->byteSize();
    is_fixed_size = elem_type->isFixedSize();
}

std::string TypeInfo::kindName() const
{
    switch (kind()) {
        case Kind::Int: return "Entero"; 
        case Kind::Real: return "Real"; 
        case Kind::Char: return "Caracter"; 
        case Kind::Bool: return "Booleano"; 
        case Kind::String: return "Cadena"; 
        case Kind::Array: return "Arreglo"; 
        case Kind::Record: return "Registro";
        default:
            return "DPU";
        }
}

TypeInfoSPtr TypeInfo::String(int size)
{
    return std::make_shared<StringTypeInfo>(size);
}

TypeInfoSPtr TypeInfo::Array(const std::vector<int>& dims, const TypeInfoSPtr &elem_type)
{
    return std::make_shared<ArrayTypeInfo>(dims, elem_type);
}

TypeInfoSPtr TypeInfo::BinaryFile(const TypeInfoSPtr &elem_type)
{
    return std::make_shared<FileTypeInfo>(elem_type);
}
