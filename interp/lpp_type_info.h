#ifndef LPPTYPEINFO_H
#define LPPTYPEINFO_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "lpp_types.h"

class TypeInfo;

using TypeInfoSPtr = std::shared_ptr<TypeInfo>;

class TypeInfo
{
public:
    static TypeInfoSPtr Int;
    static TypeInfoSPtr Real;
    static TypeInfoSPtr Char;
    static TypeInfoSPtr Bool;

    enum class Kind
    { Int, Real, Char, Bool, String, Array, Record, Alias, File };

    TypeInfo(): TypeInfo(0, true)
    {}

    TypeInfo(int size, bool is_fixed_size)
      : byte_size(size), is_fixed_size(is_fixed_size)
    {}

    virtual ~TypeInfo()
    {}

    virtual bool isPrimType() const
    { return false; }

    template <typename TKind>
    bool is(TKind tkind) const
    { return kind() == tkind; }

    template<typename TKind, typename... TMore>
    bool is(TKind k1, TMore... kn) const
    { return is(k1) || is(kn...); }

    std::string kindName() const;

    int byteSize() const
    { return byte_size; }

    bool isFixedSize() const
    { return is_fixed_size; }

    virtual Kind kind() const = 0;
    virtual bool isEquiv(const TypeInfo *rhs) const = 0;

    template <typename T>
    const T* cptr() const
    { return reinterpret_cast<const T *>(this); }

    template <typename T>
    T* ptr()
    { return reinterpret_cast<T *>(this); }

    static TypeInfoSPtr String(int size = 0);
    static TypeInfoSPtr Array(const std::vector<int>& dims, const TypeInfoSPtr& elem_type);
    static TypeInfoSPtr BinaryFile(const TypeInfoSPtr& elem_type);
    static TypeInfoSPtr TextFile;
    static TypeInfoSPtr File;

protected:
    int byte_size;
    bool is_fixed_size;
};

template<TypeInfo::Kind tkind>
class PrimTypeInfo: public TypeInfo
{
public:
    PrimTypeInfo(int size): TypeInfo(size, true)
    {}

    bool isPrimType() const override
    { return true; }

    TypeInfo::Kind kind() const override
    { return tkind; }
};

class IntTypeInfo: public PrimTypeInfo<TypeInfo::Kind::Int>
{
public:
    IntTypeInfo(): PrimTypeInfo(sizeof(Lpp::Int))
    {}

    bool isEquiv(const TypeInfo *rhs) const override
    { return rhs->is(Kind::Int) || rhs->is(Kind::Real); }
};

class RealTypeInfo: public PrimTypeInfo<TypeInfo::Kind::Real>
{
public:
    RealTypeInfo(): PrimTypeInfo(sizeof(Lpp::Real))
    {}

    bool isEquiv(const TypeInfo *rhs) const override
    { return rhs->is(Kind::Int) || rhs->is(Kind::Real); }
};

class CharTypeInfo: public PrimTypeInfo<TypeInfo::Kind::Char>
{
public:
    CharTypeInfo(): PrimTypeInfo(sizeof(Lpp::Char))
    {}

    bool isEquiv(const TypeInfo *rhs) const override
    { return rhs->is(Kind::String) || rhs->is(Kind::Char); }
};

class BoolTypeInfo: public PrimTypeInfo<TypeInfo::Kind::Bool>
{
public:
    BoolTypeInfo(): PrimTypeInfo(sizeof(Lpp::Bool))
    {}

    bool isEquiv(const TypeInfo *rhs) const override
    { return rhs->is(Kind::Bool); }
};

class StringTypeInfo: public TypeInfo
{
public:
    StringTypeInfo(int size): TypeInfo(size, size != 0)
    {}

    Kind kind() const override
    { return Kind::String; }

    bool isEquiv(const TypeInfo *rhs) const override
    { return rhs->is(Kind::String) || rhs->is(Kind::Char); }
};

class ArrayTypeInfo: public TypeInfo
{
public:
    ArrayTypeInfo(const std::vector<int>& _dims, const TypeInfoSPtr& elem_type)
        : _dims(_dims), elem_type(elem_type)
    { updateSize(); }

    int flatSize() const
    { return flat_size; }

    const std::vector<int>& dims() const
    { return _dims; }

    TypeInfoSPtr elemType() const
    { return elem_type; }

    Kind kind() const override
    { return Kind::Array; }

    bool isEquiv(const TypeInfo *rhs) const override;
    int flatIndex(const std::vector<int>& idxs) const;

private:
    void updateSize();

private:
    std::vector<int> _dims;
    int flat_size;
    TypeInfoSPtr elem_type;
};

class RecordTypeInfo: public TypeInfo
{
public:
    class FieldInfo
    {
        friend class RecordTypeInfo;
    public:
        FieldInfo(const std::string& _name, const TypeInfoSPtr& type_info)
            : _name(_name), type_info(type_info)
        {}

        std::string name() const
        { return _name; }

        int index() const
        { return _index; }

        const TypeInfoSPtr& typeInfo() const
        { return type_info; }

    private:
        std::string _name;
        int _index;
        const TypeInfoSPtr type_info;
    };

    RecordTypeInfo(const std::string& _name, std::vector<FieldInfo>&& _fields)
      : _name(_name), _fields(std::move(_fields))
    { updateRecordInfo(); }

    std::string name() const
    { return _name; }

    bool hasField(const std::string& f_name) const
    { return field(f_name) == nullptr; }

    const FieldInfo* field(const std::string& f_name) const;

    const std::vector<FieldInfo>& fields() const
    { return _fields; }

    Kind kind() const override
    { return Kind::Record; }

    bool isEquiv(const TypeInfo *rhs) const override
    { return (rhs->is(Kind::Record) && (rhs->cptr<RecordTypeInfo>()->_name == _name)); }

    static TypeInfoSPtr createShared(const std::string& _name, std::vector<FieldInfo>&& _fields);

private:
    void updateRecordInfo();

private:
    std::string _name;
    std::vector<FieldInfo> _fields;
};

class AliasTypeInfo: public TypeInfo
{
public:
    AliasTypeInfo(const std::string& _name, const TypeInfoSPtr& alias_type)
        : _name(_name), alias_type(alias_type)
    { is_fixed_size = alias_type->isFixedSize(); }

    std::string name() const
    { return _name; }

    TypeInfoSPtr aliasType() const
    { return alias_type; }

    Kind kind() const override
    { return Kind::Alias; }

    bool isEquiv(const TypeInfo *rhs) const override
    { return alias_type->isEquiv(rhs); }

private:
    std::string _name;
    TypeInfoSPtr alias_type;
};

class FileTypeInfo: public TypeInfo
{
public:
    FileTypeInfo(): elem_type(nullptr)
    {}

    FileTypeInfo(const TypeInfoSPtr& elem_type)
      :  elem_type(elem_type)
    {}

    bool isBinary() const
    { return elem_type != nullptr; }

    bool isText() const
    { return elem_type == nullptr; }

    TypeInfoSPtr elemType() const
    { return elem_type; }

    Kind kind() const override
    { return Kind::File; }

    bool isEquiv(const TypeInfo *rhs) const override
    { return rhs->is(Kind::File); }

private:
    TypeInfoSPtr elem_type;
};

#endif // LPPTYPEINFO_H
