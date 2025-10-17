cmake_minimum_required(VERSION 4.1.2)
project(util VERSION 1.0 LANGUAGES CXX)

set(
    UTIL_FILE_SOURCES
    util_file.h
    util_file.cc
)

set(
    UTIL_IO_SOURCES
    util_io.h
    util_io.cc
)

set(
    UTIL_MATH_SOURCES
    util_math.h
    util_math.cc
)

set(
    UTIL_STRING_SOURCES
    util_string.h
    util_string.cc
)

set(
    UTIL_TIME_SOURCES
    util_time.h
    util_time.cc
)

set(
    PROJECT_SOURCES
    ${UTIL_FILE_SOURCES}
    ${UTIL_IO_SOURCES}
    ${UTIL_MATH_SOURCES}
    ${UTIL_STRING_SOURCES}
    ${UTIL_TIME_SOURCES}
)

add_library(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)