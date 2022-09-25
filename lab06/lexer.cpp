/**
 * @file   lexer.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Lexer/Tokenizer for C@ language.
 * @date   2022-09-25
 *
 * @copyright Copyright (c) 2022
 */
#include "lexer.hpp"

namespace cat {

std::unordered_map<std::string, token_type> lexer::s_keywords{
    {"config", token_type::config},
    {"print",  token_type::print}
};

lexer::lexer(std::string const& source) : m_source(source), m_cursor(0), m_line(1) {}
lexer::~lexer() = default;

auto lexer::tokenize() -> std::vector<token> {
    std::vector<token> tokens{};
    auto tkn = next_token();
    while (tkn.has_value()) {
        tokens.push_back(tkn.value());
        tkn = next_token();
    }
    return tokens;
}

auto lexer::consume() -> void { ++m_cursor; }
auto lexer::consume_next() -> char { return m_source[m_cursor++]; }
auto lexer::peek() const -> char { return m_source[m_cursor]; }

auto lexer::next_token() -> std::optional<token> {
    if (!has_next()) return {};
    if (is_space()) consume();
    if (!has_next()) return {};
    std::string res{};  // Eaten results

    // TODO: Handle strings source code

    do {
        if (is_newline()) ++m_line;
        res += consume_next();
    } while (has_next() && !is_whitespace());
    if (has_next()) consume();

    auto const token_keyword = s_keywords.find(res);
    if (token_keyword != std::end(s_keywords))
        return token(res, token_keyword->second);

    return token(res, token_type::invalid);
}

auto lexer::is_tab()     const -> bool { return peek() == '\t'; }
auto lexer::is_space()   const -> bool { return peek() == ' ';  }
auto lexer::is_newline() const -> bool { return peek() == '\n'; }
auto lexer::has_next()   const -> bool { return m_cursor < m_source.size(); }
auto lexer::is_carriage_return() const -> bool { return peek() == '\r'; }
auto lexer::is_whitespace() const -> bool {
    return is_space() || is_tab() || is_newline() || is_carriage_return();
}

}
