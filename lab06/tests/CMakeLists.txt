cmake_minimum_required(VERSION 3.21)
project(tests)

set(TARGET_NAME lexertest)
set(TARGET_SOURCE_FILES "lexertest.cpp")
add_executable(${TARGET_NAME} ${TARGET_SOURCE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}")
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
target_link_libraries(${TARGET_NAME} cat GTest::gtest)
if (NOT MSVC)
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

set(TARGET_NAME parsertest)
set(TARGET_SOURCE_FILES "parsertest.cpp")
add_executable(${TARGET_NAME} ${TARGET_SOURCE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}")
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
target_link_libraries(${TARGET_NAME} cat GTest::gtest)
if (NOT MSVC)
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

set(TARGET_NAME interpretertest.cpp)
set(TARGET_SOURCE_FILES "interpretertest.cpp")
add_executable(${TARGET_NAME} ${TARGET_SOURCE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}")
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
target_link_libraries(${TARGET_NAME} cat GTest::gtest)
if (NOT MSVC)
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
