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

lexer::lexer(std::string const& source) : m_source(source), m_cursor(0), m_line(1) {
    (void)m_column;
}
lexer::~lexer() = default;

auto lexer::tokenize() -> std::vector<token> {
    std::vector<token> tokens{};
    auto tkn = next_token();
    while (tkn.has_value()) {
        tokens.push_back(tkn.value());
        tkn = next_token();
    }
    m_line = 0;
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
    // TODO: Add a way to see where a token is located in the source file.
    // TODO: String token support
    // TODO: Unary operator +T, -T, ++T, T++, --T, T--

    // FIXME: Handle if the line ending is different somehow, LF, CRLF. It might not be a problem.
    if (is_newline() || is_carriage_return()) {
        res = consume_next();
        return token(res, token_type::newline, "", m_line++);
    }

    // FIXME: Find a better way? It's kind of ugly
    if (res.empty()) {
        do {
            res += consume_next();
            if (res.front() == '(') break;
            if (peek() == ')') break;
        } while (has_next() && !is_whitespace());
        if (has_next() && !is_newline() && is_space()) consume();
    }

    if (token::is_numeric(res))
        return token(res, token_type::numeric_literal, "", m_line);

    auto const token_valid = token::str_token(res);
    if (token_valid.has_value())
        return token(res, token_valid.value(), "", m_line);

    auto const type_of_token = token::is_identifier(res) ? token_type::identifier : token_type::invalid;
    return token(res, type_of_token, "", m_line);
}

auto lexer::has_next()   const -> bool { return m_cursor < m_source.size(); }
auto lexer::is_tab()     const -> bool { return peek() == '\t'; }
auto lexer::is_space()   const -> bool { return peek() == ' ';  }
auto lexer::is_newline() const -> bool { return peek() == '\n'; }
auto lexer::is_carriage_return() const -> bool { return peek() == '\r'; }
auto lexer::is_whitespace() const -> bool {
    return is_space() || is_tab() || is_newline() || is_carriage_return();
}

}
