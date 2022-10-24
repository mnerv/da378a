/**
 * @file   parsertest.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Parser test suites for cat language library.
 * @date   2022-10-17
 *
 * @copyright Copyright (c) 2022
 */
#include <string>

#include "gtest/gtest.h"

#include "parser.hpp"

TEST(parser, numeric_literal) {
    cat::token one_token{"1", cat::token_type::numeric_literal};
    std::vector<cat::token> tokens{one_token};
    cat::parser parser{tokens};
    parser.parse();
    auto one_node = cat::make_ref<cat::numeric_literal_node>(one_token);

    auto program = parser.program();
    ASSERT_EQ(one_node->str(), program.front()->str());
}

TEST(parser, binary_operation_plus_numeric_literals) {
    cat::token a_token{"1", cat::token_type::numeric_literal};
    cat::token op_token{"+", cat::token_type::plus};
    cat::token b_token{"2", cat::token_type::numeric_literal};
    std::vector<cat::token> tokens{a_token, op_token, b_token};
    cat::parser parser{tokens};
    parser.parse();
    auto a  = cat::make_ref<cat::numeric_literal_node>(a_token);
    auto b  = cat::make_ref<cat::numeric_literal_node>(b_token);
    auto op = cat::make_ref<cat::binary_expression_node>(op_token, a, b);
    auto program = parser.program();

    ASSERT_EQ(op->str(), program.front()->str());
}

TEST(parser, binary_operation_minus_numeric_literals) {
    cat::token a_token{"1", cat::token_type::numeric_literal};
    cat::token op_token{"-", cat::token_type::minus};
    cat::token b_token{"2", cat::token_type::numeric_literal};
    std::vector<cat::token> tokens{a_token, op_token, b_token};
    cat::parser parser{tokens};
    parser.parse();
    auto a  = cat::make_ref<cat::numeric_literal_node>(a_token);
    auto b  = cat::make_ref<cat::numeric_literal_node>(b_token);
    auto op = cat::make_ref<cat::binary_expression_node>(op_token, a, b);
    auto program = parser.program();

    ASSERT_EQ(op->str(), program.front()->str());
}

auto main(int argc, char const* argv[]) -> int {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}
