#include "lpp_record.h"

LppRecord::LppRecord(std::vector<LppVariant> &&fields)
    : fields(std::move(fields))
{}

std::shared_ptr<LppObject> LppRecord::clone() const
{
    std::vector<LppVariant> newFields = fields;
    return std::make_shared<LppRecord>(std::move(newFields));
}

std::string LppRecord::toString() const
{
    return "Record";
}
