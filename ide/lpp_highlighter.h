// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class LPPHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    LPPHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct Token {
        enum { Keyword, BiFunction, Ident, Number, StringLiteral, LineComment,
               StartOfComment, EndOfComment, None, End };

        int id;
        int start_pos;
        int len;
    };

    class LppLexer
    {
    public:
        LppLexer(const QString& input, bool in_comment = false)
            : begin(input.constBegin()),
            cursor(input.constBegin()),
            limit(input.constEnd()),
            in_comment(in_comment)
        {}

        Token nextToken();

    private:
        Token makeToken(int tid);

    private:
        bool in_comment;
        QString::ConstIterator begin, cursor, marker, limit, tbegin;
    };

private:
    QTextCharFormat kw_fmt;
    QTextCharFormat number_fmt;
    QTextCharFormat comment_fmt;
    QTextCharFormat str_fmt;
    QTextCharFormat ident_fmt;
    QTextCharFormat bifunc_fmt;
};

#endif // HIGHLIGHTER_H
