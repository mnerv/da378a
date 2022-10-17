/**
 * @file   hello.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Google Test suites for cat language library.
 * @date   2022-10-17
 *
 * @copyright Copyright (c) 2022
 */
#include "gtest/gtest.h"

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

TEST(lexer, identifier) {
    cat::lexer lexer{"config dec"};
    auto const tokens = lexer.tokenize();
    for (auto const& token : tokens)
        ASSERT_EQ(cat::token_category::identifier, cat::token_type_category(token.type()));
}

TEST(lexer, numeric_negative) {
    constexpr auto numeric_literal = "-2";
    cat::lexer lexer{numeric_literal};
    auto const tokens = lexer.tokenize();
    ASSERT_NE(std::begin(tokens), std::end(tokens));
    ASSERT_EQ(std::string(numeric_literal), std::begin(tokens)->value());
}

TEST(lexer, numeric_positive) {
    constexpr auto numeric_literal = "+2";
    cat::lexer lexer{numeric_literal};
    auto const tokens = lexer.tokenize();
    ASSERT_EQ(std::string(numeric_literal), tokens.begin()->value());
}

auto main(int argc, char const* argv[]) -> int {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}
