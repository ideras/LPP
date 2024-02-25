#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include "lpp_terminal.h"

int main(int argc, char *argv[])
{
    Terminal term;

    //term.clear();
    term.setCursorPos({1, 1});
    term.writeString("Hello World: ");
    term.setCursorPos({2, 1});
    term.writeString("Hello World: ");
    term.setCursorPos({5, 1});
    term.setTextColor(Color::Green);
    term.setBackColor(Color::Black);
    term.writeString("Hello World: ");
    std::string text = term.readString();
    term.writeString(text);
    int val = term.readInt();
    term.writeInt(val);
    double valr = term.readReal();
    term.writeReal(valr);
    char ch = term.readChar();
    term.writeChar(ch);
    bool valb = term.readBool();
    term.writeString(valb? "Verdadero" : "Falso");

    while (!term.kbhit()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
