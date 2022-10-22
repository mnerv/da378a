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
// S     -> ID [ID | E]+
// S     -> ID "=" [ E | ID ]
// E     -> T + E | T - E | T
// T     -> F * T | F / T | F
// F     -> ID | INT | FLOAT | (E) | -F
// ID    -> ^[a-zA-Z][a-zA-Z0-9]+$
// INT   -> ^[-+]?[0-9]+$
// FLOAT -> ^[-+]?[0-9]+.(?:[0-9]+f?)?$

// Grammar rules (verbose)
//
// function_statement   -> id [ id | math_expression ]+
// assignment_statement -> id "=" math_expression
// math_expression      -> sum_expression
// sum_expression       -> product_expression [ "+" product_expression | "-" product_expression ]+
// product_expression   -> primary_expression [ "*" primary_expression | "/" primary_expression ]+
// primary_expression   ->  id | int | float | "(" math_expressin ")" | "-" primary_expression
// args                 -> [ int | id ]+
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

auto parser::parse_expression() -> node_ref_t {
    return nullptr;
}

auto parser::parse_math_expression() -> node_ref_t {
    return parse_sum_expression();
}
auto parser::parse_sum_expression() -> node_ref_t {
    auto left = parse_product_expression();
    auto tk   = peek_consume();
    if (!tk.has_value()) return left;

    if (tk.value().type() == token_type::plus || tk.value().type() == token_type::minus) {
        auto op = peek_ahead();
        node_ref_t right{nullptr};
        if (op.has_value() && token_type_category(op.value().type()) == token_category::operator_)
            right = parse_sum_expression();
        else
            right = parse_product_expression();
        if (right != nullptr) return make_binary_expression_node(tk.value(), left, right);
    }

    return nullptr;  // TODO: Show error
}
auto parser::parse_product_expression() -> node_ref_t {
    auto left = parse_primary_expression();
    if (left == nullptr) return nullptr;

    auto tk_op = peek();
    if (!tk_op.has_value()) return left;
    auto const& tk = tk_op.value();
    if (tk.type() == token_type::asterisk || tk.type() == token_type::slash) {
        next_token();
        auto op = peek_ahead();
        node_ref_t right{nullptr};
        if (op.has_value() && token_type_category(op.value().type()) == token_category::operator_)
            right = parse_sum_expression();
        else
            right = parse_primary_expression();
        if (right != nullptr) return make_binary_expression_node(tk, left, right);
    }
    return left;
}
auto parser::parse_primary_expression() -> node_ref_t {
    auto tk = peek_consume();
    if (!tk.has_value()) return nullptr;
    switch (tk.value().type()) {
        case token_type::identifier:
            return make_identifier_node(tk.value());
        case token_type::numeric_literal:
            return make_numeric_literal_node(tk.value());
        case token_type::paren_open:
            return parse_math_expression();
        case token_type::paren_close:
        default:
            break;
    }
    return nullptr;
}
auto parser::parse_args() -> std::vector<node_ref_t> {
    std::vector<node_ref_t> args{};
    while (peek().has_value() && peek().value().type() != token_type::newline)
        args.push_back(parse_statement());
    return args;
}
auto parser::parse_int() -> node_ref_t {
    if (!peek().has_value()) return nullptr;
    return make_numeric_literal_node(peek().value());
}
auto parser::parse_id() -> node_ref_t {
    if (!peek().has_value()) return nullptr;
    return make_identifier_node(peek().value());
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

