/**
 * @file   ast.hpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  AST C@ language.
 * @date   2022-10-01
 *
 * @copyright Copyright (c) 2022
 */

#include "ast.hpp"

namespace cat {
numeric_literal_node::numeric_literal_node(token tk) : ast_node(std::move(tk), node_type::numeric_literal) {
    m_value = std::stoi(m_token.value());
}

auto numeric_literal_node::str() const -> std::string {
    using namespace std::string_literals;
    std::string fmt{name()};
    fmt += "{";
    fmt += " value: "s + std::to_string(m_value) + ",";
    fmt += " raw: \""s + m_token.value()         + "\" ";
    fmt += "}";
    return fmt;
}

binary_expression_node::binary_expression_node(token tk, node_ref_t left, node_ref_t right) : ast_node(std::move(tk), node_type::binary_expression) {
    m_left  = std::move(left);
    m_right = std::move(right);
    m_operator = m_token.type();
}
auto binary_expression_node::str() const -> std::string {
    std::string fmt{name()};
    fmt += "{";
    fmt += " operator: \"" + m_token.value() + "\",";
    fmt += " left: "       + m_left->str()   + ",";
    fmt += " right: "      + m_right->str()  + " ";
    fmt += "}";
    return fmt;
}

variable_declaration_node::variable_declaration_node(token tk, node_ref_t init)
    : ast_node(std::move(tk), node_type::variable_declaration),
      m_identifier(m_token.value()), m_init(std::move(init)) {
}

auto variable_declaration_node::str() const -> std::string {
    std::string fmt{name()};
    fmt += "{";
    fmt += " identifier: \"" + m_identifier  + "\",";
    fmt += " init: "         + m_init->str() + " ";
    fmt += "}";
    return fmt;
}

auto make_numeric_literal_node(token tk) -> node_ref_t {
    return std::make_shared<numeric_literal_node>(tk);
}
auto make_binary_expression_node(token tk, node_ref_t left, node_ref_t right) -> node_ref_t {
    return std::make_shared<binary_expression_node>(tk, left, right);
}
auto make_variable_declaration_node(token tk, node_ref_t init) -> node_ref_t {
    return std::make_shared<variable_declaration_node>(tk, init);
}

}

