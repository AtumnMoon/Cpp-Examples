#include "util.h"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <iostream>
#include <string>

namespace util {

// =========================================================================
//  UTILITY /  STRING MANIPULATION
// =========================================================================

/**
 * @brief Check if the character is a white space
 * Check if the character is a newline, white space, tab, carriage return, and
 * etc.
 * @param c The character to check
 * @return true The character is a white space
 * @return false The character is a not a white space
 */
bool is_whitespace(unsigned char c) { return std::isspace(c); }

/**
 * @brief Trim the leading whitespaces from a string
 *
 * @param s The raw string value with white spaces
 */
void ltrim(std::string& s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !is_whitespace(ch);
          }));
}

/**
 * @brief Trim the trailing whitespaces from a string
 *
 * @param s The raw string value with white spaces
 */
void rtrim(std::string& s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !is_whitespace(ch); })
              .base(),
          s.end());
}

/**
 * @brief Trims the leading and trailing white spaces from a string
 *
 * @param s The raw string value with white spaces
 * @return std::string The resulting string after removing the whitespaces
 */
std::string trim(std::string s) {
  rtrim(s);
  ltrim(s);
  return s;
}

// =========================================================================
//  UTILITY / I/O HANDLING
// =========================================================================

/**
 * @brief Converts string to integer safely
 *
 * @param str Read-only string to be converted into integer
 * @return std::optional<int> The parsed integer value if conversion succeeded,
 * or empty if conversion failed.
 */
std::optional<int> string_to_int(const std::string& str) {
  int result = 0;
  const auto [ptr, ec] =
      std::from_chars(str.data(), str.data() + str.size(), result);

  if (ec == std::errc() && ptr == str.data() + str.size()) {
    return result;
  }

  return std::nullopt;
}

/**
 * @brief Show the prompt and get the user input.
 *
 * @param prompt The prompt to be shown to the user
 * @return std::optional<std::string> The trimmed user input, or empty if a
 * fatal I/O error occurred.
 */
std::optional<std::string> get_user_input(std::string_view prompt) {
  std::string input;
  std::cout << prompt;

  if (!std::getline(std::cin, input)) {
    // Check for fatal stream error (e.g., Ctrl+D/Z)
    std::cerr << "ERROR: Fatal error in reading input stream.\n";
    return std::nullopt;
  }

  return trim(input);
}

/**
 * @brief Get the user input through but with safety.
 *
 * @param prompt The prompt to be shown to the user
 * @param out_selection The user input but converted into integer
 * @return true The operation is a success
 * @return false The operation failed
 */
bool get_menu_selection(std::string_view prompt, int& out_selection) {
  while (true) {
    std::optional<std::string> input_opt = get_user_input(prompt);

    if (!input_opt.has_value()) {
      return false;
    }

    if (input_opt->empty()) {
      std::cerr << "ERROR: Input cannot be empty. Please try again.\n";
      continue;
    }

    if (std::optional<int> selection_opt = string_to_int(*input_opt);
        selection_opt.has_value()) {
      out_selection = *selection_opt;
      return true;
    }

    std::cerr << "ERROR: Invalid input. Please enter a number.\n";
  }
}

}  // namespace util