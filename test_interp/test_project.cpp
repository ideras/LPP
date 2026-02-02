#include "doctest.h"
#include "project_manager/lpp_project_parser.h"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("Parse Project File") {
    // Use system temp directory for the temporary project file
    fs::path tempPath = fs::temp_directory_path() / "test_project.lppprj";
    std::string filename = tempPath.string();
    
    std::ofstream out(filename);
    out << "Proyecto \"MiSistema\"\n";
    out << "    Version: \"1.0.0\"\n";
    out << "    Principal: \"main.lpp\"\n";
    out << "    Archivos\n";
    out << "        \"main.lpp\"\n";
    out << "        \"lib.lpp\"\n";
    out << "    Fin Archivos\n";
    out << "Fin Proyecto\n";
    out.close();

    LppProject project = LppProjectParser::parse(filename);

    CHECK(project.name == "MiSistema");
    CHECK(project.version == "1.0.0");
    CHECK(project.entryPoint == "main.lpp");
    CHECK(project.files.size() == 2);
    CHECK(project.files[0] == "main.lpp");
    CHECK(project.files[1] == "lib.lpp");

    fs::remove(filename);
}
