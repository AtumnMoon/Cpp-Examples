#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#include <fstream>
#include <iostream>
#include <string>

namespace util::file {

// =========================================================================
//  UTILITY / GENERIC FILE I/O AND SERIALIZATION
// =========================================================================

/**
 * @brief Saves a serializable object to a file.
 *
 * This function requires the object's type (T) to have an implemented
 * stream insertion operator (operator<<) to serialize itself.
 *
 * @tparam T The type of the object to save.
 * @param filename The path to the file.
 * @param object The constant reference to the object to be saved.
 * @return bool True if the operation succeeded, false otherwise.
 */
template <typename T>
bool save_to_file(const std::string& filename, const T& object) {
  // Open the file for writing (std::ios::out)
  std::ofstream ofs(filename);

  if (!ofs.is_open()) {
    std::cerr << "Error: Could not open file for writing: " << filename << "\n";
    return false;
  }

  // Use the object's defined stream insertion operator
  ofs << object;

  // Check if the write operation failed
  if (ofs.fail()) {
    std::cerr << "Error: Failed to write data to file: " << filename << "\n";
    ofs.close();
    return false;
  }

  ofs.close();
  return true;
}

/**
 * @brief Loads a serializable object from a file.
 *
 * This function requires the object's type (T) to have an implemented
 * stream extraction operator (operator>>) to deserialize itself.
 *
 * @tparam T The type of the object to load.
 * @param filename The path to the file.
 * @param object The reference to the object where loaded data will be stored.
 * @return bool True if the operation succeeded, false otherwise.
 */
template <typename T>
bool load_from_file(const std::string& filename, T& object) {
  // Open the file for reading (std::ios::in)
  std::ifstream ifs(filename);

  if (!ifs.is_open()) {
    // This is often not a fatal error (e.g., file doesn't exist yet)
    // so we print a note and return false.
    std::cerr << "Note: Could not open file for reading (may not exist): "
              << filename << "\n";
    return false;
  }

  // Use the object's defined stream extraction operator
  ifs >> object;

  // Check for reading errors (like corrupt data or end-of-file reached
  // prematurely)
  if (ifs.fail() && !ifs.eof()) {
    std::cerr << "Error: Failed to read all data from file: " << filename
              << "\n";
    ifs.close();
    return false;
  }

  ifs.close();
  return true;
}

}  // namespace util::file

#endif
