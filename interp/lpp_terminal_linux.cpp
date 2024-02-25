#include <iostream>
#include <vector>
#include <unordered_map>
#include <termios.h>
#include <unistd.h>
#include "lpp_terminal.h"

static constexpr const char Reset_Term[] = "\033[m";
static constexpr const char ClearScreen_Code[] = "\033[2J\033[1;1f";
static constexpr const char Forecolor_Code[] = "\033[38;5;";
static constexpr const char Backcolor_Code[] = "\033[48;5;";

int ansi_color[] = {
    0,  // Black
    18, // Dark blue
    28, // Dark green
    39, // Dark cyan
    88, // Dark red
    91, // Purple
    100, // Dark yellow
    251, // Light grey
    244, // Grey
    21, // Blue
    40, // Green
    51, // Cyan
    196, // Red
    201, // Magenta
    226, // Yellow
    15, // White
};

static inline int mapToAnsiColor(Color color)
{
    int icolor = static_cast<int>(color) % 16;

    return ansi_color[icolor];
}

class KeyInput
{
public:
    KeyInput();
    ~KeyInput();

    bool kbhit();
    int getch();

private:
    struct termios prev_settings, curr_settings;
    int peek_ch;
};

KeyInput::KeyInput()
{
    tcgetattr(STDIN_FILENO, &prev_settings);
    curr_settings = prev_settings;
    curr_settings.c_lflag &= ~(ICANON | ECHO | ISIG);
    curr_settings.c_cc[VMIN] = 1;
    curr_settings.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &curr_settings);
    peek_ch = -1;
}
    
KeyInput::~KeyInput()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &prev_settings);
}

bool KeyInput::kbhit()
{
    unsigned char ch;
    int nread;

    if (peek_ch != -1) {
        return true;
    }

    curr_settings.c_cc[VMIN] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &curr_settings);
    nread = read(0, &ch, 1);
    curr_settings.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &curr_settings);

    if (nread > 0) {
        peek_ch = ch;
        return true;
    }
    return false;
}
    
int KeyInput::getch()
{
    char ch;

    if (peek_ch != -1){
        ch = peek_ch;
        peek_ch = -1;
    } else {
        read(STDIN_FILENO, &ch, 1);
    }

    return ch;
}

Terminal::Terminal()
  : cp(Color::White, Color::Black),
    key_input(new KeyInput)
{
    setColor(cp);
    setCursorPos({1, 1});
}
    
Terminal::~Terminal()
{ 
    std::cout << Reset_Term << std::flush;
}

void Terminal::clear()
{
    std::cout << ClearScreen_Code << std::flush;
}

void Terminal::setColor(const ColorPair& cp)
{
    this->cp = cp;
    std::cout << Forecolor_Code << mapToAnsiColor(cp.foreground) << 'm'
              << Backcolor_Code << mapToAnsiColor(cp.background) << 'm'
              << std::flush;
              
}

ColorPair Terminal::getColor() const
{
    return cp;
}

void Terminal::setCursorPos(const TermPos& pos)
{
    std::cout << "\033[" << pos.row << ";" << pos.column << "f" << std::flush;
}

TermPos Terminal::getCursorPos()
{
    std::cout << "\033[6n" << std::flush;
    std::vector<char> buffv(32);

    int read_count = read(STDIN_FILENO, buffv.data(), buffv.size());
    if (read_count <= 0) {
        return {1, 1};
    }

    const char *p = buffv.data();
    const char *end = (buffv.data() + read_count);
    
    if (*p++ != '\x1B')
        return {1, 1};
    if (*p++ != '\x5B')
        return {1, 1};

    int row = 0;
    while (p < end && *p != ';') {
        row = row * 10 + (*p - '0');
        p++;
    }
    p++;
    int col = 0;
    while (p < end && *p != 'R') {
        col = col * 10 + (*p - '0');
        p++;
    }
    return TermPos{row, col};
}
    
bool Terminal::kbhit()
{
    return key_input->kbhit();
}
    
int Terminal::getch()
{
    return key_input->getch();
}
