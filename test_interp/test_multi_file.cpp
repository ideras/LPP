#include "doctest.h"
#include "lpp_interp.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include "project_manager/lpp_project_parser.h"

namespace fs = std::filesystem;
extern std::ostringstream oss;

TEST_CASE("Multi-file Project Execution") {
    fs::path tempDir = fs::temp_directory_path() / "lpp_multi_test";
    fs::create_directories(tempDir);
    
    // lib.lpp
    std::ofstream lib(tempDir / "lib.lpp");
    lib << "Funcion Suma(Entero a, Entero b) : Entero\n"
        << "Inicio\n"
        << "    Retorne a + b\n"
        << "Fin\n";
    lib.close();
    
    // main.lpp
    std::ofstream main(tempDir / "main.lpp");
    main << "Inicio\n"
         << "    Escriba Suma(5, 10)\n"
         << "Fin\n";
    main.close();
    
    // test.lppprj
    std::ofstream prj(tempDir / "test.lppprj");
    prj << "Proyecto \"TestMulti\"\n"
        << "    Version: \"1.0.0\"\n"
        << "    Principal: \"main.lpp\"\n"
        << "    Archivos\n"
        << "        \"lib.lpp\"\n"
        << "        \"main.lpp\"\n"
        << "    Fin Archivos\n"
        << "Fin Proyecto\n";
    prj.close();
    
    LppInterp interp;
    oss.str("");
    
    LppProject proj = LppProjectParser::parse((tempDir / "test.lppprj").string());
    REQUIRE_NOTHROW(interp.execute(proj));
    
    CHECK(oss.str() == "15");
    
    fs::remove_all(tempDir);
}
