/**
 * @file   interpreter.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Interpreter C@ language.
 * @date   2022-10-01
 *
 * @copyright Copyright (c) 2022
 */
#include "interpreter.hpp"

namespace cat {
interpreter::interpreter(std::ostream& output) : m_output(output), m_variables({}) {
    (void)m_output;
    (void)m_variables;
}
interpreter::~interpreter() = default;

auto interpreter::eval([[maybe_unused]]node_ref_t const& node) -> bool {
    return false;
}

auto recursive_print(std::ostream& output, cat::node_ref_t const& node, std::int32_t const& level, std::int32_t const& indent_size) -> void {
    using namespace std::string_literals;
    if (node == nullptr) return;
    auto indent = [](std::int32_t const& indent_level) {
        std::string str;
        for (auto i = 0; i < indent_level; ++i) str += " ";
        return str;
    };
    output << std::string(node->name()) << " {"s;
    output << "\n"s;

    switch (node->type()) {
    case cat::node_type::identifier: {
        auto const& n = dynamic_cast<cat::identifier_node const&>(*node);
        output << indent(level + indent_size) << "id: \""s << n.id() << "\","s;
        break;
    }
    case cat::node_type::numeric_literal: {
        auto const& n = dynamic_cast<cat::numeric_literal_node const&>(*node);
        output << indent(level + indent_size) << "value: "s << std::to_string(n.value()) << ",\n"s;
        output << indent(level + indent_size) << "raw: \""s << std::to_string(n.value()) << "\","s;
        break;
    }
    case cat::node_type::assignment_expression: {
        auto const& n = dynamic_cast<cat::assignment_expression_node const&>(*node);
        output << indent(level + indent_size) << "operator: \""s << n.raw_token().value() << "\","s;
        break;
    }
    case cat::node_type::binary_expression: {
        auto const& n = dynamic_cast<cat::binary_expression_node const&>(*node);
        output << indent(level + indent_size) << "operator: \""s << n.raw_token().value() << "\","s;
        break;
    }
    case cat::node_type::variable_declarator: {
        auto const& n = dynamic_cast<cat::variable_declarator_node const&>(*node);
        output << indent(level + indent_size) << "id: \""s << n.id()->raw_token().value() << "\",\n"s;
        output << indent(level + indent_size) << "init: "s;
        recursive_print(output, n.init(), level + indent_size);
        break;
    }
    case cat::node_type::call_expression: {
        auto const& n = dynamic_cast<cat::call_expression_node const&>(*node);
        output << indent(level + indent_size) << "callee: \""s << n.callee()->raw_token().value() << "\",\n"s;
        output << indent(level + indent_size) << "args: [ "s;
        auto const& args = n.args();
        if (!args.empty()) output << "\n"s << indent(level + indent_size);
        for (std::size_t i = 0; i < args.size(); ++i) {
            auto const& arg = args[i];
            output << indent(level + indent_size) << std::to_string(i) << ": "s;
            recursive_print(output, arg, level + indent_size * 2);
            output << ",\n"s;
            output << indent(level + indent_size);
        }
        output << "]"s;
        break;
    }
    default:
        output << indent(level + indent_size) << "NOT_IMPLEMENTED: "s << std::string(node->name());
        break;
    }

    if (node->left() != nullptr) {
        output << "\n"s;
        output << indent(level + indent_size) << "left: "s;
        recursive_print(output, node->left(), level + indent_size);
    }
    if (node->right() != nullptr) {
        output << ",\n"s;
        output << indent(level + indent_size) << "right: "s;
        recursive_print(output, node->right(), level + indent_size);
    }
    output << "\n"s;
    output << indent(level) << "}"s;
    if (level == 0) output << "\n"s;
}
}
