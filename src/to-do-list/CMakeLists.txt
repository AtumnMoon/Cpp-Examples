cmake_minimum_required(VERSION 4.1.2)

# The project settings
# Name: to-do-list
# Version: 1.0 in development
# Language: C++
project(to-do-list VERSION 1.0 LANGUAGES CXX)

# Set all your source file here
set(
    PROJECT_SOURCES
    main.cc
)

# The binary/executable, leave it as is
# It uses the project name to be the name of the executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Use the latest C++ 23
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

# Set warnings as error, to help correct code
# It won't compile if there is an error btw
target_compile_options(${PROJECT_NAME}
    PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:${COMMON_WARNING_FLAGS} -Werror>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

# Set the output directory to be "build/bin"
# Separating exectubles from libraries
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# ======= Unit testing using Google Test =======
find_package(GTest REQUIRED)

# The test executable for unit testing
add_executable(to-do-list-test
    # This executable will contain all test implementation files.
    simple_task_test.cc
    task.cc
    # Headers often need to be listed for certain toolchains
    task_errors.h
    simple_task.h
)

# Link the required libraries and set dependencies for the test executable.
target_link_libraries(to-do-list-test
    PRIVATE
    GTest::gtest_main
)

# Apply the same C++ standard to the test executable.
target_compile_features(to-do-list-test PRIVATE cxx_std_23)

# Apply the same warning settings to the test executable.
target_compile_options(to-do-list-test
    PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:${COMMON_WARNING_FLAGS} -Werror>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

# Set the output directory for the test executable.
set_target_properties(to-do-list-test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Enables GoogleTest to automatically find and run this executable as a test suite.
include(GoogleTest)
gtest_discover_tests(to-do-list-test)
