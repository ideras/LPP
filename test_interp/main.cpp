#include <iostream>
#include "lpp_filemanager.h"

extern std::unordered_map<std::string, std::string> file_map;

int main()
{
    LppFileManager file_mgr;

    file_map["test.txt"] = "";
    int fh = file_mgr.openFile("test.txt", std::ios::out);
    file_mgr.writeFile(fh, "This is a test", 14);
    file_mgr.closeFile(fh);

    std::cout << file_map["test.txt"] << '\n';
    return 0;
}