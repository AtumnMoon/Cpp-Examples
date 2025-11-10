#include "task.h"

#include <ostream>

/**
 * Implementation of Task::operator<<(std::ostream& os, const Task& task)
 * overload
 */
std::ostream& operator<<(std::ostream& os, const Task& task) {
  os << task.ToString();
  return os;
}
