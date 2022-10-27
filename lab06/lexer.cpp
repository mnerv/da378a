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

lexer::lexer(std::string const& source, std::string const& filename)
    : m_source(source), m_filename(filename), m_cursor(0), m_line(1) {
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
auto lexer::consume_whitespace() -> void { while (is_whitespace() && has_next()) consume(); }
auto lexer::peek_consume() -> char { return m_source[m_cursor++]; }
auto lexer::peek() const -> char { return m_source[m_cursor]; }

auto lexer::next_token() -> std::optional<token> {
    if (!has_next()) return {};
    consume_whitespace();
    if (!has_next()) return {};
    std::string res{};  // Eaten results
    // TODO: Add a way to see where a token is located in the source file.

    // String literal
    if (is_quote()) {
        consume();
        while (!is_quote()) {
            if (is_newline()) return token(res, token_type::invalid, m_filename, m_line++);
            res += peek_consume();
        }
        consume();
        return token(res, token_type::string_literal, m_filename, m_line);
    }

    // Numeric literal
    if (is_digit()) {
        while (is_digit()) res += peek_consume();
        return token(res, token_type::numeric_literal, m_filename, m_line);
    }

    // Operator
    if (is_operator()) {
        res += peek_consume();
        auto const& valid = token::str_token(res);
        return token(res, valid.has_value() ? valid.value() : token_type::invalid, m_filename, m_line);
    }

    // FIXME: Handle if the line ending is different somehow, LF, CRLF. It might not be a problem.
    if (is_newline() || is_carriage_return()) {
        res = peek_consume();
        return token(res, token_type::newline, "", m_line++);
    }

    return {};
}

auto lexer::has_next()   const -> bool { return m_cursor < m_source.size(); }
auto lexer::is_tab()     const -> bool { return peek() == '\t'; }
auto lexer::is_space()   const -> bool { return peek() == ' ';  }
auto lexer::is_newline() const -> bool { return peek() == '\n'; }
auto lexer::is_carriage_return() const -> bool { return peek() == '\r'; }
auto lexer::is_whitespace() const -> bool {
    return is_space() || is_tab() || is_newline() || is_carriage_return();
}
auto lexer::is_quote() const -> bool {
    return peek() == '\"';
}
auto lexer::is_digit() const -> bool {
    return std::isdigit(peek());
}
auto lexer::is_operator() const -> bool {
    return token::is_operator(std::string{peek()});
}
}
