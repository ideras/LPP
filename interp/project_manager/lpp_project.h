#ifndef LPP_PROJECT_H
#define LPP_PROJECT_H

#include <string>
#include <vector>
#include <memory>
#include "lpp_ast.h"

struct ParsedFile
{
    std::string filename;
    Ast::NodeUPtr ast;

    ParsedFile(std::string name, Ast::NodeUPtr node)
        : filename(std::move(name)), ast(std::move(node))
    {}
};

struct LppProject
{
    std::string name;
    std::string version;
    std::string entryPoint; // "Principal"
    std::vector<std::string> files; // "Archivos"
    std::string projectDir; // Absolute path to project directory

    static LppProject fromSingleFile(const std::string& path);
};

#endif // LPP_PROJECT_H
