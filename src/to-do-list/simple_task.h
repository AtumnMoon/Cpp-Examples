/**
 * @file simple_task.h
 * @brief Defines a basic, fully functional to-do item.
 *
 * This file declares the 'SimpleTask' class, which is a concrete
 * implementation of the Task blueprint. It handles basic information
 * like the description text and whether the task is finished.
 *
 * @author Moon
 */
#ifndef TO_DO_LIST_SIMPLE_TASK_H_
#define TO_DO_LIST_SIMPLE_TASK_H_

#include <cstdint>
#include <expected>
#include <string>

#include "task.h"
#include "task_errors.h"

/**
 * @class SimpleTask
 * @brief A standard, manageable to-do item.
 *
 * This class implements the full behavior of a task, including
 * storing its description and managing its completion status.
 */
class SimpleTask : public Task {
 public:
  /**
   * @brief Creates a new, pending (not finished) task.
   * @param description The initial text that describes the task.
   */
  SimpleTask(const std::string& description)
      : description_(std::move(description)), is_complete_(false) {
    if (description.empty()) {
      throw TaskConstructionError(
          "Simple Task Error: Description must not be empty.");
    }
  }

  /**
   * @brief Gets the identifier of the task.
   * @return std::uint64_t The task's id.
   */
  std::uint64_t GetId() const override { return id_; }

  /**
   * @brief Gets the text that describes what the task is about.
   * @return std::string The task's descriptive text.
   */
  std::string GetDescription() const override { return description_; }

  /**
   * @brief Checks if the task has been finished.
   * @retval true The task is done.
   * @retval false The task is still pending.
   */
  bool IsComplete() const override { return is_complete_; }

  /**
   * @brief Changes the descriptive text of the task.
   *
   * The new description is checked to ensure it is not empty and
   * does not exceed the maximum length (255 characters).
   *
   * @param description The new text for the task.
   * @return std::expected<void, TaskError> Empty on success, or an
   * error code if it failed validation.
   */
  std::expected<void, TaskError> SetDescription(
      const std::string& description) override {
    // Size validation
    if (description.empty()) {
      return std::unexpected<TaskError>{TaskError::kEmptyDescription};
    }

    // Length validation
    if (description.length() > 255) {
      return std::unexpected<TaskError>{TaskError::kDescriptionTooLong};
    }

    description_ = std::move(description);
    return {};
  }

  /**
   * @brief Marks the task as complete (finished).
   *
   * Once a task is marked complete, it cannot be marked complete again.
   *
   * @return std::expected<void, TaskError> Empty on success, or an
   * error code if the task was already done.
   */
  std::expected<void, TaskError> MarkComplete() override {
    if (is_complete_) {
      return std::unexpected<TaskError>{TaskError::kAlreadyComplete};
    }

    is_complete_ = true;
    return {};
  }

  /**
   * @brief Converts the task to texual representation
   *
   * Converts the task into a format of SimpleTask { ID: id_, Completion Status:
   * is_complete_, Description: description_}.
   *
   * @return std::string The textual representation of task.
   */
  std::string ToString() const override {
    return "SimpleTask { ID: " + std::to_string(id_) +
           ", Completion Status: " + std::to_string(is_complete_) +
           ", Description: " + description_ + "}";
  }

 private:
  /// The task identifier
  std::uint64_t id_{};

  /// The completion status
  bool is_complete_{};

  /// The textual description of task
  std::string description_{};
};

#endif
