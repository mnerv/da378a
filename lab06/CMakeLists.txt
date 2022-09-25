cmake_minimum_required(VERSION 3.12)
project(catc VERSION 0.0.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)  # Group CMake targets inside a folder
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)         # Generate compile_commands.json for language servers

set(SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/lexer.hpp"
    "${PROJECT_SOURCE_DIR}/token.hpp"

    "${PROJECT_SOURCE_DIR}/lexer.cpp"
    "${PROJECT_SOURCE_DIR}/token.cpp"
    "${PROJECT_SOURCE_DIR}/catc.cpp"
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
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
        #"/fsanitize=address"  # Doesn't work without Visual Studio
    )
endif()
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${SOURCE_FILES})

