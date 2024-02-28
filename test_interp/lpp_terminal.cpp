#include <sstream>
#include "lpp_terminal.h"
#include "str_util.h"

std::ostringstream oss;

#if defined(__linux__) || defined(__APPLE__)
class KeyInput {};
#endif

Terminal::Terminal(): cp(Color::White, Color::Black)
{ oss.str(""); }

Terminal::~Terminal() {}

void Terminal::clear()
{ }

void Terminal::setTextColor(Color _color) {}
void Terminal::setBackColor(Color _color) {}
void Terminal::setColor(const ColorPair& cp) {}

ColorPair Terminal::getColor() const
{ return {Color::White, Color::Black}; }

void Terminal::setCursorPos(const TermPos& pos) {}

TermPos Terminal::getCursorPos()
{ return {1, 1}; }

bool Terminal::kbhit()
{ return false; }

int Terminal::getch()
{ return 0; }

std::string Terminal::readString()
{ return "Esta es un cadena"; }

int Terminal::readInt()
{ return 134; }

double Terminal::readReal()
{ return 3.14159; }

char Terminal::readChar()
{ return 'C'; }

bool Terminal::readBool()
{ return true; }


void Terminal::writeString(const std::string& str)
{
    oss << str;
}

void Terminal::writeInt(int val) 
{
    oss << val;
}

void Terminal::writeReal(double val) 
{
    oss << str::formatReal(val);
}

void Terminal::writeChar(char c) 
{
    oss << c;
}
