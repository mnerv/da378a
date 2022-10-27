/**
 * @file   lexer.hpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Lexer/Tokenizer for C@ language.
 * @date   2022-09-25
 *
 * @copyright Copyright (c) 2022
 */
#ifndef CATC_LEXER_HPP
#define CATC_LEXER_HPP
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

#include "token.hpp"

namespace cat {
/**
 * Lexer or Tokenizer, here we use the two naming interchangeable. The purpose
 * of this is to generate tokenize for the parser to create an
 * AST(Abstract Syntax Tree).
 */
class lexer {
  public:
    lexer(std::string const& source, std::string const& filename = "");
    ~lexer();

    auto tokenize() -> std::vector<token>;

  private:
    auto consume() -> void;
    auto consume_space() -> void;
    auto peek_consume() -> char;
    auto peek() const -> char;

    auto next_token() -> std::optional<token>;

    // Whitespace character - Wikipedia
    // https://en.wikipedia.org/wiki/Whitespace_character
  private:
    auto has_next()   const -> bool;
    auto is_tab()     const -> bool;
    auto is_space()   const -> bool;
    auto is_newline() const -> bool;
    auto is_carriage_return() const -> bool;
    auto is_whitespace()      const -> bool;
    auto is_quote() const -> bool;
    auto is_digit() const -> bool;
    auto is_operator() const -> bool;

  private:
    std::string m_source;
    std::string m_filename;
    std::size_t m_cursor;
    std::size_t m_line;
    std::size_t m_column;
};
}

#endif  // CATC_LEXER_HPP
