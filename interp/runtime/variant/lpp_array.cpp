#include "lpp_array.h"

LppArray::LppArray(std::vector<LppVariant> &&data, const std::vector<int> &dims)
    : data(std::move(data)), dims(dims)
{
}

std::shared_ptr<LppObject> LppArray::clone() const
{
    std::vector<LppVariant> newData = data;
    return std::make_shared<LppArray>(std::move(newData), dims);
}

std::string LppArray::toString() const
{
    return "Array";
}
