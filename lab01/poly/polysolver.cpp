/**
 * @file   polysolver.cpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  Task 08 - 11. Polynomial solver
 *         Linux/macOS (clang)
 *         clang++ -std=c++20 -Wall -Wextra -Wconversion -Wpedantic -Wshadow -Werror -c poly2.cpp -o poly2.o
 *         clang++ -std=c++20 -Wall -Wextra -Wconversion -Wpedantic -Wshadow -Werror poly2.o polysolver.cpp -o polysolver
 *
 *         Windows
 *         cl /std:c++20 /W4 /WX /EHsc /c poly2.cpp
 *         cl /std:c++20 /W4 /WX /EHsc /c polysolver.cpp
 *         link /out:polysolver.exe poly2.obj polysolver.obj
 *
 *         08. Implement poly2 eval and findRoots
 *
 *         09. findRoots return value by parameter
 *
 * @date   2022-09-02
 */
#include <cstdint>
#include <iostream>
#include "poly2.h"

int main([[maybe_unused]]int argc, [[maybe_unused]]char const* argv[])
{
    std::cout << "Root-finding started...\n";
    std::int32_t root_count;
    float root_a, root_b;

    Poly2 poly1(1.0f, 2.0f, 1.0f);
    std::cout << "x = -1.0: f(x) = " << poly1.eval(-1.0f) << "\n";
    poly1.findRoots(root_count, root_a, root_b);
    std::cout << "roots: " << root_count << ", x1: " << root_a << ", x2: " << root_b << "\n";

    Poly2 poly2(2.0f, -1.0f, -1.0f);
    std::cout << "x = -0.5: f(x) = " << poly2.eval(-0.5f) << ", ";
    std::cout << "x = -1.0: f(x) = " << poly2.eval(1.0f)  << "\n";
    poly2.findRoots(root_count, root_a, root_b);
    std::cout << "roots: " << root_count << ", x1: " << root_a << ", x2: " << root_b << "\n";

    Poly2 poly3(1.0f, 1.0f, 1.0f);
    std::cout << "x = 0.0:  f(x) = " << poly3.eval(0.0f) << "\n";
    poly3.findRoots(root_count, root_a, root_b);
    std::cout << "roots: " << root_count << ", x1: " << root_a << ", x2: " << root_b << "\n";
    return 0;
}

