cmake_minimum_required(VERSION 3.12)
project(lab03 VERSION 0.0.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)  # Group CMake targets inside a folder
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)         # Generate compile_commands.json for language servers

if (NOT MSVC)
    add_compile_options(
        "-Wall"
        "-Wextra"
        "-Wconversion"
        "-Wpedantic"
        "-Wno-shadow"
        "-Werror"
    )
else()
    add_compile_options(
        "/W4"
        "/WX"
        "/fsanitize=address"
    )
endif()

# PersonReg static library
project(PersonReg)
set(TARGET_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/Person.hpp"
    "${PROJECT_SOURCE_DIR}/PersonReg.hpp"

    "${PROJECT_SOURCE_DIR}/Person.cpp"
    "${PROJECT_SOURCE_DIR}/PersonReg.cpp"
)
add_library(${PROJECT_NAME} OBJECT ${TARGET_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_SOURCE_DIR}"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${TARGET_SOURCE_FILES})

# SimpleTest Executable
project(SimpleTest)
set(TARGET_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/SimpleTest.cpp"
)
add_executable(${PROJECT_NAME} ${TARGET_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}"
)
target_link_libraries(${PROJECT_NAME} PersonReg)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${TARGET_SOURCE_FILES})

# PersonRegTest Executable
project(PersonRegTest)
set(TARGET_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/PersonRegTest.cpp"
)
add_executable(${PROJECT_NAME} ${TARGET_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}"
)
target_link_libraries(${PROJECT_NAME} PersonReg)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${TARGET_SOURCE_FILES})

