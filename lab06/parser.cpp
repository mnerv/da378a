/**
 * @file   parser.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Parser C@ language.
 * @date   2022-09-27
 *
 * @copyright Copyright (c) 2022
 */
#include "parser.hpp"
#include <iostream>

// Grammars
// E: Rule (Expression)
// T: Non-Terminal Symbols "Grammar Symbols" (Term)
// F: (Factor)
// +-*/()=: Terminal Symbols

// E -> T + E | T - E | T
// T -> F * T | F / T | F
// F -> ID | INT | (E) | -F

// ID  -> ^[a-zA-Z][a-zA-Z0-9]+$
// INT -> ^[-+]?[0-9]+$

namespace cat {

parser::parser(std::vector<token> const& tokens) : m_cursor(0), m_tokens(tokens), m_nodes({}) {}
parser::~parser() = default;

auto parser::parse() -> node_ref_t {
    return nullptr;
}
auto parser::nodes() const -> std::vector<node_ref_t> const& { return m_nodes; }
auto parser::next_token() -> void { ++m_cursor; }
auto parser::peek() const -> token const& { return m_tokens[m_cursor]; }

}

