#ifndef __SERIALIZER_HELPER_H__
#define __SERIALIZER_HELPER_H__

#include <string>
#include <vector>

// std::string toHexString(const char* bytes, int size);
std::string toHexString(const std::vector<char>& bytes);
std::string toHexString(const std::string& bytes);
std::vector<char> toByteVector(const std::string& hex_str);

#endif
