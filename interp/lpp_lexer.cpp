/*
 * lpp_lex.cpp: Implementation of LPP lexical analizer
 */

#include <iostream>
#include "lpp_exception.h"
#include "lpp_lexer.h"
#include "str_util.h"

#define DIGITOS	while (isdigit(ch))         \
                {                           \
                    text += static_cast<char>(ch); \
                    ch = nextChar();          \
				}

struct  TKeyword
{
    const char *text;
    Token value;
};

TKeyword kwords[] = {
    {"arreglo"	, Token::KwArreglo},
    {"de"		, Token::KwDe},
    {"entero"	, Token::KwEntero},
    {"real"		, Token::KwReal},
    {"caracter",  Token::KwChar},
    {"booleano",  Token::KwBool},
    {"cadena"	, Token::KwCadena},
    {"funcion"	, Token::KwFuncion},
    {"procedimiento", Token::KwProcedimiento},
    {"var"		, Token::KwVar},
    {"inicio"	, Token::KwInicio},
    {"fin"		, Token::KwFin},
    {"final"	, Token::KwFin},
    {"si"		, Token::KwSi},
    {"entonces", Token::KwEntonces},
    {"sino"		, Token::KwSino},
    {"fin si"	, Token::KwFinSi},
    {"mientras", Token::KwMientras},
    {"haga"		, Token::KwHaga},
    {"fin mientras", Token::KwFinMientras},
    {"para"		, Token::KwPara},
    {"hasta"	, Token::KwHasta},
    {"fin para", Token::KwFinPara},
    {"llamar"	, Token::KwLlamar},
    {"repita"	, Token::KwRepita},
    {"hasta"	, Token::KwHasta},
    {"caso"		, Token::KwCaso},
    {"fin caso"	, Token::KwFinCaso},
    {"o"		, Token::OpBoolOr},
    {"y"		, Token::OpBoolAnd},
    {"no"		, Token::KWNo},
    {"div"		, Token::OpIDiv},
    {"mod"		, Token::OpMod},
    {"lea"		, Token::KwLea},
    {"escriba"	, Token::KwEscriba},
    {"retorne"	, Token::KWRetorne},
    {"tipo"		, Token::KwTipo},
    {"es"		, Token::KwEs},
    {"registro"	, Token::KwRegistro},
    {"fin registro"	, Token::KwFinRegistro},
    {"archivo"	, Token::KwArchivo},
    {"secuencial", Token::KwSecuencial},
    {"abrir", Token::KwAbrir},
    {"como"	, Token::KwComo},
    {"lectura"	, Token::KwLectura},
    {"escritura", Token::KwEscritura},
    {"cerrar", Token::KwCerrar},
    {"leer", Token::KwLeer},
    {"escribir", Token::KwEscribir},
    {"verdadero", Token::KwVerdadero},
    {"falso"	, Token::KwFalso},
};

Token LppLexer::getNextToken()
{	int ch, ch2;
    
    text = "";
    while(1)
    {	ch = nextChar();

        if (ch == ' ' || ch == '\t') {
            continue;
        }
        
        text += static_cast<char>(ch);

        if (ch == '/')
        {
            ch2 = nextChar();
            if (ch2 == '*') // Block comment
            {
                while (1)
                {
                    ch2 = nextChar();
					if (ch2==EOF)
                        throw LPPException(src_line, "Comentario no cerrado");

					if (ch2=='*')
                    {
                        ch2 = nextChar();
						if (ch2=='/')
							break;
						if (ch2==EOF)
                            throw LPPException(src_line, "Comentario no cerrado");
                        
                        ungetChar(ch2);
					}
                    else if (ch2 == '\n') {
                        src_line++;
					}
				}
				if (ch2 != EOF)
					continue;
			}
			else if (ch2=='/')
            {
                while (1)
                {
                    ch2 = nextChar();
					if (ch2==EOF || ch2=='\n')
						break;
				}
				ch = ch2;
			}
			else
                ungetChar(ch2);
		}


        if (ch == '\n') {
            src_line ++;
            return Token::EndOfLine;
        } else if (ch == '\r') {
            ch = nextChar();
            if (ch == '\n') {
                src_line++;
                return Token::EndOfLine;
            }
            ungetChar(ch);
            return Token::Unkown;
        }
		else if (isalpha(ch) || ch=='_')
		{
            text = "";
			while ( isalnum(ch) || ch=='_')
            {
                text += static_cast<char>(ch);
                ch = nextChar();
            }
            
            std::string lbuffer = str::lower(text);
            if (lbuffer.compare("fin") == 0 && ch == ' ')
            {
                std::string str;
                
                while ((ch = nextChar()) == ' ');

				str = "";
                while (isalpha(ch))
                {
                    str += static_cast<char>(ch);
                    ch = nextChar();
				}

                if (!str.empty())
                {
                    text += ' ';
                    text += str;
                }
			}
			
            if (ch != EOF)
                ungetChar(ch);
            
            lbuffer = str::lower(text);
            for (int i=0; i < sizeof(kwords)/sizeof(kwords[0]); i++)
            {
                if (lbuffer.compare(kwords[i].text) == 0) {
                    return kwords[i].value;
                }
			}
            
            if (text.find_first_of(' ') != std::string::npos)
				return Token::Unkown;

			return Token::Ident;
		}
		else if (ch=='"')
		{
            text = "";
            while ((ch=nextChar()) != '"' && ch != '\n' && ch != EOF)
                text += static_cast<char>(ch);
			
            if (ch == '\n' || ch == EOF)
                throw LPPException(src_line, "Falta '\"' en la cadena");

			return Token::StrLiteral;
		}
        else if (ch == '\'')
		{
            text = "";
            while ((ch=nextChar()) != '\'' && ch != '\n' && ch != EOF)
                text += static_cast<char>(ch);
			
            if (ch == '\n' || ch == EOF)
                throw LPPException(src_line, "Se esperaba '\''");
            
            if (text.length() != 1)
                throw LPPException(src_line, "La longitud de las literales tipo caracter debe ser 1");

			return Token::CharLiteral;
		}
		else if (ch == '>')
        {
            text = '>';
            ch = nextChar();

			if (ch == '=')
                text += static_cast<char>(ch);
            else
                ungetChar(ch);

			return Token::OpRel;
		}
		else if (ch=='<')
        {
            text='<';
            ch = nextChar();

			if (ch=='=' || ch=='>' || ch=='-')
                text += static_cast<char>(ch);
			else
                ungetChar(ch);
            
            if (text == "<-")
				return Token::OpAssign;
			else
				return Token::OpRel;
		}
		else if (ch == '=')
			return Token::OpRel;
		else if (isdigit(ch))
        {
            bool dot = false;
            text = "";
			
			DIGITOS;

			if (ch == '.')
            {
                dot = true;
                text += static_cast<char>(ch);
                ch = nextChar();
				
				DIGITOS;
			}
			if (ch == 'E' || ch == 'e')
            {	text += static_cast<char>(ch);
                ch = nextChar();
				DIGITOS;
            }
            ungetChar(ch);

            return dot? Token::RealConst : Token::IntConst;
		}
		else if (ch=='-')
        {
            text = '-';
            ch = nextChar();

            if (ch == '>')
            {
                text += static_cast<char>(ch);
                return Token::RangeInd;
            } else {
                ungetChar(ch);
                return Token::OpSub;
            }
		}
		else if (ch == '+')
            return Token::OpAdd;
		else if (ch == '*')
			return Token::OpMult;
		else if (ch == '/')
			return Token::OpDiv;
		else if (ch=='^')
			return Token::OpPow;
		else if (ch==':')
			return Token::Colon;
		else if (ch=='.')
			return Token::Dot;
		else if (ch==',')
			return Token::Comma;
		else if (ch=='(')
			return Token::OpenPar;
		else if (ch==')')
			return Token::ClosePar;
		else if (ch=='[')
			return Token::OpenBracket;
		else if (ch==']')
			return Token::CloseBracket;
		else if (ch==EOF)
			return Token::Eof;
		else
            return Token::Unkown;
    }
}

void LppLexer::ungetChar(int ch)
{
    in.putback(ch);
}

int LppLexer::nextChar()
{
    return in.get();
}
