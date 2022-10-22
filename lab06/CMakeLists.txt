cmake_minimum_required(VERSION 3.21)
project(catc VERSION 0.0.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)  # Group CMake targets inside a folder
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)         # Generate compile_commands.json for language servers

# cat language library
set(TARGET_NAME cat)
set(TARGET_SOURCE_FILES
    "ast.hpp"
    "interpreter.hpp"
    "lexer.hpp"
    "parser.hpp"
    "token.hpp"

    "ast.cpp"
    "interpreter.cpp"
    "lexer.cpp"
    "parser.cpp"
    "token.cpp"
)
add_library(${TARGET_NAME} OBJECT ${TARGET_SOURCE_FILES})
target_include_directories(${TARGET_NAME} PUBLIC "${PROJECT_SOURCE_DIR}")
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
if (NOT MSVC AND NOT WIN32)
    target_compile_options(${TARGET_NAME} PRIVATE
        "-Wall"
        "-Wextra"
        "-Wconversion"
        "-Wpedantic"
        "-Wshadow"
        "-Werror"
    )
else()
    target_compile_options(${TARGET_NAME} PRIVATE
        "/W4"
        "/WX"
        "/utf-8"
        #"/fsanitize=address"  # Doesn't work without Visual Studio
    )
endif()
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${TARGET_SOURCE_FILES})

# catc program
set(TARGET_NAME ${PROJECT_NAME})
set(TARGET_SOURCE_FILES "catc.cpp")
add_executable(${TARGET_NAME} ${TARGET_SOURCE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}")
target_link_libraries(${TARGET_NAME} PRIVATE cat)
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
if (NOT MSVC AND NOT WIN32)
    target_compile_options(${TARGET_NAME} PRIVATE
        "-Wall"
        "-Wextra"
        "-Wconversion"
        "-Wpedantic"
        "-Wshadow"
        "-Werror"
    )
else()
    target_compile_options(${TARGET_NAME} PRIVATE
        "/W4"
        "/WX"
        #"/fsanitize=address"  # Doesn't work without Visual Studio
    )
endif()
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${TARGET_SOURCE_FILES})

# Unit tests with Google Test
find_package(GTest CONFIG)
if (GTest_FOUND)
add_subdirectory(tests)
endif()
