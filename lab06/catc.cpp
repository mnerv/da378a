/**
 * @file   catc.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  catc is a mini project interpreter for the C@ (cat) language.
 *         This program compiles and interpret the C@ code.
 *
 *         Functionality requirements:
 *           - Read code from a source file
 *           - Parse and execute according to the C@ grammar. Add your own code
 *             (or code suggested by a teacher)
 *           - Output sends to the std::ostream, such as std::cout (standard out)
 *           - Terminals defined by regular expressions (int and variable)
 *             should be matched properly to the provided pattern. int-tokens
 *             should be matched before being ast to C++ integers.
 * @date   2022-09-15
 *
 * @copyright Copyright (c) 2022
 */
#include <iostream>

#include "lexer.hpp"

[[maybe_unused]]constexpr auto test_source = R"(config dec
print 1 + 1
print 3 + 3 * 3
print ( 3 + 3 ) * 3
x = 2 - -2
y = x
z = y * ( 16 / ( y - 2 ) )
print x
print y
print z
config hex
print z
config bin
print z
)";

[[maybe_unused]]constexpr auto out_source = R"(2
12
18
4
4
32
0x20
0000000000100000
)";

auto main([[maybe_unused]]int argc, [[maybe_unused]]char const* argv[]) -> int {
    cat::lexer lexer{test_source};
    auto tokens = lexer.tokenize();
    for (auto const& token : tokens) {
        std::cout << token.str() << "\n";
    }
    return 0;
}

