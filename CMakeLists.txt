cmake_minimum_required(VERSION 3.5)

project(idk_core VERSION 0.0.1)
# add_compile_options(-Werror -Wall -Wextra)

add_library(
    ${PROJECT_NAME} STATIC
)
target_compile_features(
    ${PROJECT_NAME} PUBLIC cxx_std_23
)
target_include_directories(
    ${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/h"
)
target_link_libraries(
    ${PROJECT_NAME} PRIVATE libidk
)
target_sources(
    ${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/file.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/port.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/service.cpp"
)
    
# set(VANE_SRCPATH "${CMAKE_SOURCE_DIR}/vane/src")
# set(VANE_INCPATH "${CMAKE_SOURCE_DIR}/vane/inc")
# set(THIRDPARTY_PREFIX "${CMAKE_SOURCE_DIR}/external/install/")
# set(THIRDPARTY_INCPATH "${THIRDPARTY_PREFIX}/include")

# add_subdirectory(vane)
# add_subdirectory(vanegame)

