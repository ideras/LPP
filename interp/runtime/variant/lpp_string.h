#ifndef LPP_STRING_H
#define LPP_STRING_H

#include <string>
#include "lpp_object.h"

class LppString : public LppObject
{
public:
    LppString(const std::string &val): value(val)
    {}

    LppObjectKind kind() const override
    { return LppObjectKind::String; }

    std::shared_ptr<LppObject> clone() const override
    { return std::make_shared<LppString>(value); }

    std::string toString() const override
    { return value; }

    std::string &get()
    { return value; }

    const std::string &get() const
    { return value; }

private:
    std::string value;
};

#endif // LPP_STRING_H
