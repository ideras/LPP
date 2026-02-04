#ifndef LPP_ARRAY_H
#define LPP_ARRAY_H

#include <vector>
#include "lpp_object.h"
#include "lpp_variant.h"

class LppArray : public LppObject
{
public:
    LppArray(std::vector<LppVariant> &&data, const std::vector<int> &dims);

    LppObjectKind kind() const override
    { return LppObjectKind::Array; }

    std::shared_ptr<LppObject> clone() const override;

    std::string toString() const override;

    const std::vector<int> &dimensions() const
    { return dims; }

    std::vector<LppVariant> &getData()
    { return data; }

    const std::vector<LppVariant> &getData() const
    { return data; }

private:
    std::vector<LppVariant> data;
    std::vector<int> dims;
};

#endif // LPP_ARRAY_H
