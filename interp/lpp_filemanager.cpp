#include <iostream>
#include <fstream>
#include "lpp_filemanager.h"
#include "lpp_serializer.h"

LppFileManager::LppFileManager(): open_files(Initial_File_Handles)
{}

LppFileManager::~LppFileManager()
{}

int LppFileManager::openFile(const std::string &filepath, std::ios::openmode flags, int blk_size)
{
    StreamUPtr upf = std::make_unique<std::fstream>(filepath.c_str(), flags);
    if (!reinterpret_cast<std::fstream *>(upf.get())->is_open()) {
        return -1;
    }
    int fh = getNextFileHandle();
    open_files[fh] = std::move(upf);
    file_info[fh] = blk_size;

    return fh;
}

int LppFileManager::binaryRead(int fh, char *buffer, int size)
{
    std::iostream *ios = getStream(fh);

    if (!ios) {
        return -1;
    }

    ios->read(buffer, size);
    return ios->gcount();
}

bool LppFileManager::binaryWrite(int fh, const char *buffer, int size)
{
    std::iostream *ios = getStream(fh);

    if (!ios) {
        return false;
    }

    ios->write(buffer, size);
    return !ios->bad();
}

bool LppFileManager::closeFile(int fh)
{
    std::iostream *ios = getStream(fh);

    if (!ios) {
        return false;
    }

    reinterpret_cast<std::fstream *>(ios)->close();
    open_files[fh] = nullptr;

    return true;
}

bool LppFileManager::atEof(int fh)
{
    std::iostream *ios = getStream(fh);

    if (!ios) {
        return false;
    }

    return ios->eof();
}

bool LppFileManager::seekStart(int fh)
{
    std::iostream *ios = getStream(fh);

    if (!ios) {
        return false;
    }
    ios->seekg(0, std::ios::beg);
    ios->seekp(0, std::ios::beg);

    return true;
}

bool LppFileManager::seekEnd(int fh)
{
    std::iostream *ios = getStream(fh);

    if (!ios) {
        return false;
    }
    ios->seekg(0, std::ios::end);
    ios->seekp(0, std::ios::end);

    return true;
}

bool LppFileManager::seek(int fh, int pos)
{
    auto it = file_info.find(fh);
    if (it == file_info.end() || it->second == 0) {
        return false;
    }
    int blk_size = it->second;
    std::iostream *ios = getStream(fh);

    if (!ios) {
        return false;
    }
    ios->seekg(pos * blk_size, std::ios::beg);
    ios->seekp(pos * blk_size, std::ios::beg);

    return true;
}

int LppFileManager::filePos(int fh)
{
    std::iostream *ios = getStream(fh);

    if (!ios) {
        return -1;
    }
    return ios->tellg();
}

std::iostream *LppFileManager::getStream(int fh)
{
    if (fh >= 0 && fh < open_files.size()) {
        StreamUPtr& upf = open_files.at(fh);

        return upf.get();
    }
    return nullptr;
}

int LppFileManager::getNextFileHandle()
{
    for (int i = 0; i < open_files.size(); i++) {
        if (open_files[i] == nullptr) {
            return i;
        }
    }
    open_files.push_back(nullptr);

    return open_files.size() - 1;
}

LppVariant LppFileManager::textRead(int fh)
{
    std::iostream *ios = getStream(fh);

    if (!ios) {
        return LppVariant::Empty;
    }

    std::string str;
    std::getline(*ios, str);

    if (str.empty()) {
        return LppVariant::Empty;
    }

    return LppSerializer::fromString(str);
}

bool LppFileManager::textWrite(int fh, const LppVariant &val)
{
    std::iostream *ios = getStream(fh);

    if (!ios) {
        return false;
    }

    std::string str = LppSerializer::toString(val);

    ios->write(str.c_str(), str.length());
    ios->write("\n", 1);
    ios->flush();

    return true;
}
