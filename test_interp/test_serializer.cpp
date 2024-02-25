#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "doctest.h"
#include "lpp_variant.h"
#include "lpp_serializer.h"
#include "lpp_type_info.h"
#include "serializer_helper.h"

TEST_CASE("01 LPP Serializer toString")
{
    LppVariant v1(9897);
    LppVariant v2(3.14159);
    LppVariant v3(true);
    LppVariant v4('A');
    LppVariant v5(std::string("This is a \"string of characters"));

    CHECK(LppSerializer::toString(v1) == "9897");
    CHECK(LppSerializer::toString(v2) == "3.14159");
    CHECK(LppSerializer::toString(v3) == "Verdadero");
    CHECK(LppSerializer::toString(v4) == "'A'");
    CHECK(LppSerializer::toString(v5) == "\"This is a \\\"string of characters\"");
}

TEST_CASE("02 LPP Serializer toString")
{
    TypeInfoSPtr arrti = TypeInfo::Array({10}, TypeInfo::Int);
    LppVariant varr;

    varr.initValue(arrti.get());
    std::vector<LppVariant>& arr = varr.arrayRef();
    arr[0] = 83;
    arr[1] = 89;
    arr[2] = 60;
    arr[3] = 49;
    arr[4] = 34;
    arr[5] = 80;
    arr[6] = 25;
    arr[7] = 66;
    arr[8] = 42;
    arr[9] = 22;

    
    CHECK(LppSerializer::toString(varr) == "[ 83, 89, 60, 49, 34, 80, 25, 66, 42, 22 ]");
}

TEST_CASE("03 LPP Serializer toString")
{
    TypeInfoSPtr recti = RecordTypeInfo::createShared("MyRecord", 
                                { {"Campo1", TypeInfo::Int},
                                  {"Campo2", TypeInfo::Real},
                                  {"Campo3", TypeInfo::Bool},
                                  {"Campo4", TypeInfo::Char},
                                  {"Campo5", TypeInfo::String(0)}  });
    LppVariant rec;

    rec.initValue(recti.get());
    std::vector<LppVariant>& arr = rec.arrayRef();

    arr[0] = 9897;
    arr[1] = 3.14159;
    arr[2] = true;
    arr[3] = 'A';
    arr[4] = std::string("This is a string with quotes \"embedded\"");
    
    CHECK(LppSerializer::toString(rec) == "{ 9897, 3.14159, Verdadero, 'A', \"This is a string with quotes \\\"embedded\\\"\" }");
}

TEST_CASE("04 LPP Serializer toString")
{
    TypeInfoSPtr arrti = TypeInfo::Array({5}, TypeInfo::Array({2}, TypeInfo::Int));
    LppVariant varr;

    varr.initValue(arrti.get());
    std::vector<LppVariant>& arr = varr.arrayRef();
    arr[0].arrayRef()[0] = 83;
    arr[0].arrayRef()[1] = 89;
    arr[1].arrayRef()[0] = 60;
    arr[1].arrayRef()[1] = 49;
    arr[2].arrayRef()[0] = 34;
    arr[2].arrayRef()[1] = 80;
    arr[3].arrayRef()[0] = 25;
    arr[3].arrayRef()[1] = 66;
    arr[4].arrayRef()[0] = 42;
    arr[4].arrayRef()[1] = 22;
    
    CHECK(LppSerializer::toString(varr) == "[ [ 83, 89 ], [ 60, 49 ], [ 34, 80 ], [ 25, 66 ], [ 42, 22 ] ]");
}

TEST_CASE("05 LPP Serializer toString")
{
    TypeInfoSPtr recti = RecordTypeInfo::createShared("MyRecord", 
                                { {"Campo1", TypeInfo::Int},
                                  {"Campo2", TypeInfo::Real},
                                  {"Campo3", TypeInfo::Array({5}, TypeInfo::Array({2}, TypeInfo::Int))},
                                  {"Campo4", TypeInfo::Bool}  });
    LppVariant rec;

    rec.initValue(recti.get());
    std::vector<LppVariant>& arr = rec.arrayRef();

    arr[0] = 9897;
    arr[1] = 3.14159;
    arr[2].arrayRef()[0].arrayRef()[0] = 83;
    arr[2].arrayRef()[0].arrayRef()[1] = 89;
    arr[2].arrayRef()[1].arrayRef()[0] = 60;
    arr[2].arrayRef()[1].arrayRef()[1] = 49;
    arr[2].arrayRef()[2].arrayRef()[0] = 34;
    arr[2].arrayRef()[2].arrayRef()[1] = 80;
    arr[2].arrayRef()[3].arrayRef()[0] = 25;
    arr[2].arrayRef()[3].arrayRef()[1] = 66;
    arr[2].arrayRef()[4].arrayRef()[0] = 42;
    arr[2].arrayRef()[4].arrayRef()[1] = 22;
    arr[3] = false;

    CHECK(LppSerializer::toString(rec) == "{ 9897, 3.14159, [ [ 83, 89 ], [ 60, 49 ], [ 34, 80 ], [ 25, 66 ], [ 42, 22 ] ], Falso }");
}

TEST_CASE("01 LPP Serializer fromString")
{
    LppVariant v1 = LppSerializer::fromString("9897");
    LppVariant v2 = LppSerializer::fromString("3.14159");
    LppVariant v3 = LppSerializer::fromString("Verdadero");
    LppVariant v4 = LppSerializer::fromString("'A'");
    LppVariant v5 = LppSerializer::fromString("\"This is a \\\"string of characters\"");

    REQUIRE(v1.isInt());
    CHECK(v1.toInt() == 9897);
    REQUIRE(v2.isReal());
    CHECK(v2.toReal() == 3.14159);
    REQUIRE(v3.isBool());
    CHECK(v3.toBool());
    REQUIRE(v4.isChar());
    CHECK(v4.toChar() == 'A');
    REQUIRE(v5.isString());
    CHECK(v5.stringRef() == "This is a \"string of characters");
}

TEST_CASE("02 LPP Serializer fromString")
{
    LppVariant varr = LppSerializer::fromString("[ 83, 89, 60, 49, 34, 80, 25, 66, 42, 22 ]");

    REQUIRE(varr.isArray());

    std::vector<LppVariant>& arr = varr.arrayRef();
    REQUIRE(arr.size() == 10);
    
    CHECK(arr[0].isInt());
    CHECK(arr[1].isInt());
    CHECK(arr[2].isInt());
    CHECK(arr[3].isInt());
    CHECK(arr[4].isInt());
    CHECK(arr[5].isInt());
    CHECK(arr[6].isInt());
    CHECK(arr[7].isInt());
    CHECK(arr[8].isInt());
    CHECK(arr[9].isInt());
    CHECK(arr[0].toInt() == 83);
    CHECK(arr[1].toInt() == 89);
    CHECK(arr[2].toInt() == 60);
    CHECK(arr[3].toInt() == 49);
    CHECK(arr[4].toInt() == 34);
    CHECK(arr[5].toInt() == 80);
    CHECK(arr[6].toInt() == 25);
    CHECK(arr[7].toInt() == 66);
    CHECK(arr[8].toInt() == 42);
    CHECK(arr[9].toInt() == 22);
}

TEST_CASE("03 LPP Serializer fromString")
{
    LppVariant rec = LppSerializer::fromString("{ 9897, 3.14159, Verdadero, 'A', \"This is a string with quotes \\\"embedded\\\"\" }");

    REQUIRE(rec.isRecord());

    std::vector<LppVariant>& arr = rec.arrayRef();
    REQUIRE(arr.size() == 5);

    CHECK(arr[0].isInt());
    CHECK(arr[1].isReal());
    CHECK(arr[2].isBool());
    CHECK(arr[3].isChar());
    CHECK(arr[4].isString());

    CHECK(arr[0].toInt() == 9897);
    CHECK(arr[1].toReal() == 3.14159);
    CHECK(arr[2].toBool());
    CHECK(arr[3].toChar() =='A');
    CHECK(arr[4].stringRef() == std::string("This is a string with quotes \"embedded\""));
}

TEST_CASE("04 LPP Serializer fromString")
{
    LppVariant varr = LppSerializer::fromString("[ [ 83, 89 ], [ 60, 49 ], [ 34, 80 ], [ 25, 66 ], [ 42, 22 ] ]");

    REQUIRE(varr.isArray());

    std::vector<LppVariant>& arr = varr.arrayRef();
    REQUIRE(arr.size() == 5);

    REQUIRE(arr[0].isArray());
    REQUIRE(arr[1].isArray());
    REQUIRE(arr[2].isArray());
    REQUIRE(arr[3].isArray());
    REQUIRE(arr[4].isArray());
    REQUIRE(arr[0].arrayRef().size() == 2);
    REQUIRE(arr[1].arrayRef().size() == 2);
    REQUIRE(arr[2].arrayRef().size() == 2);
    REQUIRE(arr[3].arrayRef().size() == 2);
    REQUIRE(arr[4].arrayRef().size() == 2);

    CHECK(arr[0].arrayRef()[0].toInt() == 83);
    CHECK(arr[0].arrayRef()[1].toInt() == 89);
    CHECK(arr[1].arrayRef()[0].toInt() == 60);
    CHECK(arr[1].arrayRef()[1].toInt() == 49);
    CHECK(arr[2].arrayRef()[0].toInt() == 34);
    CHECK(arr[2].arrayRef()[1].toInt() == 80);
    CHECK(arr[3].arrayRef()[0].toInt() == 25);
    CHECK(arr[3].arrayRef()[1].toInt() == 66);
    CHECK(arr[4].arrayRef()[0].toInt() == 42);
    CHECK(arr[4].arrayRef()[1].toInt() == 22);
}

TEST_CASE("05 LPP Serializer fromString") {
    LppVariant rec = LppSerializer::fromString("{ 9897, 3.14159, [ [ 83, 89 ], [ 60, 49 ], [ 34, 80 ], [ 25, 66 ], [ 42, 22 ] ], Falso }");

    REQUIRE(rec.isRecord());

    std::vector<LppVariant>& arr = rec.arrayRef();
    REQUIRE(arr.size() == 4);
    REQUIRE(arr[0].isInt());
    REQUIRE(arr[1].isReal());
    REQUIRE(arr[2].isArray());
    REQUIRE(arr[3].isBool());

    CHECK(arr[0].toInt() == 9897);
    CHECK(arr[1].toReal() == 3.14159);
    CHECK(!arr[3].toBool());

    REQUIRE(arr[2].arrayRef()[0].isArray());
    REQUIRE(arr[2].arrayRef()[1].isArray());
    REQUIRE(arr[2].arrayRef()[2].isArray());
    REQUIRE(arr[2].arrayRef()[3].isArray());
    REQUIRE(arr[2].arrayRef()[4].isArray());

    REQUIRE(arr[2].arrayRef()[0].arrayRef().size() == 2);
    REQUIRE(arr[2].arrayRef()[1].arrayRef().size() == 2);
    REQUIRE(arr[2].arrayRef()[2].arrayRef().size() == 2);
    REQUIRE(arr[2].arrayRef()[3].arrayRef().size() == 2);
    REQUIRE(arr[2].arrayRef()[4].arrayRef().size() == 2);

    CHECK(arr[2].arrayRef()[0].arrayRef()[0] == 83);
    CHECK(arr[2].arrayRef()[0].arrayRef()[1] == 89);
    CHECK(arr[2].arrayRef()[1].arrayRef()[0] == 60);
    CHECK(arr[2].arrayRef()[1].arrayRef()[1] == 49);
    CHECK(arr[2].arrayRef()[2].arrayRef()[0] == 34);
    CHECK(arr[2].arrayRef()[2].arrayRef()[1] == 80);
    CHECK(arr[2].arrayRef()[3].arrayRef()[0] == 25);
    CHECK(arr[2].arrayRef()[3].arrayRef()[1] == 66);
    CHECK(arr[2].arrayRef()[4].arrayRef()[0] == 42);
    CHECK(arr[2].arrayRef()[4].arrayRef()[1] == 22);
}

TEST_CASE("01 LPP Serializer toBinary")
{
    LppVariant v1(9897);
    LppVariant v2(3.14159);
    LppVariant v3(true);
    LppVariant v4('A');
    LppVariant v5(std::string("ABCDEF"));

    std::vector<char> bytes1 = LppSerializer::toBinary(v1, TypeInfo::Int);
    std::vector<char> bytes2 = LppSerializer::toBinary(v2, TypeInfo::Real);
    std::vector<char> bytes3 = LppSerializer::toBinary(v3, TypeInfo::Bool);
    std::vector<char> bytes4 = LppSerializer::toBinary(v4, TypeInfo::Char);
    std::vector<char> bytes5 = LppSerializer::toBinary(v5, TypeInfo::String(6));

    CHECK(toHexString(bytes1) == "a9260000");
    CHECK(toHexString(bytes2) == "6e861bf0f9210940");
    CHECK(toHexString(bytes3) == "01");
    CHECK(toHexString(bytes4) == "41");
    CHECK(toHexString(bytes5) == "414243444546");
}

TEST_CASE("02 LPP Serializer toBinary")
{
    TypeInfoSPtr arrti = TypeInfo::Array({10}, TypeInfo::Int);
    LppVariant varr;

    varr.initValue(arrti.get());
    std::vector<LppVariant>& arr = varr.arrayRef();
    arr[0] = 83;
    arr[1] = 89;
    arr[2] = 60;
    arr[3] = 49;
    arr[4] = 34;
    arr[5] = 80;
    arr[6] = 25;
    arr[7] = 66;
    arr[8] = 42;
    arr[9] = 22;

    std::vector<char> bytes = LppSerializer::toBinary(varr, arrti);

    REQUIRE(bytes.size() == sizeof(Lpp::Int) * 10);
    CHECK(toHexString(bytes) == "53000000590000003c00000031000000220000005000000019000000420000002a00000016000000");
}

TEST_CASE("03 LPP Serializer toBinary")
{
    TypeInfoSPtr recti = RecordTypeInfo::createShared("MyRecord", 
                                { {"Campo1", TypeInfo::Int},
                                  {"Campo2", TypeInfo::Real},
                                  {"Campo3", TypeInfo::Bool},
                                  {"Campo4", TypeInfo::Char},
                                  {"Campo5", TypeInfo::String(6)}  });
    LppVariant rec;

    rec.initValue(recti.get());
    std::vector<LppVariant>& arr = rec.arrayRef();

    arr[0] = 9897;
    arr[1] = 3.14159;
    arr[2] = true;
    arr[3] = 'A';
    arr[4] = std::string("ABCDEF");

    std::vector<char> bytes = LppSerializer::toBinary(rec, recti);
    
    REQUIRE(bytes.size() == sizeof(Lpp::Int) + sizeof(Lpp::Real) + sizeof(Lpp::Bool) + sizeof(Lpp::Char) + 6);
    CHECK(toHexString(bytes) == "a92600006e861bf0f92109400141414243444546");
}

TEST_CASE("04 LPP Serializer toBinary")
{
    TypeInfoSPtr arrti = TypeInfo::Array({5}, TypeInfo::Array({2}, TypeInfo::Int));
    LppVariant varr;

    varr.initValue(arrti.get());
    std::vector<LppVariant>& arr = varr.arrayRef();
    arr[0].arrayRef()[0] = 83;
    arr[0].arrayRef()[1] = 89;
    arr[1].arrayRef()[0] = 60;
    arr[1].arrayRef()[1] = 49;
    arr[2].arrayRef()[0] = 34;
    arr[2].arrayRef()[1] = 80;
    arr[3].arrayRef()[0] = 25;
    arr[3].arrayRef()[1] = 66;
    arr[4].arrayRef()[0] = 42;
    arr[4].arrayRef()[1] = 22;

    std::vector<char> bytes = LppSerializer::toBinary(varr, arrti);

    REQUIRE(bytes.size() == sizeof(Lpp::Int) * 10);
    CHECK(toHexString(bytes) == "53000000590000003c00000031000000220000005000000019000000420000002a00000016000000");
}

TEST_CASE("05 LPP Serializer toBinary")
{
    TypeInfoSPtr recti = RecordTypeInfo::createShared("MyRecord", 
                                { {"Campo1", TypeInfo::Int},
                                  {"Campo2", TypeInfo::Real},
                                  {"Campo3", TypeInfo::Array({5}, TypeInfo::Array({2}, TypeInfo::Int))},
                                  {"Campo4", TypeInfo::Bool}  });
    LppVariant rec;

    rec.initValue(recti.get());
    std::vector<LppVariant>& arr = rec.arrayRef();

    arr[0] = 9897;
    arr[1] = 3.14159;
    arr[2].arrayRef()[0].arrayRef()[0] = 83;
    arr[2].arrayRef()[0].arrayRef()[1] = 89;
    arr[2].arrayRef()[1].arrayRef()[0] = 60;
    arr[2].arrayRef()[1].arrayRef()[1] = 49;
    arr[2].arrayRef()[2].arrayRef()[0] = 34;
    arr[2].arrayRef()[2].arrayRef()[1] = 80;
    arr[2].arrayRef()[3].arrayRef()[0] = 25;
    arr[2].arrayRef()[3].arrayRef()[1] = 66;
    arr[2].arrayRef()[4].arrayRef()[0] = 42;
    arr[2].arrayRef()[4].arrayRef()[1] = 22;
    arr[3] = false;

    std::vector<char> bytes = LppSerializer::toBinary(rec, recti);
    
    REQUIRE(bytes.size() == sizeof(Lpp::Int) + sizeof(Lpp::Real) + sizeof(Lpp::Bool) + sizeof(Lpp::Int) * 5 * 2);
    CHECK(toHexString(bytes) == "a92600006e861bf0f921094053000000590000003c00000031000000220000005000000019000000420000002a0000001600000000");
}

TEST_CASE("01 LPP Serializer fromBinary")
{
    LppVariant v1(0);
    LppVariant v2(0.0);
    LppVariant v3(false);
    LppVariant v4('\0');
    LppVariant v5(std::string{});

    TypeInfoSPtr str6ti = TypeInfo::String(6);

    LppSerializer::fromBinary(v1, TypeInfo::Int.get(), toByteVector("a9260000"));
    LppSerializer::fromBinary(v2, TypeInfo::Real.get(), toByteVector("6e861bf0f9210940"));
    LppSerializer::fromBinary(v3, TypeInfo::Bool.get(), toByteVector("01"));
    LppSerializer::fromBinary(v4, TypeInfo::Char.get(), toByteVector("41"));
    LppSerializer::fromBinary(v5, str6ti.get(), toByteVector("414243444546"));

    REQUIRE(v1.isInt());
    CHECK(v1.toInt() == 9897);
    REQUIRE(v2.isReal());
    CHECK(v2.toReal() == 3.14159);
    REQUIRE(v3.isBool());
    CHECK(v3.toBool());
    REQUIRE(v4.isChar());
    CHECK(v4.toChar() == 'A');
    REQUIRE(v5.isString());
    CHECK(v5.stringRef() == "ABCDEF");
}
