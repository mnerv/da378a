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
// S: Statement
// E: Rule (Expression)
// T: Non-Terminal Symbols "Grammar Symbols" (Term)
// F: (Factor)
// +-*/()=: Terminal Symbols

// Grammar rules
//
// S     -> ID [ ID | E ]+
// S     -> ID "=" [ E | ID ]
// E     -> T [ + | - T ]+
// T     -> F * T | F / T | F
// F     -> ID | INT | FLOAT | (E) | -F
// ID    -> ^[a-zA-Z][a-zA-Z0-9]+$
// INT   -> ^[-+]?[0-9]+$
// FLOAT -> ^[-+]?[0-9]+.(?:[0-9]+f?)?$

// parse_e
// parse_t
// parse_f
// parse_id
// parse_int

// Grammar rules (verbose)
//
// function_statement   -> id [ id | math_expression ]+
// assignment_statement -> id "=" math_expression
// math_expression      -> product_expression [ "+" product_expression | "-" product_expression ]+
// product_expression   -> primary_expression [ "*" primary_expression | "/" primary_expression ]+
// primary_expression   ->  id | int | float | "(" math_expressin ")" | "-" primary_expression
// int                  -> ^[-+]?[0-9]+$
// id                   -> ^[a-zA-Z][a-zA-Z0-9]+$
// float                -> ^[-+]?[0-9]+.(?:[0-9]+f?)?$

namespace cat {

parser::parser(std::vector<token> const& tokens) : m_cursor(0), m_tokens(tokens), m_nodes({}) {}
parser::~parser() = default;

auto parser::parse() -> void {
    node_ref_t current_node{nullptr};
    do {
        current_node = parse_statement();
        if (current_node != nullptr) m_nodes.push_back(current_node);
    } while (current_node != nullptr);
}
auto parser::program() const -> std::vector<node_ref_t> const& { return m_nodes; }

auto parser::parse_statement() -> node_ref_t {
    return parse_math_expression();
}

auto parser::parse_math_expression() -> node_ref_t {
    auto left = parse_product_expression();
    auto tk   = peek();
    while (true) {
        if (!tk.has_value()) return left;
        next_token();
        auto right = parse_product_expression();
        left  = make_binary_expression_node(tk.value(), left, right);
        tk    = peek();
    }
}
auto parser::parse_product_expression() -> node_ref_t {
    auto left = parse_primary_expression();
    if (left == nullptr) return nullptr;
    auto tk = peek();
    while (tk.has_value()) {
        if (tk->type() != token_type::asterisk && tk->type() != token_type::slash) break;
        next_token();
        auto right = parse_product_expression();
        left  = make_binary_expression_node(tk.value(), left, right);
        tk    = peek();
    }
    return left;
}
auto parser::parse_primary_expression() -> node_ref_t {
    auto tk = peek();
    if (!tk.has_value()) return nullptr;
    next_token();
    switch (tk.value().type()) {
        case token_type::identifier:
            return make_identifier_node(*tk);
        case token_type::numeric_literal:
            return make_numeric_literal_node(*tk);
        case token_type::paren_open: {
            auto a = parse_math_expression();
            if (a == nullptr) return nullptr;
            tk = peek();
            if (tk.has_value() && tk->type() == token_type::paren_close) {
                next_token();
                return a;
            } else {
                return nullptr;
            }
        }
        default:
            return nullptr;
    }
}
auto parser::parse_args() -> std::vector<node_ref_t> {
    std::vector<node_ref_t> args{};
    while (peek().has_value() && peek().value().type() != token_type::newline)
        args.push_back(parse_statement());
    return args;
}

auto parser::next_token() -> void { ++m_cursor; }
auto parser::peek() const -> std::optional<token> {
    if (!has_next()) return {};
    return m_tokens[m_cursor];
}
auto parser::peek_ahead(std::size_t const& i) const -> std::optional<token> {
    if (m_cursor + i >= m_tokens.size()) return {};
    return m_tokens[m_cursor + i];
}
auto parser::peek_consume() -> std::optional<token> {
    if (!has_next()) return {};
    return m_tokens[m_cursor++];
}
auto parser::has_next() const -> bool { return m_cursor < m_tokens.size(); }

}

