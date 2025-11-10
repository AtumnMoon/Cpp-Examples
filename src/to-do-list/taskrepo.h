/**
 * @file task_repo.h
 * @brief Defines the TaskRepo interface for managing To-Do List tasks.
 *
 * This header file establishes the abstract contract (TaskRepo) for all data
 * operations related to the Task structure. It is designed to be
 * storage-agnostic, meaning implementers can use a database, file, or in-memory
 * map without changing this interface.
 *
 * This file uses standard C++ features like std::expected (for clear error
 * results) and std::optional (for clear "value not found" results).
 *
 * @author Moon
 */
#ifndef TO_DO_LIST_TASK_REPO_H_
#define TO_DO_LIST_TASK_REPO_H_

#include <cstdint>
#include <expected>
#include <optional>
#include <vector>

#include "task.h"
#include "task_errors.h"

/**
 * @brief Blueprint for managing To-Do List Tasks.
 *
 * This defines a standard way to Save, Read, Update, and Delete (CRUD) tasks,
 * regardless of where the data is actually kept (like a database, a file, or
 * memory). Think of it as the **Boss** that handles all storage requests for
 * your to-do items.
 */
class TaskRepo {
 public:
  /**
   * @brief Required for proper cleanup when the TaskRepo is no longer needed.
   */
  virtual ~TaskRepo() = default;

  /**
   * @brief Adds a brand new task to the list.
   *
   * @param task The task details to be saved.
   * @return std::expected<std::uint64_t, TaskError> Returns the **new unique
   * ID** of the saved task on success. If something goes wrong (e.g., input
   * data is bad), it returns a **TaskError** instead.
   */
  virtual std::expected<std::uint64_t, TaskError> addTask(const Task& task) = 0;

  /**
   * @brief Modifies an existing task.
   *
   * @param task The task object containing the new information (must include a
   * valid ID).
   * @return std::expected<void, TaskError> Returns **success** if the task was
   * updated. If the task ID doesn't exist or there's a problem saving, it
   * returns a **TaskError**.
   */
  virtual std::expected<void, TaskError> updateTask(const Task& task) = 0;

  /**
   * @brief Permanently removes a task from the list using its ID.
   *
   * @param id The unique number identifying the task to remove.
   * @return std::expected<void, TaskError> Returns **success** if the task was
   * removed. If the ID is not found or there's a storage issue, it returns a
   * **TaskError**.
   */
  virtual std::expected<void, TaskError> deleteTask(std::uint64_t id) = 0;

  /**
   * @brief Gets every single task currently stored.
   *
   * @return std::vector<Task> A simple list of all tasks. This list will be
   * empty if there are no tasks.
   */
  virtual std::vector<Task> getAllTasks() = 0;

  /**
   * @brief Finds a specific task using its unique ID number.
   *
   * It uses `std::optional` because it's completely normal for a search to
   * simply **find nothing**.
   *
   * @param id The unique number of the task you want to find.
   * @return std::optional<Task> The task object if it exists, or **nothing** if
   * no task matches the ID.
   */
  virtual std::optional<Task> getTaskByID(std::uint64_t id) = 0;
};

#endif
