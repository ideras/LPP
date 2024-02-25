/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QDebug>
#include <QPainter>
#include <QTextBlock>

#include "lpp_editor.h"

LppEditor::LppEditor(QWidget *parent): QPlainTextEdit(parent)
{
    line_number_area = new LineNumberArea(this);

    connect(this, &LppEditor::blockCountChanged, this, &LppEditor::updateLineNumberAreaWidth);
    connect(this, &LppEditor::updateRequest, this, &LppEditor::updateLineNumberArea);
    connect(this, &LppEditor::cursorPositionChanged, this, &LppEditor::highlightCurrentLine);

    line_area_backcolor.setRgb(0xef, 0xf0, 0xf1);
    line_area_textcolor.setRgb(0x80, 0x80, 0x80);
    sel_line_backcolor.setRgb(0xff, 0xed, 0xe7);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
    setLineWrapMode(QPlainTextEdit::NoWrap);
}

int LppEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void LppEditor::gotoLine(int line_number)
{
    QTextCursor cursor(document()->findBlockByLineNumber(line_number - 1));
    setTextCursor(cursor);
}

void LppEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void LppEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy) {
        line_number_area->scroll(0, dy);
    } else {
        line_number_area->update(0, rect.y(), line_number_area->width(), rect.height());
    }

    if (rect.contains(viewport()->rect())) {
        updateLineNumberAreaWidth(0);
    }
}

void LppEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    line_number_area->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void LppEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extra_sels;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        selection.format.setBackground(sel_line_backcolor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extra_sels.append(selection);
    }

    setExtraSelections(extra_sels);
}

void LppEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(line_number_area);
    painter.fillRect(event->rect(), line_area_backcolor);

    QTextBlock block = firstVisibleBlock();
    int block_number = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());
    int sel_block_number = textCursor().blockNumber();
    QFont sel_bold = painter.font();
    QFont def_font = painter.font();

    sel_bold.setBold(true);

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString str_number = QString::number(block_number  + 1);

            if (sel_block_number == block_number) {
                painter.setFont(sel_bold);
            } else {
                painter.setFont(def_font);
            }

            painter.setPen(line_area_textcolor);
            painter.drawText(0, top, line_number_area->width(), fontMetrics().height(),
                             Qt::AlignRight, str_number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++block_number;
    }
}
