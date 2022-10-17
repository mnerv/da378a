/**
 * @file   token.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Token C@ language.
 * @date   2022-09-25
 *
 * @copyright Copyright (c) 2022
 */
#include "token.hpp"
#include <numeric>
#include <algorithm>
#include <cctype>
#include <utility>

namespace cat {
std::unordered_map<std::string, token_type> token::s_token_strs{
    // Keywords

    // Punctuations
    {"\n",     token_type::newline},
    {"(",      token_type::paren_open},
    {")",      token_type::paren_close},

    // Operators
    {"=",      token_type::equals},
    {"+",      token_type::plus},
    {"-",      token_type::minus},
    {"*",      token_type::asterisk},
    {"/",      token_type::slash},
};

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
        case token_category::identifier:  return "identifier";
        case token_category::invalid:
        case token_category::_count:      return "invalid";
    }
    return "invalid";
}

auto token_type_category(token_type const& type) -> token_category {
    switch (type) {
#define ENUMERATOR_CATLANG_TOKEN(_type, category) case token_type::_type: return token_category::category;
        ENUMERATOR_CATLANG_TOKENS
#undef  ENUMERATOR_CATLANG_TOKEN
        default: break;
    }
    return token_category::invalid;
}

token::token(std::string value, token_type const& type, std::size_t const& line) : m_value(std::move(value)), m_type(type), m_line(line) {}

auto token::type() const -> token_type { return m_type; }
auto token::value() const -> std::string { return m_value; }

auto token::str() const -> std::string {
    using namespace std::string_literals;
    auto sanitize_str = [](std::string const& str) -> std::string {
        return std::reduce(std::begin(str), std::end(str), std::string{}, [](auto a, auto b) {
            std::string raw{};
            if (b == '\n')     raw = "\\n";
            else if(b == '\r') raw = "\\r";
            else if(b == '\t') raw = "\\t";
            else raw = b;
            return a + raw;
        });
    };
    std::string str{"cat::token{ "};
    str += "value: \"" + sanitize_str(m_value)  + "\", ";
    str += "type: "    + token_type_str(m_type) + ", ";
    str += "line: "    + std::to_string(m_line);
    str += " }";
    return str;
}

auto token::str_token(std::string const& str) -> std::optional<token_type> {
    auto it = s_token_strs.find(str);
    if (it != std::end(s_token_strs)) return it->second;
    else return {};
}

auto token::is_numeric(std::string const& str) -> bool {
    return std::all_of(std::begin(str), std::end(str),
            [](auto const& c) { return std::isdigit(c); });
}
}
