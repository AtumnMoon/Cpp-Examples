#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include <string>
#include <vector>

namespace util::string {

// =========================================================================
//  UTILITY /  STRING MANIPULATION
// =========================================================================

/**
 * @brief Removes leading whitespace from a string.
 *
 * @param s The string to trim.
 * @return std::string& A reference to the modified string.
 */

std::string& left_trim(std::string& s);

/**
 * @brief Removes trailing whitespace from a string.
 *
 * @param s The string to trim.
 * @return std::string& A reference to the modified string.
 */
std::string& right_trim(std::string& s);

/**
 * @brief Removes leading and trailing whitespace from a string.
 *
 * @param s The string to trim.
 * @return std::string& A reference to the modified string.
 */
std::string& trim(std::string& s);

/**
 * @brief Converts a string to all lowercase characters.
 *
 * @param s The string to convert.
 * @return std::string& A reference to the modified string.
 */
std::string& to_lower(std::string& s);

/**
 * @brief Converts a string to all uppercase characters.
 *
 * @param s The string to convert.
 * @return std::string& A reference to the modified string.
 */
std::string& to_upper(std::string& s);

/**
 * @brief Splits a string into a vector of strings based on a delimiter.
 *
 * @param s The input string to split.
 * @param delimiter The character to split the string by.
 * @param include_empty If true, empty strings resulting from consecutive delimiters are included.
 * @return std::vector<std::string> A std::vector<std::string> containing the tokens.
 */
std::vector<std::string> split(const std::string& s, char delimiter, bool include_empty = false);

}  // namespace util::string

#endif
