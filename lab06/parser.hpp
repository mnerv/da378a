/**
 * @file   parser.hpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Parser C@ language.
 * @date   2022-09-27
 *
 * @copyright Copyright (c) 2022
 */
#ifndef CATC_PARSER_HPP
#define CATC_PARSER_HPP

#include <vector>
#include <memory>
#include <optional>

#include "token.hpp"
#include "ast.hpp"

namespace cat {
/**
 * C@ language parser.
 *
 * @code
 * Grammar rules
// S     -> ID [ ID | E ]+
// S     -> ID = [ E | ID ]
// E     -> T [ + | - T ]+
// T     -> F [ * | / T ]+
// F     -> ID | INT | (E) | -F
// ID    -> ^[a-zA-Z][a-zA-Z0-9]*$
// INT   -> ^[-+]?[0-9]+$
 * @endcode
 */
class parser {
  public:
    parser(std::vector<token> const& tokens);
    ~parser();

    auto parse() -> void;
    auto program() const -> std::vector<node_ref_t> const&;

  private:
    auto parse_statement() -> node_ref_t;

    auto parse_call_expression() -> node_ref_t;
    auto parse_assignment_statement() -> node_ref_t;

    auto parse_expression() -> node_ref_t;
    auto parse_term_expression() -> node_ref_t;
    auto parse_factor_expression() -> node_ref_t;
    auto parse_args() -> std::vector<node_ref_t>;

  private:
    auto consume() -> void;
    auto peek() const -> std::optional<token>;
    auto peek_next(std::size_t const& i = 1) const -> std::optional<token>;
    auto has_next() const -> bool;

  private:
    std::size_t             m_cursor;
    std::vector<token>      m_tokens;
    std::vector<node_ref_t> m_nodes;
};

}

#endif  // CATC_PARSER_HPP
