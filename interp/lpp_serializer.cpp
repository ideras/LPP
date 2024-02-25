#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "str_util.h"
#include "lpp_serializer.h"

LppSerializer::LppSerializer()
{

}

std::string LppSerializer::toString(const LppVariant& val)
{
    switch (val.kind()) {
        case Kind::Bool: return val.toBool()? "Verdadero" : "Falso";
        case Kind::Int: return std::to_string(val.toInt());
        case Kind::Char: return "'" + std::string(1, val.toChar()) + "'";
        case Kind::Real: return str::formatReal(val.toReal());

        case Kind::String: {
            std::ostringstream oss;
            oss << std::quoted(val.stringCRef());
            return oss.str();
        }

        case Kind::Array: return arrayToString(val);
        case Kind::Record: return recordToString(val);

        default:
            throw std::runtime_error("Invalid kind in call to LppVariantSerializer.toString");
    }
}

std::string LppSerializer::arrayToString(const LppVariant& val)
{
    bool first = true;

    std::string str = "[ ";
    for (const auto& v : val.arrayCRef()) {
        if (first) {
            first = false;
        } else {
            str += ", ";
        }
        str += toString(v);
    }
    str += " ]";
    return str;
}

std::string LppSerializer::recordToString(const LppVariant& val)
{
    bool first = true;

    std::string str = "{ ";
    for (const auto& v : val.arrayCRef()) {
        if (first) {
            first = false;
        } else {
            str += ", ";
        }
        str += toString(v);
    }
    str += " }";
    return str;
}

LppVariant LppSerializer::fromString(const std::string &str)
{
    Lexer lex(str);
    Parser parser(lex);

    return parser.parse();
}

std::vector<char> LppSerializer::toBinary(const LppVariant &val, const TypeInfoSPtr &typei)
{
    std::vector<char> bytes(typei->byteSize());
    toBinary(val, typei.get(), bytes.data());

    return bytes;
}

bool LppSerializer::fromBinary(LppVariant& val, const TypeInfo *typei, const std::vector<char>& bytes)
{
    if (bytes.size() != typei->byteSize()) {
        return false;
    }

    return fromBinary(val, typei, bytes.data());
}

bool LppSerializer::sameType(const LppVariant &val1, const LppVariant &val2)
{
    if (val1.valueKind() != val2.valueKind()) {
        return false;
    }
    if (!val1.isArray() && !val1.isRecord()) {
        return true;
    }
    const std::vector<LppVariant>& arr1 = val1.arrayCRef();
    const std::vector<LppVariant>& arr2 = val2.arrayCRef();

    if (arr1.size() != arr2.size()) {
        return false;
    }
    for (int i = 0; i < arr1.size(); i++) {
        if (!sameType(arr1[i], arr2[i])) {
            return false;
        }
    }
    return true;
}

void LppSerializer::toBinary(const LppVariant &val, const TypeInfo *typei, char *bytes)
{
    switch (val.valueKind()) {
        case LppVariant::Kind::Int:
            *reinterpret_cast<Lpp::Int *>(bytes) = val.toInt();
            break;
        case LppVariant::Kind::Real:
            *reinterpret_cast<Lpp::Real *>(bytes) = val.toReal();
            break;
        case LppVariant::Kind::Char:
            *reinterpret_cast<Lpp::Char *>(bytes) = val.toChar();
            break;
        case LppVariant::Kind::Bool:
            *reinterpret_cast<Lpp::Bool *>(bytes) = val.toBool();
            break;
        case LppVariant::Kind::String: {
            int byte_size = typei->byteSize();
            const std::string& str = val.stringCRef();
            if (str.length() < byte_size) {
                std::fill_n(bytes, byte_size, '\0');
                std::copy(str.cbegin(), str.cend(), bytes);
            } else {
                std::copy(str.cbegin(), str.cbegin() + byte_size, bytes);
            }

            break;
        }
        case LppVariant::Kind::Array: {
            const std::vector<LppVariant>& varray = val.arrayCRef();
            const TypeInfo* elem_type = typei->cptr<ArrayTypeInfo>()->elemType().get();
            char *p = bytes;

            for (const auto& itm : varray) {
                toBinary(itm, elem_type, p);
                p += elem_type->byteSize();
            }
            break;
        }
        case LppVariant::Kind::Record:  {
            const std::vector<LppVariant>& varray = val.arrayCRef();
            const RecordTypeInfo* rti= typei->cptr<RecordTypeInfo>();
            char *p = bytes;

            for (const auto& fld: rti->fields()) {
                toBinary(varray[fld.index()], fld.typeInfo().get(), p);
                p += fld.typeInfo()->byteSize();
            }
            break;
        }
        default:
            break;
        }
}

bool LppSerializer::fromBinary(LppVariant &val, const TypeInfo *typei, const char *bytes)
{
    const char *p = bytes;

    switch (typei->kind()) {
        case TypeInfo::Kind::Int:
            static_cast<Lpp::Int&>(val) = *reinterpret_cast<const Lpp::Int *>(p);
            break;
        case TypeInfo::Kind::Real:
            static_cast<Lpp::Real&>(val) = *reinterpret_cast<const Lpp::Real *>(p);
            break;
        case TypeInfo::Kind::Char:
            static_cast<Lpp::Char&>(val) = *reinterpret_cast<const Lpp::Char *>(p);
            break;
        case TypeInfo::Kind::Bool:
            static_cast<Lpp::Bool&>(val) = *reinterpret_cast<const Lpp::Bool *>(p);
            break;
        case TypeInfo::Kind::String:
           static_cast<std::string&>(val) = std::string(p, typei->byteSize());
           break;
        case TypeInfo::Kind::Array: {
            const TypeInfo* elem_type = typei->cptr<ArrayTypeInfo>()->elemType().get();
            auto& varray = static_cast<std::vector<LppVariant>&>(val);

            for (auto& itm : varray) {
                fromBinary(itm, elem_type, p);
                p += elem_type->byteSize();
            }
            break;
        }
        case TypeInfo::Kind::Record: {
            const RecordTypeInfo* rti = typei->cptr<RecordTypeInfo>();
            auto& varray = static_cast<std::vector<LppVariant>&>(val);

            for (const auto& fld: rti->fields()) {
                fromBinary(varray[fld.index()], fld.typeInfo().get(), p);
                p += fld.typeInfo()->byteSize();
            }
            break;
        }
        default:
            return false;
    }

    return true;
}

LppVariant LppSerializer::Lexer::getValue(LppSerializer::Token tk)
{
    switch (tk) {
        case Token::Int: return toInt();
        case Token::Real: return toReal();
        case Token::Char: return toChar();
        case Token::Bool: return toBool();
        case Token::String: return toString();
        default:
            return LppVariant::Empty;
    }
}

LppVariant LppSerializer::Lexer::toInt()
{
    try {
        return std::stoi(text());
    } catch (...) {
        return LppVariant::Empty;
    }
}

LppVariant LppSerializer::Lexer::toReal()
{
    try {
        return std::stod(text());
    } catch (...) {
        return LppVariant::Empty;
    }
}

LppVariant LppSerializer::Lexer::toChar()
{
    return text()[1];
}

LppVariant LppSerializer::Lexer::toBool()
{
    if (str::lower(text()) == "falso") {
        return false;
    } else {
        return true;
    }
}

LppVariant LppSerializer::Lexer::toString()
{
    std::istringstream iss(text());
    std::string str;

    iss >> std::quoted(str);

    return str;
}

LppSerializer::Token LppSerializer::Lexer::nextToken()
{
    if (pos >= str.length()) {
        return Token::End;
    }

    _text = "";
    do {
        char ch = str[pos++];
        if (ch == ' ' || ch == '\t') {
            continue;
        }
        switch (ch) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                _text += ch;
                while (pos < str.length()) {
                    ch = str[pos++];
                    if (!isdigit(ch)) break;

                    _text += ch;
                }
                if (ch == '.') {
                    _text += ch;
                    while (pos < str.length()) {
                        ch = str[pos++];
                        if (!isdigit(ch)) break;

                        _text += ch;
                    }
                    if (pos < str.length()) pos--;

                    return Token::Real;
                }
                if (pos < str.length()) pos--;

                return Token::Int;
            }
            case '\'': {
                _text += ch;
                if (pos < str.length()) {
                    _text += str[pos++];
                }
                ch = str[pos++];
                if (ch == '\'') {
                    _text += ch;
                    return Token::Char;
                }
                return Token::Error;
            }
            case '"': {
                _text += ch;

                ch = '\0';
                bool prev_was_slash = false;
                while (pos < str.length()) {
                    ch = str[pos++];
                    if (ch == '"' && !prev_was_slash) {
                        break;
                    }
                    if (ch == '\\') {
                        prev_was_slash = true;
                    } else {
                        prev_was_slash = false;
                    }

                    _text += ch;
                }
                if (ch == '"') {
                    _text += ch;
                    pos++;

                    return Token::String;
                }
                return Token::Error;
            }
            case 'V':
            case 'v':
            case 'F':
            case 'f': {
                _text += ch;

                while (pos < str.length()) {
                    ch = str[pos++];
                    if (!isalpha(ch)) break;

                    _text += ch;
                }
                if (pos < str.length()) pos--;

                if (str::lower(_text) == "verdadero" || str::lower(_text) == "falso") {
                    return Token::Bool;
                }
                return Token::Error;
            }
            case '{':
                _text += ch;
                return Token::OpenCurly;
            case '}':
                _text += ch;
                return Token::CloseCurly;
            case '[':
                _text += ch;
                return Token::OpenBracket;
            case ']':
                _text += ch;
                return Token::CloseBracket;
            case ',':
                _text += ch;
                return Token::Comma;
            default:
                return Token::Error;
        }
    } while (true);
}

LppVariant LppSerializer::Parser::parse()
{
    tk = lex.nextToken();
    LppVariant val = parseItem();

    tk = lex.nextToken();
    if (tk != Token::End) {
        return LppVariant::Empty;
    }
    return val;
}

LppVariant LppSerializer::Parser::parseItem()
{
    switch (tk) {
        case Token::Int:
        case Token::Real:
        case Token::Char:
        case Token::Bool:
        case Token::String: {
            LppVariant val = lex.getValue(tk);
            tk = lex.nextToken();
            return val;
        }

        case Token::OpenBracket:
            return parseArray();

        case Token::OpenCurly:
            return parseRecord();

        default:
            return LppVariant::Empty;
    }
}

LppVariant LppSerializer::Parser::parseArray()
{
    tk = lex.nextToken();
    std::vector<LppVariant> varray;
    LppVariant itmval = parseItem();

    if (itmval.isEmpty()) {
        return itmval;
    }
    varray.push_back(itmval);

    while (tk == Token::Comma) {
        tk = lex.nextToken();

        itmval = parseItem();
        if (itmval.isEmpty()) {
            return itmval;
        }
        varray.push_back(itmval);
    }

    if (!match(Token::CloseBracket)) {
        return LppVariant::Empty;
    }
    tk = lex.nextToken();

    return LppVariant::makeArray(std::move(varray));
}

LppVariant LppSerializer::Parser::parseRecord()
{
    tk = lex.nextToken();
    std::vector<LppVariant> varray;
    LppVariant itmval = parseItem();

    if (itmval.isEmpty()) {
        return itmval;
    }
    varray.push_back(itmval);

    while (tk == Token::Comma) {
        tk = lex.nextToken();

        itmval = parseItem();
        if (itmval.isEmpty()) {
            return itmval;
        }
        varray.push_back(itmval);
    }

    if (!match(Token::CloseCurly)) {
        return LppVariant::Empty;
    }
    tk = lex.nextToken();

    return LppVariant::makeRecord(std::move(varray));
}
