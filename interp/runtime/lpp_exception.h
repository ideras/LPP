#ifndef __LPP_EXCEPTION_H__
#define __LPP_EXCEPTION_H__

#include <string>
#include <exception>
#include "lpp_variant.h"

class LPPException : public std::exception
{
public:
    LPPException(int src_line, const std::string& msg);
    LPPException(int src_line, const std::string& filename, const std::string& msg);

    const char* what() const noexcept override {
        return msg.c_str();
    }

    std::string getMessage() const {
        return msg;
    }

    int getSrcLine() const {
        return src_line;
    }

    std::string getFilename() const {
        return filename;
    }

    void setFilename(const std::string& _filename) {
        filename = _filename;
    }

private:
    int src_line;
    std::string filename;
    std::string msg;
};

// Exception used for implementing return statements in the interpreter
// This is an acceptable use of exceptions for control flow in this context
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
