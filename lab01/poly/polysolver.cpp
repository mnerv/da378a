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
 *         10. Read coefficients by std::cin
 *
 *         11. Read coefficients by redirect
 *             Usage: (./polysolver < coeffs.txt) > roots.txt
 *
 * @date   2022-09-02
 */
#include <cstdint>
#include <iostream>
#include "poly2.h"

int main([[maybe_unused]]int argc, [[maybe_unused]]char const* argv[])
{
    std::cout << "Root-finding started...\n";
    constexpr std::size_t MAX_COEFFS = 3;
    float coeffs[MAX_COEFFS];
    float input = 0.0f;
    std::size_t input_count = 0;
    while (std::cin >> input) {
        coeffs[input_count++] = input;
        if (input_count > MAX_COEFFS - 1) {
            input_count = 0;

            std::int32_t root_count;
            float x1, x2;
            Poly2 poly(coeffs[0], coeffs[1], coeffs[2]);
            poly.findRoots(root_count, x1, x2);
            std::cout << "roots: " << root_count << "\n";
            std::cout << "   x1: " << x1 << ", x2: " << x2 << ", ";
            if (root_count == 1) {
                std::cout << "f(x1) = " << poly.eval(x1) << "\n";
            } else if (root_count == 2) {
                std::cout << "f(x1) = " << poly.eval(x1) << ", ";
                std::cout << "f(x2) = " << poly.eval(x1) << "\n";
            }
        }
    }
    return 0;
}

