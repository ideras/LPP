#ifndef LPP_PROJECT_PARSER_H
#define LPP_PROJECT_PARSER_H

#include <string>
#include <fstream>
#include "lpp_project.h"

class LppProjectParser
{
public:
    LppProjectParser() = delete;

    static LppProject parse(const std::string& filePath);

private:
    static void skipWhitespace(std::istream& in);
    static std::string readString(std::istream& in);
    static std::string readIdentifier(std::istream& in);
    static void expect(std::istream& in, const std::string& expected);
};

#endif // LPP_PROJECT_PARSER_H
