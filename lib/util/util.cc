#include "util.h"

#include <algorithm>
#include <cctype>

namespace util {

bool is_whitespace(unsigned char c) { return std::isspace(c); }

void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !is_whitespace(ch);
          }));
}

void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !is_whitespace(ch); })
              .base(),
          s.end());
}

std::string trim(std::string s) {
  rtrim(s);
  ltrim(s);
  return s;
}

} // namespace util