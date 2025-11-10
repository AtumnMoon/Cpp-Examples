#include <exception>
#include <stdexcept>

#include "simple_task.h"
#include "task_errors.h"

int main() {
  try {
    SimpleTask task("");
  } catch (const TaskConstructionError& e) {
    std::cerr << "Task Construction Failure:" << e.what() << std::endl;
  } catch (const std::logic_error& e) {
    std::cerr << "Generic Logic Error: " << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Unknown Standard Error: " << e.what() << std::endl;
  }

  return 0;
}
