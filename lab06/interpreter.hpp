/**
 * @file   interpreter.hpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Interpreter C@ language.
 * @date   2022-10-01
 *
 * @copyright Copyright (c) 2022
 */
#ifndef CATC_INTERPRETER_HPP
#define CATC_INTERPRETER_HPP

#include <string>
#include <ostream>
#include <unordered_map>

#include "parser.hpp"

namespace cat {
auto recursive_print(std::ostream& output, node_ref_t const& node, std::int32_t const& level = 0, std::int32_t const& indent_size = 2) -> void;

class interpreter {
  public:
    interpreter(std::ostream& output);
    ~interpreter();

    auto eval(node_ref_t const& node) -> void;

  private:
    auto eval_expression(node_ref_t node) -> std::int32_t;
    auto print(std::int32_t const& num) -> void;
    auto dump_ast(std::string const& value) -> void;

  private:
    std::ostream& m_output;

  private:
    std::unordered_map<std::string, std::int32_t> m_variables;

    enum class config_mode {
        dec, bin, hex
    };
    config_mode m_mode{config_mode::dec};
};
}

#endif  // CATC_INTERPRETER_HPP
