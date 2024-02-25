#ifndef __LPP_EXCEPTION_H__
#define __LPP_EXCEPTION_H__

#include <string>
#include "lpp_variant.h"

class LPPException
{
public:
    LPPException(int src_line, const std::string& msg);

    std::string getMessage() const {
        return msg;
    }

    int getSrcLine() const {
        return src_line;
    }

private:
    int src_line;
    std::string msg;
};

class ReturnException
{
public:
    ReturnException(const LppVariant& val)
      : value(val)
    {}

    const LppVariant& getValue() const
    { return value; }

private:
    LppVariant value;
};

#endif // __LPP_EXCEPTION_H__
