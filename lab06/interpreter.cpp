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
interpreter::interpreter(std::ostream& output) : m_output(output) {}
interpreter::~interpreter() = default;

auto interpreter::eval([[maybe_unused]]node_ref_t const& node) -> bool {
    return false;
}
}
