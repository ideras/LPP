#ifndef LPPFILEMANAGER_H
#define LPPFILEMANAGER_H

#include <ios>
#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "lpp_variant.h"

class LppFileManager
{
public:
    using StreamUPtr = std::unique_ptr<std::iostream>;
    static constexpr int Initial_File_Handles = 16;

    LppFileManager();
    ~LppFileManager();

    int openFile(const std::string& filepath, std::ios_base::openmode flags, int blk_size);
    int binaryRead(int fh, char *buffer, int size);
    bool binaryWrite(int fh, const char *buffer, int size);
    LppVariant textRead(int fh);
    bool textWrite(int fh, const LppVariant& val);
    bool closeFile(int fh);
    bool atEof(int fh);
    bool seekStart(int fh);
    bool seekEnd(int fh);
    bool seek(int fh, int pos);
    int  filePos(int fh);

private:
    std::iostream *getStream(int fh);
    int getNextFileHandle();

private:
    std::vector<StreamUPtr> open_files;
    std::unordered_map<int, int> file_info;
};

#endif // LPPFILEMANAGER_H
