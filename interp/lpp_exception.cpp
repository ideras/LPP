#include "lpp_exception.h"


LPPException::LPPException(int src_line, const std::string& msg)
    : src_line(src_line),
      msg(msg)
{
}

