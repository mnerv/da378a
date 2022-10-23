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
// S     -> ID = [ E | ID ]
// E     -> T [ + | - T ]+
// T     -> F [ * | / T ]+
// F     -> ID | INT | FLOAT | (E) | -F
// ID    -> ^[a-zA-z][a-zA-z0-9]*$
// INT   -> ^[-+]?[0-9]+$
// FLOAT -> ^[-+]?[0-9]+.[0-9]*f?$

// Grammar rules (verbose line for line)
//
// function_statement   -> id [ id | math_expression ]+
// assignment_statement -> id "=" math_expression
// math_expression      -> product_expression [ "+" product_expression | "-" product_expression ]+
// product_expression   -> primary_expression [ "*" primary_expression | "/" primary_expression ]+
// primary_expression   ->  id | int | float | "(" math_expressin ")" | "-" primary_expression
// int                  -> ^[-+]?[0-9]+$
// id                   -> ^[a-zA-z][a-zA-z0-9]*$
// float                -> ^[-+]?[0-9]+.[0-9]*f?$

namespace cat {

parser::parser(std::vector<token> const& tokens) : m_cursor(0), m_tokens(tokens), m_nodes({}) {}
parser::~parser() = default;

auto parser::parse() -> void {
    node_ref_t current_node{nullptr};
    std::size_t null_count = 0;
    static constexpr std::size_t max_null_count = 256;
    do {
        current_node = parse_statement();
        if (current_node != nullptr) m_nodes.push_back(current_node);
        if (current_node == nullptr) ++null_count;
        else null_count = 0;
    } while (has_next() && null_count < max_null_count);

    // TODO: Handle error properly
    if (null_count == max_null_count) std::cerr << "TOO MANY nullptr!\n";
}
auto parser::program() const -> std::vector<node_ref_t> const& { return m_nodes; }

auto parser::parse_statement() -> node_ref_t {
    auto tk = peek();
    if (!tk.has_value()) return nullptr;
    if (tk->type() == token_type::newline) {
        consume();
        return nullptr;  // Handle error
    }

    switch (tk->type()) {
        case token_type::identifier: {
            auto next = peek_next();
            if (!next.has_value() ||
                (next.has_value() &&
                    (
                        next->category() == token_category::number     ||
                        next->category() == token_category::identifier ||
                        next->type()     == token_type::paren_open
                    )
                )
               ) {
                return parse_call_expression();
            } else if (next.has_value() && next->type() == token_type::equals) {
                return parse_assignment_statement();
            } else {
                return parse_expression();
            }
        }
        case token_type::numeric_literal:
        case token_type::paren_open:
            return parse_expression();
        default:
            return nullptr;
    }
}

auto parser::parse_call_expression() -> node_ref_t {
    auto token_callee = *peek();
    auto callee = make_ref<identifier_node>(token_callee);
    consume();
    auto args = parse_args();
    return make_ref<call_expression_node>(callee, args);
}
auto parser::parse_assignment_statement() -> node_ref_t {
    auto tk_id = peek();
    consume();
    auto equal = peek();
    consume();

    auto id   = make_ref<identifier_node>(*tk_id);
    auto init = parse_statement();
    return make_ref<assignment_expression_node>(*equal, id, init);
}

auto parser::parse_expression() -> node_ref_t {
    auto left = parse_term_expression();
    auto tk   = peek();
    while (tk.has_value()) {
        if (tk->category() != token_category::operator_) break;
        consume();
        auto right = parse_term_expression();
        left  = make_ref<binary_expression_node>(*tk, left, right);
        tk    = peek();
    }
    return left;
}
auto parser::parse_term_expression() -> node_ref_t {
    auto left = parse_factor_expression();
    if (left == nullptr) return nullptr;
    auto tk = peek();
    while (tk.has_value()) {
        if (tk->type() != token_type::asterisk && tk->type() != token_type::slash) break;
        consume();
        auto right = parse_term_expression();
        left  = make_ref<binary_expression_node>(*tk, left, right);
        tk    = peek();
    }
    return left;
}
auto parser::parse_factor_expression() -> node_ref_t {
    auto tk = peek();
    if (!tk.has_value()) return nullptr;
    consume();
    switch (tk->type()) {
        case token_type::identifier:
            return make_ref<identifier_node>(*tk);
        case token_type::numeric_literal:
            return make_ref<numeric_literal_node>(*tk);
        case token_type::paren_open: {
            auto a = parse_expression();
            if (a == nullptr) return nullptr;
            tk = peek();
            if (tk.has_value() && tk->type() == token_type::paren_close) {
                consume();
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
    auto tk = peek();
    while (tk.has_value()) {
        if (tk->type() == token_type::newline) {
            consume();
            break;
        }
        auto next = peek_next();

        if (next.has_value()) {
            args.push_back(parse_expression());
        } else {
            consume();
            args.push_back(make_ref<identifier_node>(*tk));
        }

        tk = peek();
    }
    return args;
}

auto parser::consume() -> void { ++m_cursor; }
auto parser::peek() const -> std::optional<token> {
    if (!has_next()) return {};
    return m_tokens[m_cursor];
}
auto parser::peek_next(std::size_t const& i) const -> std::optional<token> {
    if (m_cursor + i >= m_tokens.size()) return {};
    return m_tokens[m_cursor + i];
}
auto parser::has_next() const -> bool { return m_cursor < m_tokens.size(); }

}

