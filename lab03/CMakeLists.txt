cmake_minimum_required(VERSION 3.12)
project(lab03 VERSION 0.0.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(SimpleTest)
set(TARGET_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/Person.hpp"
    "${PROJECT_SOURCE_DIR}/PersonReg.hpp"

    "${PROJECT_SOURCE_DIR}/Person.cpp"
    "${PROJECT_SOURCE_DIR}/PersonReg.cpp"
    "${PROJECT_SOURCE_DIR}/SimpleTest.cpp"
)
add_executable(${PROJECT_NAME} ${TARGET_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
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
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${TARGET_SOURCE_FILES})

