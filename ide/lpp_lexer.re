#include "lpp_highlighter.h"

LPPHighlighter::Token LPPHighlighter::LppLexer::nextToken()
{
    while (true) {
        tbegin = cursor;
        if (in_comment) {
            goto block_comment;
        }
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:eof = 0;
        re2c:api = custom;
        re2c:api:style = free-form;
        re2c:define:YYCTYPE = wchar_t;
        re2c:define:YYLESSTHAN = "cursor >= limit";
        re2c:define:YYPEEK = "cursor < limit ? (*cursor).unicode() : 0";  // fake null
        re2c:define:YYSKIP = "++cursor;";
        re2c:define:YYBACKUP = "marker = cursor;";
        re2c:define:YYRESTORE = "cursor = marker;";

        NUMBER = [0-9]+;
        IDENT = [a-zA-Z_][a-zA-Z0-9_.]*;
        WSP = [ \t]+;

        *    { return makeToken(Token::None); }
        $    { return makeToken(Token::End); }
        "arreglo" | "de" | "entero" | "real" | "caracter" | "booleano" | "cadena" | "funcion" |
        "procedimiento" | "var" | "inicio" | "fin" | "final" | "si" | "entonces" | "sino" |
        "mientras" | "haga" | "para" | "hasta" | "llamar" | "repita" | "hasta" | "caso" |
        "o" | "y" | "no" | "div" | "mod" | "lea" | "escriba"  | "retorne" | "tipo" | "es" |
        "registro" | "archivo" | "secuencial" | "abrir" | "como" | "lectura" | "escritura" |
        "cerrar" | "leer" | "escribir" | "verdadero" | "falso"
        { return makeToken(Token::Keyword); }
        
        "limpiar_pantalla" | "posicionar_cursor" | "color_fondo" | "color_texto" |
        "obtener_caracter" | "obtener_tecla" | "tecla_presionada" | "pausa" |
        "nueva_linea" | "entero_a_cadena" | "real_a_cadena" | "longitud" |
        "valor_ascii" | "caracter_ascii" | "inicializar_aleatorio" | "aleatorio"
        { return makeToken(Token::BiFunction); }

        NUMBER      { return makeToken(Token::Number); }
        IDENT       { return makeToken(Token::Ident); }
        WSP         { continue; }
        "//" [^\n]*    { return makeToken(Token::LineComment); }
        [\"] [^\"]* [\"] { return makeToken(Token::StringLiteral); }
        "/*"        { in_comment = true; return makeToken(Token::StartOfComment); }
    */
    block_comment:
    /*!re2c
        *       { continue; }
        $       { return makeToken(Token::End); }
        "*/"    { return makeToken(Token::EndOfComment); }
    */
    }
}

LPPHighlighter::Token LPPHighlighter::LppLexer::makeToken(int tid)
{
    int start_pos = tbegin - begin;
    int len = cursor - tbegin;

    return {tid, start_pos, len};
}
