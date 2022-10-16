/**
 * @file   parser.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Parser C@ language.
 * @date   2022-09-27
 *
 * @copyright Copyright (c) 2022
 */
#include "parser.hpp"

namespace cat {

parser::parser(std::vector<token> const& tokens) : m_tokens(tokens) {
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        auto const& token   = tokens[i];
        auto const type     = token.type();
        [[maybe_unused]]auto const category = token_type_category(type);
    }
}

parser::~parser() = default;

}

