cmake_minimum_required(VERSION 3.12)
project(lab04 VERSION 0.0.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)  # Group CMake targets inside a folder
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)         # Generate compile_commands.json for language servers


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
        "/fsanitize=address"
    )
endif()

# Task 1 - Sort integers with algorithm
project(sortint)
set(SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/sortint.cpp"
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${SOURCE_FILES})

