cmake_minimum_required(VERSION 3.12)
project(lab02)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)  # Group CMake targets inside a folder

add_subdirectory(sieve)
add_subdirectory(strmod)
