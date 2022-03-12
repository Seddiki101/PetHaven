#ifndef MISC_H
#define MISC_H
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool has_any_digits(const std::string& s)
{
    return std::any_of(s.begin(), s.end(), ::isdigit);
}

#endif // MISC_H
