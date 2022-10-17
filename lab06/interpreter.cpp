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
interpreter::interpreter(std::vector<node_ref_t> const& nodes) : m_nodes(nodes) {
}
interpreter::~interpreter() = default;
}
