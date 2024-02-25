
#if !defined(_LPP_TOKENS_H__)
#define _LPP_TOKENS_H__

//Definiciones de constantes para los tokens
enum class Token {
    KwRegistro, KwFinRegistro, KwTipo, KwEs, KwEntero, KwReal, KwChar, KwBool, KwCadena, KwArreglo,
    KwArchivo, KwSecuencial, KwDe, KWNo, KwProcedimiento, KwFuncion, KwVar, KwSi, KwEntonces, KwSino,
    KwFinSi, KwMientras, KwHaga, KwFinMientras, KwPara, KwHasta, KwFinPara, KwRepita, KwCaso, KwFinCaso,
    KwLlamar, KwInicio, KwFin, KwLea, KwEscriba, KWRetorne, KwAbrir, KwComo, KwLectura, KwEscritura,
    KwCerrar, KwLeer, KwEscribir, KwVerdadero, KwFalso, Ident,
    EndOfLine, OpenBracket, CloseBracket, OpenPar, ClosePar, Comma, Colon, Dot, RangeInd,
    OpAssign, OpRel, OpBoolOr, OpBoolAnd, OpAdd, OpSub, OpMult, OpDiv, OpIDiv, OpMod, OpPow,
    StrLiteral, CharLiteral, IntConst, RealConst, Eof, Unkown
};

#endif
