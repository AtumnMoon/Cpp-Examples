// The Google Test framework.
#include "gtest/gtest.h"

// The files to test
#include "simple_task.h"
#include "task_errors.h"

// Passing Test: Construction of SimpleTask is a success
TEST(SimpleTaskConstructorTest, InitializesSuccessfully) {
  // Purpose: Verify that a valid description creates the task correctly.

  // Create a task using a valid string.
  SimpleTask task("Write C++ unit tests.");

  // ASSERT_EQ checks if the actual value matches the expected value.
  // We expect the description we read back to equal the one we passed in.
  ASSERT_EQ(task.GetDescription(), "Write C++ unit tests.");
}

// Exception Test: Empty description on SimpleTask Construction
TEST(SimpleTaskConstructorTest, ThrowsErrorOnEmptyDescription) {
  // Purpose: Verify that passing an empty string to the constructor
  // correctly throws a TaskConstructionError.

  // Use a Google Test ASSERTION.
  // ASSERT_THROW checks if the code block inside its first argument
  // throws the exception type specified in its second argument.
  ASSERT_THROW(SimpleTask(""),        // Code that is expected to throw
               TaskConstructionError  // The specific exception we expect
  );
}
