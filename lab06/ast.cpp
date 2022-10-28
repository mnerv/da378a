/**
 * @file   ast.hpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  AST C@ language.
 * @date   2022-10-01
 *
 * @copyright Copyright (c) 2022
 */
#include "ast.hpp"

#include <utility>

namespace cat {
identifier_node::identifier_node(token tk) : ast_node(std::move(tk), node_type::identifier), m_name(m_token.value()) { }

auto identifier_node::str() const -> std::string {
    std::string fmt{name()};
    fmt += "{";
    fmt += " id: \"" + m_name + "\" ";
    fmt += "}";
    return fmt;
}

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

string_literal_node::string_literal_node(token tk) : ast_node(std::move(tk), node_type::string_literal) {
    m_value = m_token.value();
}

auto string_literal_node::str() const -> std::string {
    using namespace std::string_literals;
    // FIXME: Sanitize string
    std::string fmt{name()};
    fmt += "{";
    fmt += " value: \""s + m_value         + "\",";
    fmt += " raw: \""s   + m_token.value() + "\" ";
    fmt += "}";
    return fmt;
}

assignment_expression_node::assignment_expression_node(token tk, node_ref_t left, node_ref_t right)
    : ast_node(std::move(tk), node_type::assignment_expression), m_operator(m_token.type()) {
    m_left  = std::move(left);
    m_right = std::move(right);
}

auto assignment_expression_node::str() const -> std::string {
    std::string fmt{name()};
    fmt += "{";
    fmt += " operator: \"" + token_type_str(m_operator) + "\",";
    fmt += " left: "       + m_left->str()   + ",";
    fmt += " right: "      + m_right->str()  + " ";
    fmt += "}";
    return fmt;
}

binary_expression_node::binary_expression_node(token tk, node_ref_t left, node_ref_t right)
    : ast_node(std::move(tk), node_type::binary_expression) {
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

unary_expression_node::unary_expression_node(token tk, node_ref_t arg, bool prefix)
    : ast_node(std::move(tk), node_type::unary_expression), m_arg(arg), m_prefix(prefix) {
    m_operator = m_token.type();
}

auto unary_expression_node::str() const -> std::string  {
    return name();
}

variable_declarator_node::variable_declarator_node(node_ref_t id, node_ref_t init)
    : ast_node(id->raw_token(), node_type::variable_declarator), m_id(std::move(id)), m_init(std::move(init)) {
}

auto variable_declarator_node::str() const -> std::string {
    std::string fmt{name()};
    fmt += "{";
    fmt += " id: \"" + m_id->str()   + "\",";
    fmt += " init: " + m_init->str() + " ";
    fmt += "}";
    return fmt;
}

call_expression_node::call_expression_node(ref<identifier_node> callee, std::vector<node_ref_t> args)
    : ast_node(callee->raw_token(), node_type::call_expression)
    , m_callee(std::move(callee)), m_args(std::move(args)) { }

auto call_expression_node::str() const -> std::string {
    std::string fmt{name()};
    fmt += "{";
    fmt += " callee: " + m_callee->str() + ",";
    fmt += " args: [ ";
    for (std::size_t i = 0; i < m_args.size(); ++i) {
        fmt += m_args[i]->str();
        if (i < m_args.size() - 1) fmt += ", ";
    }
    fmt += " ] ";
    fmt += "}";
    return fmt;
}

}

