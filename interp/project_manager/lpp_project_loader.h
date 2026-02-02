#ifndef LPP_PROJECT_LOADER_H
#define LPP_PROJECT_LOADER_H

#include <vector>
#include <string>
#include "lpp_project.h"

class LppProjectLoader
{
public:
    LppProjectLoader() = delete;

    static std::vector<ParsedFile> load(const LppProject& project);
};

#endif // LPP_PROJECT_LOADER_H
