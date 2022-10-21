/**
 * @file   hello.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Google Test suites for cat language library.
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

TEST(token, identifier_valid) {
    ASSERT_TRUE(cat::token::is_identifier("hello"));
}

TEST(token, identifier_invalid) {
    ASSERT_FALSE(cat::token::is_identifier("0hello"));
}

TEST(lexer, consume_spaces) {
    constexpr std::size_t token_size = 3;
    cat::lexer lexer{"1 +   1"};
    auto const tokens = lexer.tokenize();
    ASSERT_EQ(token_size, tokens.size());
}

TEST(lexer, identifier) {
    cat::lexer lexer{"config dec"};
    auto const tokens = lexer.tokenize();
    for (auto const& token : tokens)
        ASSERT_EQ(cat::token_category::identifier, cat::token_type_category(token.type()));
}

TEST(lexer, numeric_literals) {
    for (std::size_t i = 0; i < 10; ++i) {
        auto const source = std::to_string(i);
        cat::lexer lexer{source};
        auto const tokens = lexer.tokenize();
        ASSERT_NE(std::begin(tokens), std::end(tokens));
        EXPECT_EQ(source, tokens[0].value());
    }
}

TEST(lexer, numeric_unary_negative) {
    constexpr auto numeric_literal = "-2";
    cat::lexer lexer{numeric_literal};
    auto const tokens = lexer.tokenize();
    ASSERT_NE(std::begin(tokens), std::end(tokens));
    ASSERT_EQ(std::string(numeric_literal), std::begin(tokens)->value());
}

TEST(lexer, numeric_unary_positive) {
    constexpr auto numeric_literal = "+2";
    cat::lexer lexer{numeric_literal};
    auto const tokens = lexer.tokenize();
    ASSERT_EQ(std::string(numeric_literal), tokens.begin()->value());
}

TEST(lexer, numeric_binary_operation_plus) {
    using namespace std::string_literals;
    constexpr std::size_t token_size = 3;
    constexpr auto numeric_literal = "1 + 1";
    cat::lexer lexer{numeric_literal};
    auto const tokens = lexer.tokenize();
    ASSERT_NE(std::begin(tokens), std::end(tokens));
    ASSERT_EQ(token_size, tokens.size());
    ASSERT_EQ("1"s, tokens[0].value());
    ASSERT_EQ("+"s, tokens[1].value());
    ASSERT_EQ("1"s, tokens[2].value());
}

TEST(lexer, numeric_binary_operation_minus) {
    using namespace std::string_literals;
    constexpr std::size_t token_size = 3;
    constexpr auto numeric_literal = "1 - 1";
    cat::lexer lexer{numeric_literal};
    auto const tokens = lexer.tokenize();
    ASSERT_NE(std::begin(tokens), std::end(tokens));
    ASSERT_EQ(token_size, tokens.size());
    ASSERT_EQ("1"s, tokens[0].value());
    ASSERT_EQ("-"s, tokens[1].value());
    ASSERT_EQ("1"s, tokens[2].value());
}

TEST(lexer, numeric_binary_operation_product) {
    using namespace std::string_literals;
    constexpr std::size_t token_size = 3;
    constexpr auto numeric_literal = "1 * 1";
    cat::lexer lexer{numeric_literal};
    auto const tokens = lexer.tokenize();
    ASSERT_NE(std::begin(tokens), std::end(tokens));
    ASSERT_EQ(token_size, tokens.size());
    ASSERT_EQ("1"s, tokens[0].value());
    ASSERT_EQ("*"s, tokens[1].value());
    ASSERT_EQ("1"s, tokens[2].value());
}

TEST(lexer, numeric_binary_operation_fraction) {
    using namespace std::string_literals;
    constexpr std::size_t token_size = 3;
    constexpr auto numeric_literal = "1 / 1";
    cat::lexer lexer{numeric_literal};
    auto const tokens = lexer.tokenize();
    ASSERT_NE(std::begin(tokens), std::end(tokens));
    ASSERT_EQ(token_size, tokens.size());
    ASSERT_EQ("1"s, tokens[0].value());
    ASSERT_EQ("/"s, tokens[1].value());
    ASSERT_EQ("1"s, tokens[2].value());
}

auto main(int argc, char const* argv[]) -> int {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}
