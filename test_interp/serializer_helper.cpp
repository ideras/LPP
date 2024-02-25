#include <string>
#include <vector>

std::string toHexString(const char* bytes, int size)
{
    static const char *digits = "0123456789abcdef";

    std::string str("");
    str.reserve(size * 2);

    for (int i = 0; i < size; i++) {
        str += digits[static_cast<unsigned char>(bytes[i]) >> 4];
        str += digits[static_cast<unsigned char>(bytes[i]) & 0x0f];
    }

    return str;
}

template <typename Iter>
std::string toHexString(Iter beg, Iter end)
{
    static const char *digits = "0123456789abcdef";

    std::string str("");
    str.reserve((end - beg) * 2);

    Iter it = beg;
    while (it != end) {
        char ch = *it++;
        str += digits[static_cast<unsigned char>(ch) >> 4];
        str += digits[static_cast<unsigned char>(ch) & 0x0f];
    }

    return str;
}

std::string toHexString(const std::string& bytes)
{
    return toHexString(bytes.begin(), bytes.end());
}

std::string toHexString(const std::vector<char>& bytes)
{
    return toHexString(bytes.data(), bytes.size());
}

std::vector<char> toByteVector(const std::string& hex_str)
{
    std::vector<char> bytes;
    auto hexd = [](char hd) {
        return (hd >= '0' && hd <= '9')? (hd - '0') : (tolower(hd) - 'a' + 0xa);
    };

    bytes.reserve((hex_str.length() / 2));
    for (int i = 0; i < hex_str.length(); i += 2) {
        char ch = (hexd(hex_str[i]) << 4) | hexd(hex_str[i + 1]);
        bytes.push_back(ch);
    }

    return bytes;
}
