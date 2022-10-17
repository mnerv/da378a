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

#include <vector>

#include "ast.hpp"

namespace cat {
class interpreter {
  public:
    interpreter(std::vector<node_ref_t> const& nodes);
    ~interpreter();

  private:
    std::vector<node_ref_t> m_nodes;
};
}

#endif  // CATC_INTERPRETER_HPP
