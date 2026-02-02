#include "lpp_project.h"
#include <filesystem>

namespace fs = std::filesystem;

LppProject LppProject::fromSingleFile(const std::string& path) {
    fs::path p(path);
    fs::path absPath = fs::absolute(p);
    
    LppProject proj;
    proj.name = p.stem().string();
    proj.version = "1.0.0";
    proj.projectDir = absPath.parent_path().string();
    proj.entryPoint = absPath.filename().string();
    proj.files.push_back(proj.entryPoint);
    return proj;
}
