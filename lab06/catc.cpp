/**
 * @file   catc.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  catc is a mini project interpreter for the C@ (cat) language.
 *         This program compiles and interpret the C@ code.
 *
 *         Functionality requirements:
 *           - Read code from a source file
 *           - Parse and execute according to the C@ grammar. Add your own code
 *             (or code suggested by a teacher)
 *           - Output sends to the std::ostream, such as std::cout (standard out)
 *           - Terminals defined by regular expressions (int and variable)
 *             should be matched properly to the provided pattern. int-tokens
 *             should be matched before being ast to C++ integers.
 * @date   2022-09-15
 *
 * @copyright Copyright (c) 2022
 */
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <ios>
#include <numeric>

#include "lexer.hpp"
#include "parser.hpp"

namespace nrv {
/**
 * Simple read textfile.
 *
 * @link   http://notes.mnerv.dev/cpp.html#read-text-into-stdstring
 * @param  filename Path to text file.
 * @return Text content.
 */
static auto read_text(std::string const& filename) -> std::string {
    std::ifstream input{filename, std::ios::in};
    if (!input.is_open() || input.fail())
        throw std::runtime_error("ERROR: Loading textfile!");
    return {
        std::istreambuf_iterator<char>(input),
        std::istreambuf_iterator<char>()
    };
}
}

static auto recursive_print(cat::node_ref_t const& node, std::int32_t const& level = 0) -> void {
    constexpr auto indent_size = 2;
    if (node == nullptr) return;
    auto indent = [](std::int32_t const& level) {
        std::string str;
        for (auto i = 0; i < level; ++i) str += " ";
        return str;
    };
    std::cout << node->name() << " {";
    std::cout << "\n";

    switch (node->type()) {
    case cat::node_type::identifier: {
        auto const& n = static_cast<cat::identifier_node const&>(*node);
        std::cout << indent(level + indent_size) << "id: \"" << n.id() << "\",";
        break;
    }
    case cat::node_type::numeric_literal: {
        auto const& n = static_cast<cat::numeric_literal_node const&>(*node);
        std::cout << indent(level + indent_size) << "value: " << n.value() << ",\n";
        std::cout << indent(level + indent_size) << "raw: \"" << n.value() << "\",";
        break;
    }
    case cat::node_type::assignment_expression: {
        auto const& n = static_cast<cat::assignment_expression_node const&>(*node);
        std::cout << indent(level + indent_size) << "operator: \"" << n.raw_token().value() << "\",";
        break;
    }
    case cat::node_type::binary_expression: {
        auto const& n = static_cast<cat::binary_expression_node const&>(*node);
        std::cout << indent(level + indent_size) << "operator: \"" << n.raw_token().value() << "\",";
        break;
    }
    case cat::node_type::variable_declarator: {
        auto const& n = static_cast<cat::variable_declarator_node const&>(*node);
        std::cout << indent(level + indent_size) << "id: \"" << n.id()->raw_token().value() << "\",\n";
        std::cout << indent(level + indent_size) << "init: ";
        recursive_print(n.init(), level + indent_size);
        break;
    }
    case cat::node_type::call_expression: {
        auto const& n = static_cast<cat::call_expression_node const&>(*node);
        std::cout << indent(level + indent_size) << "callee: \"" << n.callee()->raw_token().value() << "\",\n";
        std::cout << indent(level + indent_size) << "args: [ ";
        auto const& args = n.args();
        if (args.size() != 0) std::cout << "\n" << indent(level + indent_size);
        for (std::size_t i = 0; i < args.size(); ++i) {
            auto const& arg = args[i];
            std::cout << indent(level + indent_size) << i << ": ";
            recursive_print(arg, level + indent_size * 2);
            std::cout << ",\n";
            std::cout << indent(level + indent_size);
        }
        std::cout << "]";
        break;
    }
    default:
        std::cout << indent(level + indent_size) << "NOT_IMPLEMENTED: " << node->name();
    }

    if (node->left() != nullptr) {
        std::cout << "\n";
        std::cout << indent(level + indent_size) << "left: ";
        recursive_print(node->left(), level + indent_size);
    }
    if (node->right() != nullptr) {
        std::cout << ",\n";
        std::cout << indent(level + indent_size) << "right: ";
        recursive_print(node->right(), level + indent_size);
    }
    std::cout << "\n";
    std::cout << indent(level) << "}";
    if (level == 0) std::cout << "\n";
}

auto main(int argc, char const* argv[]) -> int {
    if (argc < 2) {
        std::cout << "catc: error: no input file!\n";
        return 1;
    }

    std::filesystem::path source_file{argv[1]};
    if (!std::filesystem::exists(source_file)) {
        std::cerr << "catc: error: file does not exist!\n";
        return 1;
    }

    [[maybe_unused]]auto const source = nrv::read_text(source_file.string());
    constexpr auto test_source = "1 + 1";
    cat::lexer lexer{test_source};
    auto const tokens = lexer.tokenize();
    cat::parser parser{tokens};
    parser.parse();

    auto tk1 = cat::token("1", cat::token_type::numeric_literal);
    auto tk2 = cat::token("2", cat::token_type::numeric_literal);
    auto tkp = cat::token("+", cat::token_type::plus);

    auto n1 = cat::make_numeric_literal_node(tk1);
    auto n2 = cat::make_numeric_literal_node(tk2);
    auto np = cat::make_binary_expression_node(tkp, n1, n2);

    recursive_print(np);

    auto tka = cat::token("*", cat::token_type::asterisk);
    auto na = cat::make_binary_expression_node(tka, n1, np);

    auto tkid = cat::token("hello", cat::token_type::identifier);
    auto nid = cat::make_identifier_node(tkid);
    auto niddec = cat::make_variable_declarator_node(nid, na);

    recursive_print(niddec);

    auto tkcall = cat::token("config", cat::token_type::identifier);
    auto ncall = cat::make_identifier_node(tkcall);
    auto ncallex = cat::make_call_expression_node(ncall, {n1, n2, nid, np});

    recursive_print(ncallex);

    auto tkequal = cat::token("=", cat::token_type::equals);
    auto nass = cat::make_assignment_expression_node(tkequal, nid, n1);

    recursive_print(nass);
    return 0;
}

