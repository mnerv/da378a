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

#include <memory>
#include <ostream>
#include "parser.hpp"

namespace cat {
auto recursive_print(std::ostream& output, cat::node_ref_t const& node, std::int32_t const& level = 0, std::int32_t const& indent_size = 2) -> void;

class interpreter {
  public:
    interpreter(std::ostream& output);
    ~interpreter();

    auto eval(node_ref_t const& node) -> bool;

  private:
    [[maybe_unused]]std::ostream& m_output;
};
}

#endif  // CATC_INTERPRETER_HPP
