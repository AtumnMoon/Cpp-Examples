#ifndef UTIL_H
#define UTIL_H

#include <string>

namespace util {

void ltrim(std::string &s);
void rtrim(std::string &s);

std::string trim(std::string s);
} // namespace util

#endif