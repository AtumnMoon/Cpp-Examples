cmake_minimum_required(VERSION 4.1.2)
project(util VERSION 1.0 LANGUAGES CXX)

set(
    PROJECT_SOURCES STATIC
    util.cc
    util.h
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