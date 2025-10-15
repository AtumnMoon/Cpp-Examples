#ifndef UTIL_H
#define UTIL_H

#include <optional>
#include <string>

namespace util {

// =========================================================================
//  UTILITY /  STRING MANIPULATION
// =========================================================================

void ltrim(std::string& s);
void rtrim(std::string& s);

std::string trim(std::string s);

// =========================================================================
//  UTILITY / I/O HANDLING
// =========================================================================

std::optional<int> string_to_int(const std::string& str);
std::optional<std::string> get_user_input(std::string_view prompt);

bool get_menu_selection(std::string_view prompt, int& out_selection);

}  // namespace util

#endif