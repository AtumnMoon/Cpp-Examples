/**
 * @file task_errors.h
 * @brief Defines the error codes used for task operations.
 *
 * This file contains the Task-related custom exceptions and TaskError enum
 * class, which provides standard error when task operations (like setting
 * description or marking complete) fail.
 *
 *
 * @author Moon
 */
#ifndef TO_DO_LIST_TASK_ERRORS_H_
#define TO_DO_LIST_TASK_ERRORS_H_

#include <stdexcept>

/**
 * @class TaskConstrucitonError
 * @brief Error that violates and invalidates construction of tasks
 *
 * Useful for situations where an error must be thrown when the caller violates
 * a must have (e.g. empty description).
 */
class TaskConstructionError : public std::logic_error {
 public:
  explicit TaskConstructionError(const std::string& message)
      : std::logic_error(message) {}
};

/**
 * @brief Defines the possible errors that can occur when modifying a task.
 *
 * These codes are returned by task modification functions to clearly indicate
 * why an operation (like changing the description or marking complete) failed.
 */
enum class TaskError {
  /// The task's description was left empty when an update was attempted.
  kEmptyDescription = 0,
  /// The task's description text was too long (exceeded 255 characters).
  kDescriptionTooLong,
  /// An attempt was made to change or modify a task that is already finished.
  kAlreadyComplete
};

#endif
