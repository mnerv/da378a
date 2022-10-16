cmake_minimum_required(VERSION 3.12)
project(lab05 VERSION 0.0.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)  # Group CMake targets inside a folder
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)         # Generate compile_commands.json for language servers

find_package(GTest CONFIG)

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
        #"/fsanitize=address"  # Doesn't work without Visual Studio
    )
endif()

# string library as object file linkage
set(SOURCE_FILES
    "string.hpp"
    "string.cpp"
)
add_library(string OBJECT ${SOURCE_FILES})
target_include_directories(string PUBLIC "${PROJECT_SOURCE_DIR}")
target_compile_features(string PRIVATE cxx_std_20)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${SOURCE_FILES})

# testing application with Google Test
if (GTest_FOUND)
set(SOURCE_FILES
    "strtest.cpp"
)
add_executable(strtest ${SOURCE_FILES})
target_include_directories(strtest PRIVATE
    "${PROJECT_SOURCE_DIR}"
)
target_compile_features(strtest PRIVATE cxx_std_20)
target_link_libraries(strtest
    string
    GTest::gtest
)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${SOURCE_FILES})
endif()

# main test file
set(SOURCE_FILES "main201025.cpp")
add_executable(maintest ${SOURCE_FILES})
target_include_directories(maintest PRIVATE "${PROJECT_SOURCE_DIR}")
target_compile_features(maintest PRIVATE cxx_std_20)
target_link_libraries(maintest string)
if (NOT MSVC)
    target_compile_options(maintest PRIVATE "-Wno-error")
else()
    target_compile_options(maintest PRIVATE "/WX-" "/utf-8")
endif()
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${SOURCE_FILES})

