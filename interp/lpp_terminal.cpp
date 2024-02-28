#include <iostream>
#include "lpp_terminal.h"
#include "str_util.h"

void Terminal::setTextColor(Color _color)
{
    ColorPair cp = getColor();
    cp.foreground = _color;

    setColor(cp);
}

void Terminal::setBackColor(Color _color)
{
    ColorPair cp = getColor();
    cp.background = _color;
    
    setColor(cp);
}

void Terminal::writeString(const std::string& str)
{
    std::cout << str << std::flush;
}

void Terminal::writeInt(int val) 
{
    std::cout << val << std::flush;
}

void Terminal::writeReal(double val) 
{
    std::cout << str::formatReal(val) << std::flush;
}

void Terminal::writeChar(char c) 
{
    std::cout << c << std::flush;
}

std::string Terminal::readString()
{
    std::string text("");

    readString(text, 512, 32, {Color::Yellow, Color::Blue});

    return text;
}

int Terminal::readInt()
{
    std::string text;
    readString(text, 10, 10, {Color::Yellow, Color::Blue});

    try { return std::stoi(text); }
    catch (std::invalid_argument const& ex) {
        return 0;
    }
    catch (std::out_of_range const& ex) {
        return 0;
    } 
}

double Terminal::readReal()
{
    std::string text;
    readString(text, 16, 10, {Color::Yellow, Color::Blue});

    try { return std::stod(text); }
    catch (std::invalid_argument const& ex) {
        return 0.0;
    }
    catch (std::out_of_range const& ex) {
        return 0.0;
    } 
}

char Terminal::readChar()
{
    std::string text;
    readString(text, 1, 2, {Color::Yellow, Color::Blue});
    
    return text.empty()? 0 : text[0];
}

bool Terminal::readBool()
{
    std::string text;
    readString(text, 9, 10, {Color::Yellow, Color::Blue});

    return (str::lower(text) == "falso")? false : true;
}

void Terminal::readString(std::string &text, int max_len, int box_size, const ColorPair &cp)
{
    auto print = [this](const char *str, int len) {
        const char *p = str;

        while (*p != '\0' && len-- > 0) {
            std::cout << *p++;
        }
    };

    TermPos orig_pos = getCursorPos();
    ColorPair orig_colorp = getColor();
    
    setColor(cp);
    std::string spaces(box_size, ' ');
    std::cout << spaces;

    int start_pos, cursor_pos;
    if (text.length() < box_size) {
        start_pos = 0;
        cursor_pos = text.length();
    }
    else {
        start_pos = text.length() - box_size + 1;
        cursor_pos = box_size - 1;
    }

    if (!text.empty()) {
        setCursorPos(orig_pos);
        print(&text[start_pos], box_size);
    }
    
    setCursorPos({orig_pos.row, orig_pos.column + cursor_pos});
    std::cout << std::flush;

    bool insert = true;
    int key;
    do {
        bool update_screen = true;
        key = getch();
        
        switch (key) {
            case KeyRight:
                if (cursor_pos < box_size-1 && cursor_pos < text.length())
                    cursor_pos++;
                else if (start_pos + box_size <= text.length())
                    start_pos++;
                break;

            case KeyLeft:
                if (cursor_pos > 0)
                    cursor_pos--;
                else if (start_pos > 0)
                    start_pos--;
                break;

            case KeyHome:
                cursor_pos = 0;
                start_pos = 0;
                break;

            case KeyEnd:
                if (text.length() > box_size) {
                    start_pos = text.length() - box_size + 1;
                    cursor_pos = box_size - 1;
                } else {
                    cursor_pos = text.length();
                }
                break;

            case KeyInsert:
                insert = !insert;
                break;

            case KeyBackspace:
                if (text.length() > 0 && cursor_pos > 0) {
                    text.erase(start_pos + cursor_pos - 1, 1);
                    if (cursor_pos > 0) {
                        if ( (start_pos + box_size) > text.length() && (start_pos > 0))
                            start_pos--;
                        else
                            cursor_pos--;
                    } else if (start_pos > 0)
                        start_pos--;
                }
                break;

            case KeyDelete:
                if (text.length() > 0 && (start_pos + cursor_pos) < text.length()) {
                    text.erase(start_pos + cursor_pos, 1);
                    if (start_pos > 0) {
                        start_pos--;
                    }
                }
                break;

            case KeyEnter:
            case KeyEsc:
                break;

            default: {
                if ((key < 32) || (key > 255)) {
                    update_screen = false;
                    break;
                }

                if (insert) {
                    if (text.length() >= max_len) {
                        break;
                    }

                    text.insert(start_pos + cursor_pos, 1, static_cast<char>(key));
                } else {
                    if (start_pos + cursor_pos < max_len) {
                        if (start_pos + cursor_pos == text.length()) {
                            text += static_cast<char>(key);
                        } else {
                            text[start_pos + cursor_pos] = static_cast<char>(key);
                        }
                    }
                }

                if (cursor_pos < (box_size - 1) && cursor_pos < text.length())
                    cursor_pos++;
                else if (start_pos + box_size <= text.length())
                    start_pos++;
            }
        }
        if (update_screen) {
            setColor(cp);
            setCursorPos(orig_pos);
            std::cout << spaces;

            setCursorPos(orig_pos);
            print(&text[start_pos], box_size);
            setCursorPos({orig_pos.row, orig_pos.column + cursor_pos});
            std::cout << std::flush;
        }
    } while ( (key != KeyEnter) && (key != KeyEsc) );

    setColor(orig_colorp);
}
