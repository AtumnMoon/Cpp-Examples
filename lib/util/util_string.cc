#include "util_string.h"

#include <algorithm>
#include <sstream>
#include <vector>

namespace util::string {

// =========================================================================
//  UTILITY /  STRING MANIPULATION
// =========================================================================

/**
 * Implementation of left_trim.
 */
std::string& left_trim(std::string& s) {
  // Find the first character that is not a space
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
  return s;
}

/**
 * Implementation of right_trim.
 */
std::string& right_trim(std::string& s) {
  // Find the first character from the reverse end that is not a space
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
  return s;
}

/**
 * Implementation of trim.
 */
std::string& trim(std::string& s) { return left_trim(right_trim(s)); }

/**
 * Implementation of to_lower.
 */
std::string& to_lower(std::string& s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return s;
}

/**
 * Implementation of to_upper.
 */
std::string& to_upper(std::string& s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  return s;
}

std::vector<std::string> split(const std::string& s, char delimiter,
                               bool include_empty) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream token_stream(s);

  // Use std::getline to extract tokens up to the delimiter
  while (std::getline(token_stream, token, delimiter)) {
    if (!token.empty() || include_empty) {
      tokens.push_back(token);
    }
  }

  // Handle the case where the string ends with a delimiter (and include_empty
  // is true)
  if (include_empty && s.length() > 0 && s.back() == delimiter) {
    tokens.push_back("");
  }

  return tokens;
}

}  // namespace util::string
