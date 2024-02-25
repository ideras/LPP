#include <iostream>
#include <sstream>
#include <unordered_map>
#include "lpp_filemanager.h"
#include "lpp_serializer.h"
#include "str_util.h"

std::unordered_map<std::string, std::string> file_map;
static std::unordered_map<int, std::string> filename_map;

LppFileManager::LppFileManager(): open_files(Initial_File_Handles)
{}

LppFileManager::~LppFileManager()
{}

int LppFileManager::openFile(const std::string &filepath, std::ios::openmode flags, int blk_size)
{
    auto it = file_map.find(filepath);
    if (it == file_map.end()) {
        return -1;
    }

    StreamUPtr upf = std::make_unique<std::stringstream>(flags);

    reinterpret_cast<std::stringstream *>(upf.get())->str(it->second);
    int fh = getNextFileHandle();
    open_files[fh] = std::move(upf);
    filename_map[fh] = it->first;

    return fh;
}

bool LppFileManager::closeFile(int fh)
{
    if (fh >=0 && fh < open_files.size()) {
        StreamUPtr& upf = open_files.at(fh);
        
        std::string filename = filename_map[fh];
        filename_map.erase(fh);

        file_map[filename] = reinterpret_cast<std::stringstream *>(upf.get())->str();

        upf = nullptr;

        return true;
    }
    return false;
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
    std::iostream *ios = getStream(fh);

    if (!ios) {
        return false;
    }
    ios->seekg(pos, std::ios::beg);
    ios->seekp(pos, std::ios::beg);

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

int LppFileManager::binaryRead(int fh, char *buffer, int size)
{
    if (fh >=0 && fh < open_files.size()) {
        std::iostream *ios = getStream(fh);

        if (!ios) {
            return false;
        }

        ios->read(buffer, size);
        return ios->gcount();
    }
    return -1;
}

bool LppFileManager::binaryWrite(int fh, const char *buffer, int size)
{
    if (fh >=0 && fh < open_files.size()) {
        std::iostream *ios = getStream(fh);

        if (!ios) {
            return false;
        }

        ios->write(buffer, size);
        return !ios->bad();
    }
    return false;
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