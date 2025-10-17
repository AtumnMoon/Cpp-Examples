#include "util_io.h"

namespace util::io {

// =========================================================================
//  UTILITY / I/O HANDLING
// =========================================================================

/**
 * Implementation of get_line_input.
 */
std::string get_line_input(const std::string& prompt) {
  std::string input;
  std::cout << prompt;
  // Use std::getline to safely read an entire line, including spaces.
  std::getline(std::cin, input);

  // Check if the stream failed (e.g., Ctrl+D/Ctrl+Z pressed)
  if (std::cin.fail()) {
    std::cin.clear();  // Clear the fail flag
    return ""; // Return an empty string and let the user dev handle it
  }

  return input;
}

}  // namespace util::io
