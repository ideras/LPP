#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING

#include <sstream>
#include "doctest.h"
#include "lpp_parser.h"
#include "lpp_lexer.h"
#include "lpp_interp.h"
#include "lpp_exception.h"

#include "lpp_sources.h"

extern std::ostringstream oss;

TEST_CASE("01 Hola Mundo") {
    std::istringstream in(hola_mundo_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == hola_mundo_eout);
}

TEST_CASE("02 Int Test") {
    std::istringstream in(int_test_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == int_test_eout);
}

TEST_CASE("03 Real Test") {
    std::istringstream in(real_test_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == real_test_eout);
}

TEST_CASE("04 Char Test") {
    std::istringstream in(char_test_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == char_test_eout);
}

TEST_CASE("05 Bool Test") {
    std::istringstream in(bool_test_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == bool_test_eout);
}

TEST_CASE("01 Int Int Add") {
    std::istringstream in(int_int_add_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == int_int_add_eout);
}

TEST_CASE("02 Int Int Sub") {
    std::istringstream in(int_int_sub_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == int_int_sub_eout);
}

TEST_CASE("03 Int Int Mult") {
    std::istringstream in(int_int_mult_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == int_int_mult_eout);
}

TEST_CASE("04 Int Int Div") {
    std::istringstream in(int_int_div_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == int_int_div_eout);
}

TEST_CASE("05 Int Int I Div") {
    std::istringstream in(int_int_i_div_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == int_int_i_div_eout);
}

TEST_CASE("06 Int Int Mod") {
    std::istringstream in(int_int_mod_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == int_int_mod_eout);
}

TEST_CASE("07 Int Int Pow") {
    std::istringstream in(int_int_pow_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == int_int_pow_eout);
}

TEST_CASE("08 Real Real Add") {
    std::istringstream in(real_real_add_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == real_real_add_eout);
}

TEST_CASE("09 Real Real Sub") {
    std::istringstream in(real_real_sub_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == real_real_sub_eout);
}

TEST_CASE("10 Real Real Mult") {
    std::istringstream in(real_real_mult_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == real_real_mult_eout);
}

TEST_CASE("11 Real Real Div") {
    std::istringstream in(real_real_div_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == real_real_div_eout);
}

TEST_CASE("12 Real Real I Div") {
    std::istringstream in(real_real_i_div_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == real_real_i_div_eout);
}

TEST_CASE("13 Real Real Mod") {
    std::istringstream in(real_real_mod_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == real_real_mod_eout);
}

TEST_CASE("14 Real Real Pow") {
    std::istringstream in(real_real_pow_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == real_real_pow_eout);
}

TEST_CASE("15 Add Int Real") {
    std::istringstream in(add_int_real_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == add_int_real_eout);
}

TEST_CASE("16 Add Real Int") {
    std::istringstream in(add_real_int_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == add_real_int_eout);
}

TEST_CASE("17 Bool Ops") {
    std::istringstream in(bool_ops_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == bool_ops_eout);
}

TEST_CASE("18 Unary Ops") {
    std::istringstream in(unary_ops_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == unary_ops_eout);
}

TEST_CASE("01 Test String1") {
    std::istringstream in(test_string1_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_string1_eout);
}

TEST_CASE("02 Test String2") {
    std::istringstream in(test_string2_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_string2_eout);
}

TEST_CASE("03 Test String3") {
    std::istringstream in(test_string3_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_string3_eout);
}

TEST_CASE("04 Test String4") {
    std::istringstream in(test_string4_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_string4_eout);
}

TEST_CASE("05 Concat String") {
    std::istringstream in(concat_string_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == concat_string_eout);
}

TEST_CASE("06 Concat String Char") {
    std::istringstream in(concat_string_char_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == concat_string_char_eout);
}

TEST_CASE("01 Test Array1 D Int") {
    std::istringstream in(test_array1_d_int_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_array1_d_int_eout);
}

TEST_CASE("02 Test Array1 D String") {
    std::istringstream in(test_array1_d_string_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_array1_d_string_eout);
}

TEST_CASE("03 Test Array2 D Int") {
    std::istringstream in(test_array2_d_int_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_array2_d_int_eout);
}

TEST_CASE("04 Test Array2 D String") {
    std::istringstream in(test_array2_d_string_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_array2_d_string_eout);
}

TEST_CASE("05 Test Array3 D Int") {
    std::istringstream in(test_array3_d_int_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_array3_d_int_eout);
}

TEST_CASE("06 Test Array3 D String") {
    std::istringstream in(test_array3_d_string_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_array3_d_string_eout);
}

TEST_CASE("07 Test Array Of Array Int") {
    std::istringstream in(test_array_of_array_int_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_array_of_array_int_eout);
}

TEST_CASE("08 Test Array Of Array Of Array Int") {
    std::istringstream in(test_array_of_array_of_array_int_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_array_of_array_of_array_int_eout);
}

TEST_CASE("01 Test Rel Int") {
    std::istringstream in(test_rel_int_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_rel_int_eout);
}

TEST_CASE("02 Test Rel Real") {
    std::istringstream in(test_rel_real_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_rel_real_eout);
}

TEST_CASE("01 Test Mientras") {
    std::istringstream in(test_mientras_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_mientras_eout);
}

TEST_CASE("02 Test Repita") {
    std::istringstream in(test_repita_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_repita_eout);
}

TEST_CASE("03 Test Para") {
    std::istringstream in(test_para_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_para_eout);
}

TEST_CASE("04 Test Si") {
    std::istringstream in(test_si_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_si_eout);
}

TEST_CASE("05 Test Si Anidado") {
    std::istringstream in(test_si_anidado_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_si_anidado_eout);
}

TEST_CASE("06 Test Caso1") {
    std::istringstream in(test_caso1_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_caso1_eout);
}

TEST_CASE("07 Test Caso2") {
    std::istringstream in(test_caso2_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_caso2_eout);
}

TEST_CASE("08 Test Caso3") {
    std::istringstream in(test_caso3_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_caso3_eout);
}

TEST_CASE("09 Test Caso4") {
    std::istringstream in(test_caso4_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_caso4_eout);
}

TEST_CASE("10 Test Caso5") {
    std::istringstream in(test_caso5_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_caso5_eout);
}

TEST_CASE("11 Test Caso6") {
    std::istringstream in(test_caso6_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_caso6_eout);
}

TEST_CASE("12 Test Caso7") {
    std::istringstream in(test_caso7_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_caso7_eout);
}

TEST_CASE("13 Test Caso8") {
    std::istringstream in(test_caso8_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_caso8_eout);
}

TEST_CASE("14 Test Lea") {
    std::istringstream in(test_lea_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_lea_eout);
}

TEST_CASE("01 Test Aleatorio") {
    std::istringstream in(test_aleatorio_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    std::string output = oss.str();
    int count = 0;
    std::string::size_type pos = output.find("0.", 0);
    while (pos != std::string::npos) {
        count ++;
        pos = output.find("0.", pos + 1);
    }

    REQUIRE(count == 8);
}

TEST_CASE("02 Test Caracter Ascii") {
    std::istringstream in(test_caracter_ascii_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_caracter_ascii_eout);
}

TEST_CASE("03 Test Valor Ascii") {
    std::istringstream in(test_valor_ascii_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_valor_ascii_eout);
}

TEST_CASE("04 Test Entero A Cadena") {
    std::istringstream in(test_entero_a_cadena_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_entero_a_cadena_eout);
}

TEST_CASE("05 Test Longitud Cadena") {
    std::istringstream in(test_longitud_cadena_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_longitud_cadena_eout);
}

TEST_CASE("06 Test Real A Cadena") {
    std::istringstream in(test_real_a_cadena_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_real_a_cadena_eout);
}

TEST_CASE("01 Test Simple Record") {
    std::istringstream in(test_simple_record_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_simple_record_eout);
}

TEST_CASE("02 Test Mixed Record") {
    std::istringstream in(test_mixed_record_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_mixed_record_eout);
}

TEST_CASE("03 Test Mixed Record String") {
    std::istringstream in(test_mixed_record_string_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_mixed_record_string_eout);
}

TEST_CASE("04 Test Record Of Array1 D Int") {
    std::istringstream in(test_record_of_array1_d_int_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_record_of_array1_d_int_eout);
}

TEST_CASE("05 Test Record Of Array2 D Int") {
    std::istringstream in(test_record_of_array2_d_int_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_record_of_array2_d_int_eout);
}

TEST_CASE("06 Test Record Of Record1") {
    std::istringstream in(test_record_of_record1_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_record_of_record1_eout);
}

TEST_CASE("07 Test Record Of Array Of Array Int") {
    std::istringstream in(test_record_of_array_of_array_int_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_record_of_array_of_array_int_eout);
}

TEST_CASE("08 Test Mixed Subtype Reg Array") {
    std::istringstream in(test_mixed_subtype_reg_array_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_mixed_subtype_reg_array_eout);
}

TEST_CASE("01 Test Subprg1") {
    std::istringstream in(test_subprg1_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg1_eout);
}

TEST_CASE("02 Test Subprg2") {
    std::istringstream in(test_subprg2_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg2_eout);
}

TEST_CASE("03 Test Subprg3") {
    std::istringstream in(test_subprg3_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg3_eout);
}

TEST_CASE("04 Test Subprg4") {
    std::istringstream in(test_subprg4_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg4_eout);
}

TEST_CASE("05 Test Subprg5") {
    std::istringstream in(test_subprg5_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg5_eout);
}

TEST_CASE("06 Test Subprg6") {
    std::istringstream in(test_subprg6_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg6_eout);
}

TEST_CASE("07 Test Subprg7") {
    std::istringstream in(test_subprg7_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg7_eout);
}

TEST_CASE("08 Test Subprg8") {
    std::istringstream in(test_subprg8_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg8_eout);
}

TEST_CASE("09 Test Subprg9") {
    std::istringstream in(test_subprg9_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg9_eout);
}

TEST_CASE("10 Test Subprg10") {
    std::istringstream in(test_subprg10_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg10_eout);
}

TEST_CASE("11 Test Subprg11") {
    std::istringstream in(test_subprg11_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg11_eout);
}

TEST_CASE("12 Test Subprg12") {
    std::istringstream in(test_subprg12_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg12_eout);
}

TEST_CASE("13 Test Subprg13") {
    std::istringstream in(test_subprg13_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg13_eout);
}

TEST_CASE("14 Test Subprg14") {
    std::istringstream in(test_subprg14_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg14_eout);
}

TEST_CASE("15 Test Subprg15") {
    std::istringstream in(test_subprg15_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg15_eout);
}

TEST_CASE("16 Test Subprg16") {
    std::istringstream in(test_subprg16_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg16_eout);
}

TEST_CASE("17 Test Subprg17") {
    std::istringstream in(test_subprg17_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg17_eout);
}

TEST_CASE("18 Test Subprg18") {
    std::istringstream in(test_subprg18_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == test_subprg18_eout);
}

TEST_CASE("19_gcd") {
    std::istringstream in(gcd_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == gcd_eout);
}

TEST_CASE("20_fibonacci") {
    std::istringstream in(fibonacci_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;

    REQUIRE_NOTHROW(interp.exec(prg.get()));

    REQUIRE(oss.str() == fibonacci_eout);
}

TEST_CASE("21 Test Subprg With Error") {
    std::istringstream in(test_subprg_with_error_src);

    LppLexer lexer(in);
    LppParser parser(lexer);
    Ast::NodeUPtr prg = parser.parse();

    LppInterp interp;
    
    try {
        interp.exec(prg.get());
        REQUIRE(false);
    } catch (const LPPException& ex) {
        std::string message = "Linea " + std::to_string(ex.getSrcLine()) + ": " + ex.getMessage();
        REQUIRE( message  == test_subprg_with_error_eout);
    }
}
