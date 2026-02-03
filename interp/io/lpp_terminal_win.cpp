#include <iostream>
#include <vector>
#include <unordered_map>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <windows.h>
#include "lpp_terminal.h"

std::unordered_map<int, int> key_map = {
    { 0xe050, KeyDown },
    { 0xe048, KeyUp },
    { 0xe04b, KeyLeft },
    { 0xe04d, KeyRight },
    { 0xe047, KeyHome },
    { 0xe04f, KeyEnd },
    { 0x0008, KeyBackspace },
    { 0xe053, KeyDelete },
    { 0xe052, KeyInsert },
    { 0xe051, KeyPgDown },
    { 0xe049, KeyPgUp },
    { 0x000d, KeyEnter },
};

Terminal::Terminal()
    : cp(Color::White, Color::Black)
{
    setColor(cp);
    setCursorPos({1, 1});
}

Terminal::~Terminal()
{
}

void Terminal::clear()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    BOOL bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    if (!bSuccess) return;

    DWORD con_size = csbi.dwSize.X * csbi.dwSize.Y;
    
    COORD coord = { 0, 0 };
    DWORD chars_written;
    bSuccess = FillConsoleOutputCharacter( hConsole, static_cast<TCHAR>(' '),
                                          con_size, coord, &chars_written);
    if (!bSuccess) return;

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    if (!bSuccess) return;

    bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
                                          con_size, coord, &chars_written);
    if (!bSuccess) return;

    SetConsoleCursorPosition(hConsole, coord);
}

void Terminal::setColor(const ColorPair& cp)
{
    this->cp = cp;

    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);

    WORD attr = (static_cast<WORD>(cp.foreground) & 0x0f) 
                | ((static_cast<WORD>(cp.background) & 0x0f) << 4);

    SetConsoleTextAttribute(h_console, attr);
}

ColorPair Terminal::getColor() const
{
    return cp;
}

void Terminal::setCursorPos(const TermPos& pos)
{
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cpos;

    cpos.X = static_cast<SHORT>(pos.column) - 1;
    cpos.Y = static_cast<SHORT>(pos.row) - 1;

    SetConsoleCursorPosition(h_console, cpos);
}

TermPos Terminal::getCursorPos()
{
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO cinfo;
    
    GetConsoleScreenBufferInfo(h_console, &cinfo);

    return { cinfo.dwCursorPosition.Y + 1, cinfo.dwCursorPosition.X + 1};
}

bool Terminal::kbhit()
{
    return (_kbhit() != 0);
}

int Terminal::getch()
{
    int key = _getch();

    if (key == 0xe0) {
        key = (0xe000 | (_getch() & 0xff));
    }
    auto it = key_map.find(key);
    
    return (it != key_map.end())? it->second : key;
}
