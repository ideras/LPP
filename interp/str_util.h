#ifndef _STR_UTIL_H_
#define _STR_UTIL_H_

#include <string>
#include <algorithm>

namespace str {

// trim from left
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from right
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from left & right
inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}

template<class Iter>
Iter split(const std::string &s, const std::string &delim, Iter out)
{
    if (delim.empty()) {
        *out++ = s;
        return out;
    }
    size_t a = 0, b = s.find(delim);
    for ( ; b != std::string::npos; )
    {
        *out++ = std::move(s.substr(a, b - a));
        a = b + delim.length();
        b = s.find(delim, a);
    }
    *out++ = std::move(s.substr(a, s.length() - a));
    return out;
}

inline std::string upper(const std::string &str) {
    std::string result = str;

    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

inline std::string lower(const std::string &str) {
    std::string result = str;

    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

struct iequals
{
    bool operator()(const std::string& a, const std::string& b) const
    {
        return std::equal(a.begin(), a.end(), b.begin(), b.end(),
                          [](char c1, char c2) {
                              return  std::tolower(static_cast<unsigned char>(c1)) ==
                                      std::tolower(static_cast<unsigned char>(c2));
                          });
    }
};

inline static std::string formatReal(double value)
{
    std::string str = std::to_string(value);

    auto last = str.end() - 1;
    while (*last == '0') {
        last--;
    }

    if (*last == '.') {
        last += 2;
    } else {
        last ++;
    }

    if (last != str.end()) {
        str.erase(last);
    }

    return str;
}

}

#endif
