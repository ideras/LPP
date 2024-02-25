#ifndef LPPVARIANTSERIALIZER_H
#define LPPVARIANTSERIALIZER_H

#include <string>
#include <vector>
#include "lpp_variant.h"

class LppSerializer
{
public:
    using Kind = LppVariant::Kind;
    LppSerializer();

    static std::string toString(const LppVariant& val);
    static LppVariant fromString(const std::string& str);
    static std::vector<char> toBinary(const LppVariant& val, const TypeInfoSPtr& typei);
    static bool fromBinary(LppVariant &val, const TypeInfo *typei, const std::vector<char>& bytes);
    static bool sameType(const LppVariant& val1, const LppVariant& val2);

private:
    static void toBinary(const LppVariant& val, const TypeInfo *typei, char *bytes);
    static bool fromBinary(LppVariant &val, const TypeInfo *typei, const char *bytes);

private:
    enum class Token { Int, Real, Char, Bool, String, OpenBracket, OpenCurly,
                       CloseBracket, CloseCurly, Comma, Error, End };

    class Lexer
    {
    public:
        Lexer(const std::string& str): str(str), pos(0)
        {}

        Token nextToken();
        LppVariant getValue(Token tk);
       
        std::string text() const
        { return _text; }

    private:
        LppVariant toInt();
        LppVariant toReal();
        LppVariant toChar();
        LppVariant toBool();
        LppVariant toString();

    private:
        const std::string& str;
        std::string _text;
        int pos;
    };

    class Parser
    {
    public:
        Parser(Lexer& lex): lex(lex)
        {}

        LppVariant parse();

    private:
        bool match(Token _tk)
        { return (tk == _tk); }

        LppVariant parseItem();
        LppVariant parseArray();
        LppVariant parseRecord();

    private:
        Token tk;
        Lexer& lex;
    };

private:
    static std::string arrayToString(const LppVariant& val);
    static std::string recordToString(const LppVariant& val);
};

#endif // LPPVARIANTSERIALIZER_H
