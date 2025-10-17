#ifndef UTIL_TIME_H
#define UTIL_TIME_H

#include <string>

namespace util::time {

// =========================================================================
//  UTILITY / TIME AND DATE HANDLING
// =========================================================================

/**
 * @brief Gets the current system timestamp as milliseconds since the epoch.
 *
 * @return long long The current time in milliseconds (long long).
 */
long long current_time_ms();

/**
 * @brief Converts a long long timestamp (milliseconds) to a formatted string.
 *
 * @param timestamp_ms The timestamp in milliseconds.
 * @param format The format string (e.g., "%Y-%m-%d %H:%M:%S").
 * @return std::string The formatted time string.
 */
std::string format_timestamp(long long timestamp_ms,
                             const std::string& format = "%Y-%m-%d %H:%M:%S");

}  // namespace util::time

#endif
