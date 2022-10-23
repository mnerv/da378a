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
        #"/fsanitize=address"
    )
endif()

# Task 1 - Sort integers with algorithm
set(TARGET_NAME sortint)
set(SOURCE_FILES
    "sortint.cpp"
)
add_executable(${TARGET_NAME} ${SOURCE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}"
)
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${SOURCE_FILES})

# Task 2 - Sort Person
set(TARGET_NAME sortperson)
set(SOURCE_FILES
    "PersonReg/PersonReg.hpp"
    "PersonReg/Person.hpp"
    "PersonReg/PersonReg.cpp"
    "PersonReg/Person.cpp"

    "sortperson.cpp"
)
add_executable(${TARGET_NAME} ${SOURCE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}"
)
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${SOURCE_FILES})

# Task 3 - Usage of std::remove_if
set(TARGET_NAME remif)
set(SOURCE_FILES
    "remif.cpp"
)
add_executable(${TARGET_NAME} ${SOURCE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}"
)
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${SOURCE_FILES})

