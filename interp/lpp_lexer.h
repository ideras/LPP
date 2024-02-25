/*
 * lpp_lex.h: Interface of LPP lexical analizer
 */

#if !defined(__LPP_ANALEX_H__)
#define __LPP_ANALEX_H__

#include <string>
#include <istream>
#include "lpp_tokens.h"

struct LexerState
{
    LexerState()
    {}

    LexerState(std::streampos pos, int line, const std::string& text)
        : stream_pos(pos),
          src_line(line),
          text(text)
    {}

    std::streampos stream_pos;
    int src_line;
    std::string text;
};

class LppLexer  
{
public:
    LppLexer(std::istream& in)
        : in(in), src_line(1)
    {}
    
    ~LppLexer()
    {}

    int getLine()
    { return src_line; }

    Token getNextToken();

    std::string getText() const
    { return text; }
    
    void setCurrentState(const LexerState& lstate)
    {
        in.seekg(lstate.stream_pos, std::istream::beg);
        src_line = lstate.src_line;
        text = lstate.text;
    }
    
    LexerState getCurrentState() const
    { return LexerState(in.tellg(), src_line, text); }

private:
    void ungetChar(int ch);
    int nextChar();

private:
    std::istream& in;
    int src_line;
    std::string text;
};

#endif // !defined(__LPP_ANALEX_H__)
