#include "util_time.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace util::time {

// =========================================================================
//  UTILITY / TIME AND DATE HANDLING
// =========================================================================

/**
 * Implementation of current_time_ms.
 * Uses std::chrono::system_clock for epoch time.
 */
long long current_time_ms() {
  using namespace std::chrono;
  // Get time point
  auto now = system_clock::now();

  // Calculate duration since epoch
  auto duration = now.time_since_epoch();

  // Convert to milliseconds and return as long long
  return duration_cast<milliseconds>(duration).count();
}

/**
 * Implementation of format_timestamp.
 * Uses C++ standard library functions for formatting.
 */
std::string format_timestamp(long long timestamp_ms,
                             const std::string& format) {
  // Convert milliseconds to seconds
  std::time_t timestamp_s = timestamp_ms / 1000;

  // Get local time structure (tm)
  std::tm* local_time = std::localtime(&timestamp_s);

  if (local_time == nullptr) {
    return "Error formatting time";
  }

  // Use stringstream to format the output
  std::stringstream ss;
  ss << std::put_time(local_time, format.c_str());

  return ss.str();
}

}  // namespace util::time
