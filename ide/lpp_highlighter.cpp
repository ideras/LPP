#include "lpp_highlighter.h"

LPPHighlighter::LPPHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    kw_fmt.setForeground(QColor(0x11, 0x00, 0x9e));
    number_fmt.setForeground(Qt::darkMagenta);

    ident_fmt.setFontItalic(false);
    ident_fmt.setForeground(QColor(0x6d, 0x29, 0x32));

    bifunc_fmt.setFontWeight(QFont::Bold);
    bifunc_fmt.setForeground(QColor(0x40, 0xA2, 0xE3));

    str_fmt.setForeground(QColor(0x1a, 0x5d, 0x1a));

    comment_fmt.setForeground(Qt::lightGray);
}

void LPPHighlighter::highlightBlock(const QString &text)
{
    bool in_comment = (previousBlockState() == 1);
    int block_state = 0;
    LppLexer lex(text, in_comment);

    Token tk = lex.nextToken();
    if (in_comment) {
        if (tk.id == Token::End) {
            setFormat(0, tk.start_pos, comment_fmt);
            block_state = 1;
        } else { // EndOfComment token
            setFormat(0, tk.start_pos + 2, comment_fmt);
        }
    } else {
        while (tk.id != Token::End) {
            switch (tk.id) {
                case Token::Keyword:
                setFormat(tk.start_pos, tk.len, kw_fmt);
                    break;
                case Token::Ident:
                    setFormat(tk.start_pos, tk.len, ident_fmt);
                    break;
                case Token::BiFunction:
                    setFormat(tk.start_pos, tk.len, bifunc_fmt);
                    break;
                case Token::Number:
                    setFormat(tk.start_pos, tk.len, number_fmt);
                    break;
                case Token::StringLiteral:
                    setFormat(tk.start_pos, tk.len, str_fmt);
                    break;
                case Token::LineComment:
                    setFormat(tk.start_pos, tk.len, comment_fmt);
                    break;
                case Token::StartOfComment: {
                    int orig_pos = tk.start_pos;
                    tk = lex.nextToken();
                    if (tk.id == Token::End) {
                        setFormat(orig_pos, tk.start_pos - orig_pos, comment_fmt);
                        block_state = 1;
                    } else { // EndOfComment token
                        setFormat(orig_pos, tk.start_pos - orig_pos + 2, comment_fmt);
                    }
                }
                default:
                    break;
            }
            if (tk.id != Token::End) {
                tk = lex.nextToken();
            }
        }
    }
    setCurrentBlockState(block_state);
}
