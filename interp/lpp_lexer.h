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

    LexerState(std::streampos pos, int line, int brace_depth, const std::string& text)
        : stream_pos(pos),
          src_line(line),
          brace_depth(brace_depth),
          text(text)
    {}

    std::streampos stream_pos;
    int src_line;
    int brace_depth;
    std::string text;
};

class LppLexer
{
public:
    LppLexer(std::istream& in)
        : in(in), src_line(1), brace_depth(0)
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
        brace_depth = lstate.brace_depth;
        text = lstate.text;
    }

    LexerState getCurrentState() const
    { return LexerState(in.tellg(), src_line, brace_depth, text); }

private:
    void ungetChar(int ch);
    int nextChar();

private:
    std::istream& in;
    int src_line;
    std::string text;
    int brace_depth;
};

#endif // !defined(__LPP_ANALEX_H__)
