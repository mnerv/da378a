/**
 * @file   sum.cpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  Task 04 - 07. Calculator and streams redirections
 *         Linux/macOS (clang)
 *         clang++ -std=c++20 -Wall -Wextra -Wconversion -Wpedantic -Wshadow -Werror sum.cpp -o sum
 *
 *         Windows
 *         cl /std:c++20 /W4 /WX /EHsc sum.cpp
 *
 *         04. Simple sum program
 *             Usage: ./sum
 *
 *             Enter a number and then press enter.
 *             Use ctrl+d to exit on Unix-based machines or ctrl+x on Windows.
 *
 *             The program will output the sum result on the last line.
 *
 *         05. Output-redirect to file
 *             Usage: ./sum > sum.txt
 *                    ctrl+d to exit
 *
 *         06. Input-redirect from file
 *             Usage: ./sum < terms.txt
 *
 *             terms.txt: 1 2 3 4
 * @date   2022-09-01
 */
#include <cstdint>
#include <iostream>

auto main([[maybe_unused]]int argc, [[maybe_unused]]char const* argv[]) -> int {
    std::int32_t sum = 0;
    std::int32_t in  = 0;
    while (std::cin >> in) sum += in;
    std::cout << sum << "\n";;
    return 0;
}

