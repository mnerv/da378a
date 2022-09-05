cmake_minimum_required(VERSION 3.12)
project(lab01)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT MSVC)
    add_compile_options(
        "-Wall"
        "-Wextra"
        "-Wconversion"
        "-Wpedantic"
        "-Wshadow"
        "-Werror"
    )
else()
    add_compile_options(
        "/W4"
        "/WX"
    )
endif()

project("hello")
set(HELLO_SOURCE_FILES "hello.cpp")
add_executable(${PROJECT_NAME} ${HELLO_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${HELLO_SOURCE_FILES})

project("sum")
set(SUM_SOURCE_FILES "sum.cpp")
add_executable(${PROJECT_NAME} ${SUM_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${SUM_SOURCE_FILES})

add_subdirectory(poly)
