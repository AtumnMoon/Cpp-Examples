#ifndef UTIL_IO_H
#define UTIL_IO_H

#include <iostream>
#include <limits>
#include <string>

namespace util::io {

// =========================================================================
//  UTILITY / I/O HANDLING
// =========================================================================

/**
 * @brief Prompts the user and safely reads a string of input from the console.
 *
 * This function ensures that the entire line of input is captured and
 * handles potential state issues in the input stream.
 *
 * @param prompt The message to display to the user before reading input.
 * @return std::string The string entered by the user.
 */
std::string get_line_input(const std::string& prompt);

/**
 * @brief Prompts the user for a value of a specified numeric type (e.g., int,
 * float, double).
 *
 * This function continuously prompts the user until a valid value of type T
 * is successfully read. It clears the error state of the stream and discards
 * remaining input on failure.
 *
 * @tparam T The numeric type to read (e.g., int, double).
 * @param prompt The message to display to the user.
 * @return T The validated numeric value entered by the user.
 */
template <typename T>
T get_numeric_input(const std::string& prompt) {
  T value{};
  while (true) {
    std::cout << prompt;
    // Attempt to read the value
    if (std::cin >> value) {
      // Check if there are extra characters after the number (e.g., '123a')
      if (std::cin.peek() == '\n' || std::cin.peek() == EOF) {
        // Input is valid: clear the newline from the buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
      }
    }

    // Input failed or had extra characters: handle the error
    std::cout << "Invalid input. Please enter a valid number.\n";

    // Clear the error flags
    std::cin.clear();

    // Discard the rest of the line to prevent infinite loop
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

}  // namespace util::io

#endif
