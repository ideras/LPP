#ifndef LPP_RECORD_H
#define LPP_RECORD_H

#include <vector>
#include "lpp_object.h"
#include "lpp_variant.h"

class LppRecord : public LppObject
{
public:
    LppRecord(std::vector<LppVariant> &&fields);

    LppObjectKind kind() const override
    { return LppObjectKind::Record; }

    std::shared_ptr<LppObject> clone() const override;

    std::string toString() const override;

    std::vector<LppVariant> &getFields()
    { return fields; }

    const std::vector<LppVariant> &getFields() const
    { return fields; }

private:
    std::vector<LppVariant> fields;
};

#endif // LPP_RECORD_H
