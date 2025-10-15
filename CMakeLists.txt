cmake_minimum_required(VERSION 4.1.2)
project(
    examples
    LANGUAGES CXX
)

set(CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendor/abseil-cpp)
add_subdirectory(lib/util)
add_subdirectory(src/contact-manager)
add_subdirectory(src/exam-calculator)