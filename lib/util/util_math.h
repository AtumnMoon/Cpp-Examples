#ifndef UTIL_MATH_H
#define UTIL_MATH_H

#include <algorithm>  // For std::min and std::max in clamp

namespace util::math {

// =========================================================================
//  UTILITY / MATH OPERATIONS
// =========================================================================

/**
 * @brief Calculates the power of a base to an integer exponent.
 *
 * This is safer and often faster than std::pow for integer exponents.
 * Uses template to work with any numeric type (int, float, double).
 *
 * @tparam T The numeric type of the base.
 * @param base The base number.
 * @param exp The integer exponent.
 * @return The result of base raised to the power of exp.
 */
template <typename T>
T power(T base, int exp) {
  if (exp == 0) return T{1};
  if (exp < 0) return T{1} / power(base, -exp);  // Handle negative exponents

  T result = T{1};
  while (exp > 0) {
    // If exp is odd, multiply result by base
    if (exp & 1) {
      result *= base;
    }
    // Square the base and halve the exponent
    base *= base;
    exp >>= 1;  // Same as exp = exp / 2
  }
  return result;
}

/**
 * @brief Clamps a value between a minimum and maximum boundary.
 *
 * Ensures the result is always within [min_val, max_val].
 *
 * @tparam T The type of the value and boundaries.
 * @param value The value to clamp.
 * @param min_val The lower bound.
 * @param max_val The upper bound.
 * @return The clamped value.
 */
template <typename T>
T clamp(T value, T min_val, T max_val) {
  return std::max(min_val, std::min(value, max_val));
}

}  // namespace util::math

#endif
