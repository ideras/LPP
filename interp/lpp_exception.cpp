#include "lpp_exception.h"


LPPException::LPPException(int src_line, const std::string& msg)
    : src_line(src_line),
      filename(""),
      msg(msg)
{
}

LPPException::LPPException(int src_line, const std::string& filename, const std::string& msg)
    : src_line(src_line),
      filename(filename),
      msg(msg)
{
}

