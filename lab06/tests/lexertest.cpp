/**
 * @file   lexertest.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Lexer test suites for cat language library.
 * @date   2022-10-17
 *
 * @copyright Copyright (c) 2022
 */
#include <string>

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

TEST(lexer, consume_space) {
    cat::lexer lexer{"                                "};
    auto const tokens = lexer.tokenize();
    ASSERT_EQ(0, tokens.size());
}

TEST(lexer, consume_whitespace) {
    cat::lexer lexer{"                                \n\t"};
    auto const tokens = lexer.tokenize();
    ASSERT_EQ(0, tokens.size());
}

TEST(lexer, string_literal) {
    using namespace std::string_literals;
    constexpr auto str = "\"Hello, World!\"";
    cat::token tk(cat::token_type::string_literal, str);
    cat::lexer lexer{str};
    auto const tokens = lexer.tokenize();
    ASSERT_NE(0, tokens.size());
    ASSERT_EQ("Hello, World!"s, tokens[0].value());
}

TEST(lexer, numeric_literal) {
    for (std::size_t i = 0; i < 10; ++i) {
        auto const source = std::to_string(i);
        cat::lexer lexer{source};
        auto const tokens = lexer.tokenize();
        ASSERT_NE(std::begin(tokens), std::end(tokens));
        EXPECT_EQ(source, std::begin(tokens)->value());
    }
}

TEST(lexer, operator_plus) {
    cat::lexer lexer{"+"};
    auto const tokens = lexer.tokenize();
    ASSERT_NE(std::begin(tokens), std::end(tokens));
    ASSERT_EQ(cat::token_type::plus, std::begin(tokens)->type());
}

TEST(lexer, operator_minus) {
    cat::lexer lexer{"-"};
    auto const tokens = lexer.tokenize();
    ASSERT_NE(std::begin(tokens), std::end(tokens));
    ASSERT_EQ(cat::token_type::minus, std::begin(tokens)->type());
}

TEST(lexer, operator_asterisk) {
    cat::lexer lexer{"*"};
    auto const tokens = lexer.tokenize();
    ASSERT_NE(std::begin(tokens), std::end(tokens));
    ASSERT_EQ(cat::token_type::asterisk, std::begin(tokens)->type());
}

TEST(lexer, operator_slash) {
    cat::lexer lexer{"/"};
    auto const tokens = lexer.tokenize();
    ASSERT_NE(std::begin(tokens), std::end(tokens));
    ASSERT_EQ(cat::token_type::slash, std::begin(tokens)->type());
}

TEST(lexer, operator_equals) {
    cat::lexer lexer{"="};
    auto const tokens = lexer.tokenize();
    ASSERT_NE(std::begin(tokens), std::end(tokens));
    ASSERT_EQ(cat::token_type::equals, std::begin(tokens)->type());
}

TEST(lexer, identifier) {
    constexpr std::size_t token_size = 2;
    cat::lexer lexer{"config dec"};
    auto const tokens = lexer.tokenize();
    ASSERT_EQ(token_size, tokens.size());
    ASSERT_EQ(cat::token_type::identifier, tokens[0].type());
    ASSERT_EQ(cat::token_type::identifier, tokens[1].type());
}

auto main(int argc, char const* argv[]) -> int {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}
