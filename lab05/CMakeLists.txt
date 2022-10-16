cmake_minimum_required(VERSION 3.12)
project(string VERSION 0.0.0)
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
        #"-fprofile-instr-generate"
        #"-fcoverage-mapping"
    )
    #add_link_options(
        #"-fprofile-instr-generate"
    #)
else()
    add_compile_options(
        "/W4"
        "/WX"
        #"/fsanitize=address"  # Doesn't work without Visual Studio
    )
endif()

# string library as object file linkage
set(TARGET_NAME string)
set(TARGET_SOURCE_FILES
    "string.hpp"
    "string.cpp"
)
add_library(${TARGET_NAME} OBJECT ${TARGET_SOURCE_FILES})
target_include_directories(${TARGET_NAME} PUBLIC "${PROJECT_SOURCE_DIR}")
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${TARGET_SOURCE_FILES})

# testing application with Google Test
if (GTest_FOUND)
set(TARGET_NAME strtest)
set(TARGET_SOURCE_FILES
    "strtest.cpp"
)
add_executable(${TARGET_NAME} ${TARGET_SOURCE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}"
)
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
target_link_libraries(${TARGET_NAME}
    string
    GTest::gtest
)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${TARGET_SOURCE_FILES})
endif()

# main test file
set(TARGET_NAME maintest)
set(TARGET_SOURCE_FILES "main201025.cpp")
add_executable(${TARGET_NAME} ${TARGET_SOURCE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}")
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
target_link_libraries(${TARGET_NAME} string)
if (NOT MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE "-Wno-error")
else()
    target_compile_options(${TARGET_NAME} PRIVATE "/WX-" "/utf-8")
endif()
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${TARGET_SOURCE_FILES})

