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

enum class node_type : std::uint32_t {
    identifier,
    numeric_literal,
    binary_expression,
    variable_declaration,
    call_expression,
};

class ast_node {
  public:
    ast_node(token tk, node_type type) : m_token(std::move(tk)), m_type(type) {}
    virtual ~ast_node() = default;

    virtual auto name() const -> char const* = 0;
    virtual auto str()  const -> std::string = 0;
    virtual auto raw_token() const -> token const& { return m_token; }

    auto is_type(node_type const& type) const -> bool { return m_type == type; };
    auto left()  const -> node_ref_t { return m_left; }
    auto right() const -> node_ref_t { return m_right; }

    //auto set_left(node_ref_t const& left)   -> void { m_left = left; }
    //auto set_right(node_ref_t const& right) -> void { m_right = right; }

  protected:
    node_ref_t m_left{nullptr};
    node_ref_t m_right{nullptr};
    token      m_token;
    node_type  m_type;
};

class identifier_node : public ast_node {
  public:
    identifier_node(token tk);

    auto name() const -> char const* override { return "identifier"; }
    auto str() const -> std::string override;

  private:
    std::string m_name;
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

// https://en.wikipedia.org/wiki/Binary_operation
class binary_expression_node : public ast_node {
  public:
    binary_expression_node(token tk, node_ref_t left, node_ref_t right);

    auto name() const -> char const* override { return "binary_expression"; }
    auto str() const -> std::string override;

    auto operation() const -> token_type { return m_operator; }

  private:
    token_type m_operator;
};

class variable_declaration_node : public ast_node {
  public:
    variable_declaration_node(token tk, node_ref_t init);

    auto name() const -> char const* override { return "variable_declaration"; }
    auto str() const -> std::string override;

    auto id() const -> node_ref_t { return m_id; }

  private:
    node_ref_t m_id;
    node_ref_t m_init;
};

class call_expression_node : public ast_node {
  public:
    call_expression_node(token tk, std::vector<node_ref_t> args);

    auto name() const -> char const* override { return "call_expression"; };
    auto str()  const -> std::string override;

    auto callee() const -> node_ref_t { return m_callee; }
    auto args() const -> std::vector<node_ref_t> const& { return m_args; }

  private:
    node_ref_t              m_callee;
    std::vector<node_ref_t> m_args;
};

auto make_identifier_node(token tk) -> node_ref_t;
auto make_numeric_literal_node(token tk) -> node_ref_t;
auto make_binary_expression_node(token tk, node_ref_t left, node_ref_t right) -> node_ref_t;
auto make_variable_declaration_node(token tk, node_ref_t init) -> node_ref_t;
auto make_call_expression_node(token tk, std::vector<node_ref_t> args) -> node_ref_t;

}

#endif  // CATC_AST_HPP
