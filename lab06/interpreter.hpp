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
#include "parser.hpp"

namespace cat {
class interpreter {
  public:
    interpreter(std::ostream& output);
    ~interpreter();

    auto eval(node_ref_t const& node) -> bool;

  private:
    std::ostream& m_output;
};
}

#endif  // CATC_INTERPRETER_HPP
