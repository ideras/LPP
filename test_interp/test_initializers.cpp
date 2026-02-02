#include <sstream>
#include "doctest.h"
#include "lpp_parser.h"
#include "lpp_lexer.h"
#include "lpp_interp.h"
#include "lpp_exception.h"

extern std::ostringstream oss;

TEST_CASE("Array Initializer") {
    std::string src = R"(
        Arreglo [3] de Entero arr
        Inicio
            arr <- Arreglo [3] de Entero { 10, 20, 30 }
            Escriba arr[1], arr[2], arr[3]
        Fin
    )";
    
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    
    LppInterp interp;
    oss.str(""); // Clear output
    REQUIRE_NOTHROW(interp.exec(prg.get()));
    REQUIRE(oss.str() == "102030");
}

TEST_CASE("Record Initializer Positional") {
    std::string src = R"(
        Registro Persona
            Entero id
            Cadena[20] nombre
        Fin Registro
        
        Persona p
        
        Inicio
            p <- Persona { 1, "Juan" }
            Escriba p.id, p.nombre
        Fin
    )";
    
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    
    LppInterp interp;
    oss.str("");
    REQUIRE_NOTHROW(interp.exec(prg.get()));
    REQUIRE(oss.str() == "1Juan");
}

TEST_CASE("Record Initializer Named") {
    std::string src = R"(
        Registro Persona
            Entero id
            Cadena[20] nombre
        Fin Registro
        
        Persona p
        
        Inicio
            p <- Persona { nombre: "Maria", id: 2 }
            Escriba p.id, p.nombre
        Fin
    )";
    
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    
    LppInterp interp;
    oss.str("");
    REQUIRE_NOTHROW(interp.exec(prg.get()));
    REQUIRE(oss.str() == "2Maria");
}

TEST_CASE("Nested Initializers") {
    std::string src = R"(
        Registro Punto
            Entero x, _y
        Fin Registro

        Arreglo [2] de Punto puntos

        Inicio
            puntos <- Arreglo [2] de Punto {
                Punto { x: 1, _y: 2 },
                Punto { 3, 4 }
            }
            Escriba puntos[1].x, puntos[1]._y, puntos[2].x, puntos[2]._y
        Fin
    )";
    
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    
    LppInterp interp;
    oss.str("");
    REQUIRE_NOTHROW(interp.exec(prg.get()));
    REQUIRE(oss.str() == "1234");
}

TEST_CASE("Array Initializer Inferred") {
    std::string src = R"(
        Arreglo [3] de Entero arr
        Inicio
            arr <- Arreglo { 10, 20, 30 }
            Escriba arr[1], arr[2], arr[3]
        Fin
    )";
    
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    
    LppInterp interp;
    oss.str("");
    REQUIRE_NOTHROW(interp.exec(prg.get()));
    REQUIRE(oss.str() == "102030");
}

TEST_CASE("Array Of Array Inferred") {
    std::string src = R"(
        Arreglo [2] de Arreglo [2] de Entero mat
        Inicio
            mat <- Arreglo { Arreglo { 1, 2 }, Arreglo { 3, 4 } }
            Escriba mat[1][1], mat[1][2], mat[2][1], mat[2][2]
        Fin
    )";
    
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    
    LppInterp interp;
    oss.str("");
    REQUIRE_NOTHROW(interp.exec(prg.get()));
    REQUIRE(oss.str() == "1234");
}

TEST_CASE("MultiDim Array Explicit") {
    std::string src = R"(
        Arreglo [2,2] de Entero mat
        Inicio
            mat <- Arreglo [2,2] de Entero { 1, 2, 3, 4 }
            Escriba mat[1,1], mat[1,2], mat[2,1], mat[2,2]
        Fin
    )";
    
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    
    LppInterp interp;
    oss.str("");
    REQUIRE_NOTHROW(interp.exec(prg.get()));
    REQUIRE(oss.str() == "1234");
}

TEST_CASE("MultiDim Array Inferred Type Mismatch") {
    std::string src = R"(
        Arreglo [2,2] de Entero mat
        Inicio
            mat <- Arreglo { 1, 2, 3, 4 }
        Fin
    )";
    
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    
    LppInterp interp;
    oss.str("");
    try {
        interp.exec(prg.get());
        REQUIRE(false); // Should throw
    } catch (const std::exception& e) {
        REQUIRE(std::string(e.what()).find("Tipos de datos no compatibles en asignacion") != std::string::npos);
    }
}

TEST_CASE("MultiDim Array Inferred Simplified") {
    std::string src = R"(
        Arreglo [2,2] de Entero mat
        Inicio
            mat <- Arreglo { {1, 2}, {3, 4} }
            Escriba mat[1,1], mat[1,2], mat[2,1], mat[2,2]
        Fin
    )";
    
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    
    LppInterp interp;
    oss.str("");
    REQUIRE_NOTHROW(interp.exec(prg.get()));
    REQUIRE(oss.str() == "1234");
}

TEST_CASE("Empty Inferred Array Failure") {
    std::string src = R"(
        Arreglo [2] de Entero arr
        Inicio
            arr <- Arreglo {}
        Fin
    )";
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    LppInterp interp;
    
    try {
        interp.exec(prg.get());
        REQUIRE(false);
    } catch (const LPPException& e) {
        REQUIRE(e.getMessage() == "No se puede inferir el tipo de un arreglo vacio");
    }
}

TEST_CASE("Empty Bare Array Failure") {
    std::string src = R"(
        Arreglo [2] de Entero arr
        Inicio
            arr <- Arreglo { {} }
        Fin
    )";
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    LppInterp interp;
    
    try {
        interp.exec(prg.get());
        REQUIRE(false);
    } catch (const LPPException& e) {
        REQUIRE(e.getMessage() == "No se puede inferir el tipo de un arreglo vacio");
    }
}

TEST_CASE("Inferred Array Type Mismatch Failure") {
    std::string src = R"(
        Arreglo [2] de Entero arr
        Inicio
            arr <- Arreglo { 1, "a" }
        Fin
    )";
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    LppInterp interp;
    
    try {
        interp.exec(prg.get());
        REQUIRE(false);
    } catch (const LPPException& e) {
        REQUIRE(e.getMessage() == "El tipo del elemento no coincide con el tipo del arreglo");
    }
}

TEST_CASE("Typed Array Type Mismatch Failure") {
    std::string src = R"(
        Arreglo [2] de Entero arr
        Inicio
            arr <- Arreglo [2] de Entero { 1, "a" }
        Fin
    )";
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    LppInterp interp;
    
    try {
        interp.exec(prg.get());
        REQUIRE(false);
    } catch (const LPPException& e) {
        REQUIRE(e.getMessage() == "El tipo del elemento no coincide con el tipo del arreglo");
    }
}

TEST_CASE("Typed Array Size Mismatch Failure") {
    std::string src = R"(
        Arreglo [2] de Entero arr
        Inicio
            arr <- Arreglo [2] de Entero { 1, 2, 3 }
        Fin
    )";
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    LppInterp interp;
    
    try {
        interp.exec(prg.get());
        REQUIRE(false);
    } catch (const LPPException& e) {
        REQUIRE(e.getMessage() == "Demasiados elementos en el inicializador del arreglo");
    }
}

TEST_CASE("Record Mixed Init Failure") {
    std::string src = R"(
        Registro P
            Entero a, b
        Fin Registro
        P p1
        Inicio
            p1 <- P { a: 1, 2 }
        Fin
    )";
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    LppInterp interp;
    
    try {
        interp.exec(prg.get());
        REQUIRE(false);
    } catch (const LPPException& e) {
        REQUIRE(e.getMessage() == "No se puede mezclar inicializacion posicional y nombrada");
    }
}

TEST_CASE("Record Invalid Field Failure") {
    std::string src = R"(
        Registro P
            Entero a
        Fin Registro
        P p1
        Inicio
            p1 <- P { b: 1 }
        Fin
    )";
    std::istringstream in(src);
    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();
    LppInterp interp;
    
    try {
        interp.exec(prg.get());
        REQUIRE(false);
    } catch (const LPPException& e) {
        REQUIRE(e.getMessage() == "El campo 'b' no existe en el registro 'P'");
    }
}
