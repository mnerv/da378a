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
auto lexer::consume_space() -> void { while (is_space() && has_next()) consume(); }
auto lexer::peek_consume() -> char { return m_source[m_cursor++]; }
auto lexer::peek() const -> char { return m_source[m_cursor]; }

auto lexer::next_token() -> std::optional<token> {
    if (!has_next()) return {};
    consume_space();
    if (!has_next()) return {};
    std::string res{};  // Eaten results
    // TODO: Add a way to see where a token is located in the source file.

    //// Literal string
    //auto is_literal_string = [this] { return peek() == '`'; };
    //if (is_literal_string()) {
    //    consume();
    //    while (!is_literal_string() && has_next()) res += peek_consume();
    //    if (is_literal_string()) {
    //        consume();
    //        return token(token_type::string_literal, res, m_filename, m_line);
    //    } else {
    //        return token(token_type::invalid, res, m_filename, m_line);
    //    }
    //}

    // String literal
    if (is_quote()) {
        consume();
        while (!is_quote() && has_next()) {
            if (is_newline()) return token(token_type::invalid, res, m_filename, m_line);
            res += peek_consume();
        }
        if (is_quote()) {
            consume();
            return token(token_type::string_literal, res, m_filename, m_line);
        } else {
            return token(token_type::invalid, res, m_filename, m_line);
        }
    }

    // Numeric literal
    if (is_digit()) {
        while (is_digit()) res += peek_consume();
        return token(token_type::numeric_literal, res, m_filename, m_line);
    }

    // TODO: Handle ++, -- operator

    // Operator
    if (is_operator()) {
        res += peek_consume();
        return token(*token::str_token(res), res, m_filename, m_line);
    }

    if (peek() == '(') {
        res += peek_consume();
        return token(token_type::paren_open, res, m_filename, m_line);
    }

    if (peek() == ')') {
        res += peek_consume();
        return token(token_type::paren_close, res, m_filename, m_line);
    }

    // Identifier
    if (token::is_identifier({peek()})) {
        auto is_valid_identifier_char = [this] {
            auto const& c = peek();
            return (c >= '0' && c <= '9') ||
                   (c >= 'A' && c <= 'Z') ||
                   (c >= 'a' && c <= 'z') ||
                   (c == '_');
        };
        while (is_valid_identifier_char()) res += peek_consume();
        auto const& type = token::is_identifier(res) ? token_type::identifier : token_type::invalid;
        return token(type, res, m_filename, m_line);
    }

    // FIXME: Handle if the line ending is different somehow, LF, CRLF. It might not be a problem.
    if (is_newline() || is_carriage_return()) {
        res = peek_consume();
        return token(token_type::newline, res, m_filename, m_line++);
    }

    while (has_next()) res += peek_consume();
    return token(token_type::invalid, res, m_filename, m_line);
}

auto lexer::has_next()   const -> bool { return m_cursor < m_source.size(); }
auto lexer::is_tab()     const -> bool { return peek() == '\t'; }
auto lexer::is_space()   const -> bool { return peek() == ' ';  }
auto lexer::is_newline() const -> bool { return peek() == '\n'; }
auto lexer::is_carriage_return() const -> bool { return peek() == '\r'; }
auto lexer::is_whitespace() const -> bool {
    return is_space() || is_tab() || is_newline() || is_carriage_return();
}
auto lexer::is_quote() const -> bool { return peek() == '\"'; }
auto lexer::is_digit() const -> bool { return std::isdigit(peek()); }
auto lexer::is_operator() const -> bool { return token::is_operator({peek()}); }
}
