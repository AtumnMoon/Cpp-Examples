cmake_minimum_required(VERSION 4.1.2)
project(
    cpp_examples
    LANGUAGES CXX
)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Third party resources
# add_subdirectory(extern/abseil-cpp)
add_subdirectory(extern/googletest)

# My own projects
add_subdirectory(src/simple-calculator)
add_subdirectory(src/to-do-list)
