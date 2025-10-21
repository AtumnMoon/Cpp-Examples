cmake_minimum_required(VERSION 4.1.2)
project(template VERSION 1.0 LANGUAGES CXX)

set(
    PROJECT_SOURCES
    template.cc
)

add_library(${PROJECT_NAME} ${PROJECT_SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_compile_options(${PROJECT_NAME}
    PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:${COMMON_WARNING_FLAGS} -Werror>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# To Allow other projects to use the library
target_include_directories(${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
