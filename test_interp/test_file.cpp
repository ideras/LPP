#include <unordered_map>
#include <string>
#include <sstream>
#include "doctest.h"
#include "lpp_parser.h"
#include "lpp_lexer.h"
#include "lpp_interp.h"
#include "lpp_exception.h"
#include "serializer_helper.h"

extern std::unordered_map<std::string, std::string> file_map;
extern std::ostringstream oss;

const char *bin_file_01_src =
R"(archivo de entero f1

inicio
    abrir "test.bin" como f1
    cerrar f1
    abrir "test.bin" como f1 para lectura
    cerrar f1
    abrir "test.bin" como f1 para lectura, escritura
    cerrar f1
final
)";

const char *bin_file_02_src =
R"(archivo de entero f1

inicio
    abrir "test.bin" como f1 para escritura
    escribir f1, 897
    escribir f1, 346
    escribir f1, 3289
    cerrar f1
final)";

const char *bin_file_03_src =
R"(archivo de entero f1
entero a, b, c

inicio
    abrir "test.bin" como f1 para lectura
    leer f1, a
    leer f1, b
    leer f1, c
    cerrar f1
    Escriba a, b, c
final)";

const char *bin_file_04_src =
R"(Archivo de Arreglo [10] de Entero f1
Arreglo [10] de Entero arr

Inicio
    arr[1] <- 83
    arr[2] <- 89
    arr[3] <- 60
    arr[4] <- 49
    arr[5] <- 34
    arr[6] <- 80
    arr[7] <- 25
    arr[8] <- 66
    arr[9] <- 42
    arr[10] <- 22
    Abrir "test.bin" Como f1 Para Escritura
    Escribir f1, arr
    Cerrar f1
Final)";

const char *bin_file_05_src =
R"(Registro MyReg
    Entero x
    Real r
    Arreglo [10] de Entero arr
    Cadena [10] str
Fin Registro
Archivo de MyReg f1
MyReg r

Inicio
    r.x <- 9897
    r.r <- 3.14159
    r.str <- "ABCDEF"
    r.arr[1] <- 83
    r.arr[2] <- 89
    r.arr[3] <- 60
    r.arr[4] <- 49
    r.arr[5] <- 34
    r.arr[6] <- 80
    r.arr[7] <- 25
    r.arr[8] <- 66
    r.arr[9] <- 42
    r.arr[10] <- 22
    Abrir "test.bin" Como f1 Para Escritura
    Escribir f1, r
    Cerrar f1
Final)";

const char *bin_file_06_src =
R"(
Tipo MyArr Es Arreglo[5] de Arreglo[2] de Entero
Archivo de MyArr f1
MyArr arr

Inicio
    arr[1][1] <- 83
    arr[1][2] <- 89
    arr[2][1] <- 60
    arr[2][2] <- 49
    arr[3][1] <- 34
    arr[3][2] <- 80
    arr[4][1] <- 25
    arr[4][2] <- 66
    arr[5][1] <- 42
    arr[5][2] <- 22
    Abrir "test.bin" Como f1 Para Escritura
    Escribir f1, arr
    Cerrar f1
Final
)";

const char *bin_file_07_src =
R"(
Registro MyRec
	Entero campo1
	Real campo2
	Arreglo[5] de Arreglo[2] de Entero campo3
	Booleano campo4
Fin Registro

Archivo de MyRec f1
MyRec r

Inicio
	r.campo1 <- 9897
	r.campo2 <- 3.14159
    r.campo3[1][1] <- 83
    r.campo3[1][2] <- 89
    r.campo3[2][1] <- 60
    r.campo3[2][2] <- 49
    r.campo3[3][1] <- 34
    r.campo3[3][2] <- 80
    r.campo3[4][1] <- 25
    r.campo3[4][2] <- 66
    r.campo3[5][1] <- 42
    r.campo3[5][2] <- 22
	r.campo4 <- Falso

    Abrir "test.bin" Como f1 Para Escritura
    Escribir f1, r
    Cerrar f1
Final
)";

const char *text_file_01_src =
R"(archivo secuencial f1

inicio
    abrir "test.txt" como f1
    cerrar f1
    abrir "test.txt" como f1 para lectura
    cerrar f1
    abrir "test.txt" como f1 para lectura, escritura
    cerrar f1
final)";

const char *text_file_02_src =
R"(archivo secuencial f1

inicio
    abrir "test.txt" como f1 para escritura
    escribir f1, 897
    escribir f1, 346
    escribir f1, 3289
    cerrar f1
final)";

const char *text_file_03_src =
R"(archivo secuencial f1
entero a, b, c

inicio
    abrir "test.txt" como f1 para lectura
    leer f1, a
    leer f1, b
    leer f1, c
    cerrar f1
    Escriba a, b, c
final)";

const char *text_file_04_src =
R"(Archivo Secuencial f1
Arreglo [10] de Entero arr

Inicio
    arr[1] <- 83
    arr[2] <- 89
    arr[3] <- 60
    arr[4] <- 49
    arr[5] <- 34
    arr[6] <- 80
    arr[7] <- 25
    arr[8] <- 66
    arr[9] <- 42
    arr[10] <- 22
    Abrir "test.txt" Como f1 Para Escritura
    Escribir f1, arr
    Cerrar f1
Final)";

const char *text_file_05_src =
R"(Registro MyReg
    Entero x
    Real r
    Arreglo [10] de Entero arr
    Cadena str
Fin Registro
Archivo Secuencial f1
MyReg r
Inicio
    r.x <- 897
    r.r <- 3.14159
    r.str <- "Esta es una cadena"
    r.arr[1] <- 83
    r.arr[2] <- 89
    r.arr[3] <- 60
    r.arr[4] <- 49
    r.arr[5] <- 34
    r.arr[6] <- 80
    r.arr[7] <- 25
    r.arr[8] <- 66
    r.arr[9] <- 42
    r.arr[10] <- 22
    Abrir "test.txt" Como f1 Para Escritura
    Escribir f1, r
    Cerrar f1
Final)";

TEST_CASE("Binary file of Integer 01") {
    std::istringstream in(bin_file_01_src);
    
    LppLexer lexer(in);
    LppParser parser(lexer);
    
    Ast::NodeUPtr prg;
    REQUIRE_NOTHROW(prg = parser.parse());

    LppInterp interp;
    try {
        file_map["test.bin"] = "";
        interp.exec(prg.get());
        file_map.clear();
    } catch (const LPPException& ex) {
        std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
        REQUIRE(false);
    }
}

TEST_CASE("Binary file of Integer 02") {
    std::istringstream in(bin_file_02_src);
    
    LppLexer lexer(in);
    LppParser parser(lexer);
    
    Ast::NodeUPtr prg;
    REQUIRE_NOTHROW(prg = parser.parse());

    LppInterp interp;
    try {
        file_map["test.bin"] = "";
        interp.exec(prg.get());

        std::string content = file_map["test.bin"]; 
        CHECK(toHexString(content) == "810300005a010000d90c0000");
        file_map.clear();
    } catch (const LPPException& ex) {
        std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
        REQUIRE(false);
    }
}

TEST_CASE("Binary file of Integer 03") {
    std::istringstream in(bin_file_03_src);
    
    LppLexer lexer(in);
    LppParser parser(lexer);
    
    Ast::NodeUPtr prg;
    REQUIRE_NOTHROW(prg = parser.parse());

    LppInterp interp;
    try {
        file_map["test.bin"] = std::string("\x81\x03\x00\x00\x5a\x01\x00\x00\xd9\x0c\x00\x00", sizeof(Lpp::Int)*3);
        interp.exec(prg.get());
        file_map.clear();

        REQUIRE( oss.str() == "8973463289");
    } catch (const LPPException& ex) {
        std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
        REQUIRE(false);
    }
}

TEST_CASE("Binary file of Array(Integer) 04") {
    std::istringstream in(bin_file_04_src);
    
    LppLexer lexer(in);
    LppParser parser(lexer);
    
    Ast::NodeUPtr prg;
    REQUIRE_NOTHROW(prg = parser.parse());

    LppInterp interp;
    try {
        file_map["test.bin"] = "";
        interp.exec(prg.get());
        
        std::string content = file_map["test.bin"]; 
        CHECK(toHexString(content) == "53000000590000003c00000031000000220000005000000019000000420000002a00000016000000");
        file_map.clear();
    } catch (const LPPException& ex) {
        std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
        REQUIRE(false);
    }
}

TEST_CASE("Binary file of Record 05") {
    std::istringstream in(bin_file_05_src);
    
    LppLexer lexer(in);
    LppParser parser(lexer);
    
    Ast::NodeUPtr prg;
    REQUIRE_NOTHROW(prg = parser.parse());

    LppInterp interp;
    try {
        file_map["test.bin"] = "";
        interp.exec(prg.get());
        
        std::string content = file_map["test.bin"]; 
        CHECK(toHexString(content) == "a92600006e861bf0f9210940"
                                      "53000000590000003c000000"
                                      "310000002200000050000000"
                                      "19000000420000002a000000"
                                      "1600000041424344454600000000");
        file_map.clear();
    } catch (const LPPException& ex) {
        std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
        REQUIRE(false);
    }
}

TEST_CASE("Binary file of Array(Integer) 06") {
    std::istringstream in(bin_file_06_src);
    
    LppLexer lexer(in);
    LppParser parser(lexer);
    
    Ast::NodeUPtr prg;
    REQUIRE_NOTHROW(prg = parser.parse());

    LppInterp interp;
    try {
        file_map["test.bin"] = "";
        interp.exec(prg.get());
        
        std::string content = file_map["test.bin"]; 
        CHECK(toHexString(content) == "53000000590000003c00000031000000220000005000000019000000420000002a00000016000000");
        file_map.clear();
    } catch (const LPPException& ex) {
        std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
        REQUIRE(false);
    }
}

TEST_CASE("Binary file of Record with Array 07") {
    std::istringstream in(bin_file_07_src);
    
    LppLexer lexer(in);
    LppParser parser(lexer);
    
    Ast::NodeUPtr prg;
    REQUIRE_NOTHROW(prg = parser.parse());

    LppInterp interp;
    try {
        file_map["test.bin"] = "";
        interp.exec(prg.get());
        
        std::string content = file_map["test.bin"]; 
        CHECK(toHexString(content) == "a9260000"
                                      "6e861bf0f9210940"
                                      "53000000590000003c00000031000000220000005000000019000000420000002a00000016000000"
                                      "00");
        file_map.clear();
    } catch (const LPPException& ex) {
        std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
        REQUIRE(false);
    }
}

TEST_CASE("Text file 01") {
    std::istringstream in(text_file_01_src);
    
    LppLexer lexer(in);
    LppParser parser(lexer);
    
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    try {
        file_map.clear();
        file_map["test.txt"] = "";
        interp.exec(prg.get());
    } catch (const LPPException& ex) {
        std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
        REQUIRE(false);
    }
}

TEST_CASE("Text file 02") {
    std::istringstream in(text_file_02_src);
    
    LppLexer lexer(in);
    LppParser parser(lexer);
    
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    try {
        file_map.clear();
        file_map["test.txt"] = "";
        interp.exec(prg.get());
        CHECK(file_map["test.txt"] == "897\n346\n3289\n");
    } catch (const LPPException& ex) {
        std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
        REQUIRE(false);
    }
}

TEST_CASE("Text file 03") {
    std::istringstream in(text_file_03_src);
    
    LppLexer lexer(in);
    LppParser parser(lexer);
    
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    try {
        file_map["test.txt"] = "897\n346\n3289\n";
        interp.exec(prg.get());
        REQUIRE( oss.str() == "8973463289");
    } catch (const LPPException& ex) {
        std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
        REQUIRE(false);
    }
}

TEST_CASE("Text file 04") {
    std::istringstream in(text_file_04_src);
    
    LppLexer lexer(in);
    LppParser parser(lexer);
    
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    try {
        file_map.clear();
        file_map["test.txt"] = "";
        interp.exec(prg.get());
        CHECK(file_map["test.txt"] == "[ 83, 89, 60, 49, 34, 80, 25, 66, 42, 22 ]\n");
    } catch (const LPPException& ex) {
        std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
        REQUIRE(false);
    }
}

TEST_CASE("Text file 05") {
    std::istringstream in(text_file_05_src);
    
    LppLexer lexer(in);
    LppParser parser(lexer);
    
    Ast::NodeUPtr prg;
    try {
        prg = parser.parse();
    } catch (const LPPException& ex) {
        std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
        REQUIRE(false);
    }

    LppInterp interp;

    try {
        file_map.clear();
        file_map["test.txt"] = "";
        interp.exec(prg.get());
        CHECK(file_map["test.txt"] == "{ 897, 3.14159, [ 83, 89, 60, 49, 34, 80, 25, 66, 42, 22 ], \"Esta es una cadena\" }\n");
    } catch (const LPPException& ex) {
        std::cerr << "Linea " << ex.getSrcLine() << ": " << ex.getMessage() << '\n';
        REQUIRE(false);
    }
}