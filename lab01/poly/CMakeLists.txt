cmake_minimum_required(VERSION 3.12)
project(polysolver)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/poly2.cpp"
    "${PROJECT_SOURCE_DIR}/poly2.h"
    "${PROJECT_SOURCE_DIR}/polysolver.cpp"
)
add_executable(${PROJECT_NAME} ${TARGET_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}"
)
if (NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        "-Wall"
        "-Wextra"
        "-Wconversion"
        "-Wpedantic"
        "-Wshadow"
        "-Werror"
    )
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        "/W4"
        "/WX"
    )
endif()
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${TARGET_SOURCE_FILES})

