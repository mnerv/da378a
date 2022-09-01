/**
 * @file   hello.cpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  Task 01 - 03
 *         01. Compile and link the program using command line tools.
 *             Linux/macOS (clang)
 *             clang++ -std=c++20 -Wall -Wextra -Wconversion -Wpedantic -Wshadow -Werror hello.cpp
 *
 *             Windows
 *             cl /std:c++20 /W4 /WX /EHsc hello.cpp
 * @date   2022-08-31
 */
#include <cstdint>
#include <iostream>

auto main([[maybe_unused]]int argc, [[maybe_unused]]char const* argv[]) -> int {
    std::cout << "Hello, World!\n";
    return 0;
}

