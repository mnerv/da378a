/**
 * @file   interpreter.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Interpreter C@ language.
 * @date   2022-10-01
 *
 * @copyright Copyright (c) 2022
 */
#include "interpreter.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include <stdexcept>
#include <sstream>
#include <stack>
#include <vector>

namespace cat {
interpreter::interpreter(std::ostream& output) : m_output(output), m_variables({}) {
    (void)m_output;
    (void)m_variables;
}
interpreter::~interpreter() = default;

auto interpreter::eval(node_ref_t const& node) -> void {
    using namespace std::string_literals;
    if (node->type() == node_type::call_expression) {
        auto call = std::dynamic_pointer_cast<call_expression_node>(node);
        if (call->callee()->id() == "config") {
            if (!call->args().empty()) {
                auto const& mode = *std::begin(call->args());
                if (mode->raw_token().value() == "dec") {
                    m_mode = config_mode::dec;
                } else if (mode->raw_token().value() == "bin") {
                    m_mode = config_mode::bin;
                }  else if (mode->raw_token().value() == "hex") {
                    m_mode = config_mode::hex;
                } else {
                    throw std::runtime_error("config error: invalid argument\n    expected: config [dec|bin|hex], got: config "s
                                             + token::sanitize_str(mode->raw_token().value()));
                }
            } else {
                throw std::runtime_error("Invalid argument\nexpected: [dec|bin|hex], got zero arguments");
            }
        } else if (call->callee()->id() == "print") {
            if (call->args().empty())
                throw std::runtime_error("print error: invalid argument\n    expected none zero arguments");

            auto const& arg = call->args()[0];
            if (arg->type() == node_type::string_literal) {
                auto const& str = std::dynamic_pointer_cast<string_literal_node>(arg);
                m_output << str->value();
            } else if (arg->type() == node_type::binary_expression) {
                print(eval_expression(arg));
            } else if (arg->type() == node_type::identifier) {
                auto const& n = std::dynamic_pointer_cast<identifier_node>(arg);
                auto it = m_variables.find(n->id());
                if (it == std::end(m_variables)) m_output << n->id() << ": undefined\n";
                else print(it->second);
            } else if(arg->type() == node_type::numeric_literal) {
                auto const& n = std::dynamic_pointer_cast<numeric_literal_node>(arg);
                print(n->value());
            } else {
                throw std::runtime_error("print error: unsupported argument type\n    "s + arg->str());
            }
        } else if (call->callee()->id() == "dump_ast") {
            dump_ast(call->args()[0]->raw_token().value());
        } else {
        }
    } else if (node->type() == node_type::assignment_expression) {
        auto ret = eval_expression(node->right());
        auto id = std::dynamic_pointer_cast<identifier_node>(node->left());
        m_variables.insert({id->id(), ret});
    } else if (node->type() == node_type::binary_expression){
        m_output << "i32: ";
        print(eval_expression(node));
    } else if (node->type() == node_type::numeric_literal) {
        m_output << "i32: ";
        print(eval_expression(node));
    } else {
        throw std::runtime_error("Invalid: "s + node->str());
    }
}

auto interpreter::eval_expression(node_ref_t root) -> std::int32_t {
    if (root == nullptr) return 0;
    if (root->type() == node_type::unary_expression) {
        auto const unary = std::dynamic_pointer_cast<unary_expression_node>(root);
        auto const arg = eval_expression(unary->arg());
        if (unary->operator_type() == token_type::plus) {
            return +arg;
        }
        if (unary->operator_type() == token_type::minus) {
            return -arg;
        }
    }
    if (root->left() == nullptr && root->right() == nullptr) {
        if (root->type() == node_type::numeric_literal){
            auto const ret = std::dynamic_pointer_cast<numeric_literal_node>(root);
            return ret->value();
        }
        if (root->type() == node_type::identifier){
            auto const ret = std::dynamic_pointer_cast<identifier_node>(root);
            auto it = m_variables.find(ret->id());
            if (it != std::end(m_variables)) return it->second;
            throw std::runtime_error("expression error: " + ret->id() + " is undefined");
        }
    }
    auto const bin = std::dynamic_pointer_cast<binary_expression_node>(root);
    auto const left  = eval_expression(root->left());
    auto const right = eval_expression(root->right());
    if (bin->operator_type() == token_type::plus) {
        return left + right;
    }
    if (bin->operator_type() == token_type::minus) {
        return left - right;
    }
    if (bin->operator_type() == token_type::asterisk) {
        return left * right;
    }
    if (bin->operator_type() == token_type::slash) {
        return left / right;
    }
    throw std::runtime_error("invalid expression: " + root->str());
}

auto interpreter::print(std::int32_t const& num) -> void {
    constexpr std::size_t BIT_SIZE = 32;
    switch (m_mode) {
        case config_mode::bin:
            m_output << std::bitset<BIT_SIZE>(static_cast<std::uint32_t>(num)).to_string() << "\n";
            break;
        case config_mode::hex:
            m_output << std::hex << "0x" << num << "\n";
            break;
        case config_mode::dec:
            m_output << std::dec << num << "\n";
            break;
    }
}
auto interpreter::dump_ast(std::string const& value) -> void {
    lexer lex{value};
    auto const tokens = lex.tokenize();
    parser par{tokens};
    par.parse();
    auto const& nodes = par.program();
    m_output << "Abstract Syntax Tree [\n";
    for (auto const& node : nodes) {
        std::stringstream ss;
        recursive_print(ss, node);
        auto const str = ss.str();
        m_output << "    ";
        for (std::size_t i = 0; i < str.size(); ++i) {
            m_output << str[i];
            if (str[i] == '\n' && i < str.size() - 1) m_output << "    ";
        }
        m_output << ",\n";
    }
    m_output << "]\n";
}

auto recursive_print(std::ostream& output, node_ref_t const& node, std::int32_t const& level, std::int32_t const& indent_size) -> void {
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
    case node_type::identifier: {
        auto const& n = dynamic_cast<identifier_node const&>(*node);
        output << indent(level + indent_size) << "id: \""s << n.id() << "\","s;
        break;
    }
    case node_type::numeric_literal: {
        auto const& n = dynamic_cast<numeric_literal_node const&>(*node);
        output << indent(level + indent_size) << "value: "s << std::to_string(n.value()) << ",\n"s;
        output << indent(level + indent_size) << "raw: \""s << std::to_string(n.value()) << "\","s;
        break;
    }
    case node_type::assignment_expression: {
        auto const& n = dynamic_cast<assignment_expression_node const&>(*node);
        output << indent(level + indent_size) << "operator: \""s << n.raw_token().value() << "\","s;
        break;
    }
    case node_type::binary_expression: {
        auto const& n = dynamic_cast<binary_expression_node const&>(*node);
        output << indent(level + indent_size) << "operator: \""s << n.raw_token().value() << "\","s;
        break;
    }
    case node_type::variable_declarator: {
        auto const& n = dynamic_cast<variable_declarator_node const&>(*node);
        output << indent(level + indent_size) << "id: \""s << n.id()->raw_token().value() << "\",\n"s;
        output << indent(level + indent_size) << "init: "s;
        recursive_print(output, n.init(), level + indent_size);
        break;
    }
    case node_type::call_expression: {
        auto const& n = dynamic_cast<call_expression_node const&>(*node);
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
    case node_type::string_literal: {
        auto const& n = dynamic_cast<string_literal_node const&>(*node);
        output << indent(level + indent_size) << "value: \""s << token::sanitize_str(n.value()) << "\","s;
        break;
    }
    case node_type::unary_expression: {
        auto const& n = dynamic_cast<unary_expression_node const&>(*node);
        output << indent(level + indent_size) << "operator: \""s << n.raw_token().value() << "\",\n"s;
        output << indent(level + indent_size) << "prefix: "s     << (n.is_prefix() ? "true" : "false") << ",\n"s;
        output << indent(level + indent_size) << "argument: "s;
        recursive_print(output, n.arg(), level + indent_size * 2);
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
    if (level == 0) output << ""s;
}
}
