/**
 * @file task.h
 * @brief Defines the blueprint for any item in a to-do list.
 *
 * This file declares the basic contract (interface) that all specific
 * kinds of tasks must follow. This contract specifies the common
 * abilities and information shared by every task, such as its
 * description, status, and actions.
 *
 * @author Moon
 */
#ifndef TO_DO_LIST_TASK_H_
#define TO_DO_LIST_TASK_H_

#include <cstdint>  // Provides standard integer types.
#include <expected>  // A modern utility for returning a successful result or an error message.
#include <iostream>  // Required for std::ostream used in the print operator.
#include <string>    // For handling text descriptions.

#include "task_errors.h"  // Includes the definitions for specific errors this class can return.

/**
 * @class Task
 * @brief A blueprint (interface) for any to-do item.
 *
 * This abstract class defines the fundamental abilities that all tasks must
 * have. Since it is a blueprint, you cannot create a 'Task' object directly.
 * You must create a specific type of task that inherits from it.
 */
class Task {
 public:
  /**
   * @brief Ensures safe cleanup when a task object is deleted.
   *
   * This is a standard C++ practice for base classes (virtual destructor)
   * to guarantee that when an object is deleted via a base class pointer,
   * the memory is correctly managed for all specific derived task types.
   */
  virtual ~Task() = default;

  /**
   * @brief Retrieves the unique identification number of the task.
   * @return std::uint64_t The task's unique ID.
   */
  virtual std::uint64_t GetId() const = 0;

  /**
   * @brief Retrieves the main text describing what the task is about.
   * @return std::string The task's descriptive text.
   */
  virtual std::string GetDescription() const = 0;

  /**
   * @brief Checks the current status to see if the task has been finished.
   * @retval true The task is complete.
   * @retval false The task is still pending.
   */
  virtual bool IsComplete() const = 0;

  /**
   * @brief Allows the user to change or update the descriptive text of the
   * task.
   * @param description The new, non-empty text for the task.
   * @return std::expected<void, TaskError> Returns a success signal (void)
   * or an error code (TaskError) if the operation failed.
   */
  virtual std::expected<void, TaskError> SetDescription(
      const std::string& description) = 0;

  /**
   * @brief Marks the task as complete.
   * @return std::expected<void, TaskError> Returns a success signal (void)
   * on success, or an error code (TaskError) if the task could not be
   * marked complete.
   */
  virtual std::expected<void, TaskError> MarkComplete() = 0;

  /**
   * @brief Creates a concise, human-readable text summary of the task's state.
   * @return std::string A textual representation of the task, useful for
   * logging or debugging.
   */
  virtual std::string ToString() const = 0;

  /**
   * @brief Overloads the stream insertion operator (<<) for easy printing.
   *
   * This non-member friend function allows any Task object to be directly
   * printed using standard C++ output streams (like std::cout).
   * It relies on the virtual ToString() method to generate the content.
   *
   * @param os The output stream.
   * @param task The task object to be printed.
   * @return std::ostream& A reference to the output stream, which allows
   * you to chain multiple print operations.
   */
  friend std::ostream& operator<<(std::ostream& os, const Task& task);
};

#endif
