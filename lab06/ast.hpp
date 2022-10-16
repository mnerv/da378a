/**
 * @file   ast.hpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  AST C@ language.
 * @date   2022-10-01
 *
 * @copyright Copyright (c) 2022
 */
#ifndef CATC_AST_HPP
#define CATC_AST_HPP

#include <string>

namespace cat {
class ast_node {
  public:
    virtual auto name() const -> char const* = 0;
};

class expression_node : public ast_node {
  public:
    auto name() const -> char const* override;
};
}

#endif  // CATC_AST_HPP
