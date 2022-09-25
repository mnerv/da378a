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
auto token_type_str(token_type const& type) -> std::string {
    switch (type) {
#define ENUMERATOR_CATLANG_TOKEN(_type, category) case token_type::_type: return #_type;
        ENUMERATOR_CATLANG_TOKENS
#undef  ENUMERATOR_CATLANG_TOKEN
        default: break;
    }
    return "invalid";
}

auto token_category_str(token_category const& type) -> std::string {
    switch (type) {
        case token_category::number:      return "number";
        case token_category::keyword:     return "keyword";
        case token_category::operator_:   return "operator";
        case token_category::punctuation: return "punctuation";
        case token_category::invalid:
        case token_category::_count:      return "invalid";
    }
}

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
