#ifndef LPP_SYMB_TABLE_H
#define LPP_SYMB_TABLE_H

#include <string>
#include <memory>
#include <unordered_map>
#include "lpp_variant.h"
#include "lpp_type_info.h"
#include "str_util.h"

struct LppVar
{
    LppVar(const std::string& _name, const TypeInfoSPtr& type_info)
        : _name(_name), type_info(type_info), _value()
    {}

    ~LppVar()
    {}

    std::string name() const
    { return _name; }

    const TypeInfoSPtr& typeInfo() const
    { return type_info; }

    void createValue()
    { _value.initValue(type_info.get()); }

    LppVariant& value()
    { return _value; }

private:
    std::string _name;
    TypeInfoSPtr type_info;
    LppVariant _value;
};

using LppVarSPtr = std::shared_ptr<LppVar>;

template <typename T>
class SymbolTable
{
public:
    SymbolTable()
    {}

    ~SymbolTable()
    {}

    std::shared_ptr<T> get(const std::string& key) {
        auto it = map.find(str::lower(key));

        return (it == map.end())? nullptr : it->second;
    }

    void add(const std::string& key, const std::shared_ptr<T>& value)
    { map.emplace(str::lower(key), value); }

    void add(const std::string& key, std::shared_ptr<T>&& value)
    { map.emplace(str::lower(key), std::move(value)); }

    bool contains(const std::string &key) const
    { return map.count(str::lower(key)) != 0; }

    void clear()
    { map.clear(); }

    size_t size() const
    { return map.size(); }

    std::unordered_map<std::string, std::shared_ptr<T>>& items()
    { return map; }

private:
    std::unordered_map<std::string, std::shared_ptr<T>> map;
};

#endif // LPP_SYMB_TABLE_H
