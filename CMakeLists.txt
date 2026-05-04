cmake_minimum_required(VERSION 4.2)

project(idk_core VERSION 0.0.1)

add_library(
    ${PROJECT_NAME} STATIC
)
target_compile_features(
    ${PROJECT_NAME} PUBLIC cxx_std_23
)
target_compile_options(
    ${PROJECT_NAME} PUBLIC -Werror -Wall -Wextra
)
target_include_directories(
    ${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/h"
)
target_sources(
    ${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/assert.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/cfgparser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/file.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/log.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/memory.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/port.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/service.cpp"
)
