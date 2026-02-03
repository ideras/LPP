#ifndef __LPP_TERMINAL_H__
#define __LPP_TERMINAL_H__

#include <string>
#include <memory>

enum Key {
    KeyEnter     = 0x000A,
    KeyEsc       = 0x001B,
    KeyBackspace = 0x007f,
    KeyUp        = 0x8041,
    KeyDown      = 0x8042,
    KeyLeft      = 0x8044,
    KeyRight     = 0x8043,
    KeyHome      = 0x8048,
    KeyEnd       = 0x8046,
    KeyDelete    = 0x8033,
    KeyInsert    = 0x8032,
    KeyPgDown    = 0x8036,
    KeyPgUp      = 0x8035,
};

enum class Color {
    Black, DarkBlue, DarkGreen, DarkCyan, DarkRed, Purple, DarkYellow,
    LightGrey, Grey, Blue, Green, Cyan, Red, Magenta, Yellow, White 
};

struct ColorPair {
    ColorPair(Color fg, Color bg)
      : foreground(fg), background(bg)
    {}

    ColorPair(const ColorPair& other) = default;

    Color foreground;
    Color background;
};

struct TermPos {
    TermPos(int row, int col)
      : row(row), column(col)
    {}

    TermPos(const TermPos& other) = default;

    int row;
    int column;
};

#if defined(__linux__) || defined(__APPLE__)
class KeyInput;
#endif

class Terminal
{
public:
    Terminal();
    ~Terminal();

    void clear();
    void setTextColor(Color _color);
    void setBackColor(Color _color);
    void setColor(const ColorPair& cp);
    ColorPair getColor() const;
    void setCursorPos(const TermPos& pos);
    TermPos getCursorPos();
    void writeString(const std::string& str);
    void writeInt(int val);
    void writeChar(char ch);
    void writeReal(double val);
    bool kbhit();
    int getch();

    std::string readString();
    int readInt();
    double readReal();
    char readChar();
    bool readBool();

private:
    void readString(std::string& text, int max_len, int box_size, const ColorPair& cp);    

private:
    ColorPair cp;

#if defined(__linux__) || defined(__APPLE__)
    std::unique_ptr<KeyInput> key_input;
#endif
};

 #endif
