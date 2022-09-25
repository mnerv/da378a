/**
 * @file   token.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Token C@ language.
 * @date   2022-09-25
 *
 * @copyright Copyright (c) 2022
 */
#include "token.hpp"

namespace cat {
/**
 * Token container, describe what type of token it is and what value it has.
 */
token::token(std::string const& value, token_type const& type) : m_value(value), m_type(type) {}

auto token::str() const -> std::string {
    using namespace std::string_literals;
    std::string str{"token { "};
    str += "value: " + m_value + ", ";
    str += "type: "  + token_type_str(m_type);
    str += " }";
    return str;
}
}
