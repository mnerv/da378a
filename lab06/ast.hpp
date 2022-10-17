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
#include <memory>
#include <utility>

#include "token.hpp"

namespace cat {
using node_ref_t = std::shared_ptr<class ast_node>;

class ast_node {
  public:
    ast_node(token tk) : m_token(std::move(tk)) {}
    virtual ~ast_node() = default;

    virtual auto name() const -> char const* = 0;
    virtual auto str()  const -> std::string = 0;
    virtual auto raw_token() const -> token const& { return m_token; }

    auto left()  const -> node_ref_t { return m_left; }
    auto right() const -> node_ref_t { return m_right; }

    //auto set_left(node_ref_t const& left)   -> void { m_left = left; }
    //auto set_right(node_ref_t const& right) -> void { m_right = right; }

  protected:
    node_ref_t m_left{nullptr};
    node_ref_t m_right{nullptr};
    token      m_token;
};

class numeric_literal_node : public ast_node {
  public:
    numeric_literal_node(token tk);

    auto name() const -> char const* override { return "numeric_literal"; }
    auto str() const -> std::string override;

    auto value() const -> std::int32_t { return m_value; }

  private:
    std::int32_t m_value;
};

class binary_expression_node : public ast_node {
public:
    binary_expression_node(token tk, node_ref_t left, node_ref_t right);

    auto name() const -> char const* override { return "binary_expression"; }
    auto str() const -> std::string override;
};
}

#endif  // CATC_AST_HPP
