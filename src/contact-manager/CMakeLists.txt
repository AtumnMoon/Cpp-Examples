cmake_minimum_required(VERSION 4.1.2)
project(contact_manager VERSION 1.0 LANGUAGES CXX)

set(
    CONTACT_MANAGER_SOURCES
    contact_manager.h
    contact_manager.cc
)

set(
    EXTERNAL_SOURCES
    json.hpp
)

set(
    PROJECT_SOURCES
    main.cc
    ${CONTACT_MANAGER_SOURCES}
    ${EXETERNAL_SOURCES}
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(${PROJECT_NAME} PRIVATE util)