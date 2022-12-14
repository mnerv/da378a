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

#include <vector>
#include <string>
#include <memory>
#include <utility>

#include "token.hpp"

namespace cat {
template<typename T>
using ref = std::shared_ptr<T>;

template<typename T, typename... Args>
auto make_ref(Args&&... args) -> std::shared_ptr<T> {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

using node_ref_t = ref<class ast_node>;

enum class node_type : std::uint32_t {
    identifier,
    numeric_literal,
    string_literal,
    assignment_expression,
    binary_expression,
    unary_expression,
    call_expression,
//    variable_declarator,
};

class ast_node {
  public:
    ast_node(token tk, node_type type) : m_token(std::move(tk)), m_type(type) {}
    virtual ~ast_node() = default;

    virtual auto name() const -> char const* = 0;
    virtual auto str()  const -> std::string = 0;
    virtual auto raw_token() const -> token const& { return m_token; }

    auto type() const -> node_type const& { return m_type; }
    auto is_type(node_type const& type) const -> bool { return m_type == type; };
    auto left()  const -> node_ref_t const& { return m_left; }
    auto right() const -> node_ref_t const& { return m_right; }

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

    auto id() const -> std::string const& { return m_name; }

  private:
    std::string m_name;
};

class numeric_literal_node : public ast_node {
  public:
    numeric_literal_node(token tk);

    auto name() const -> char const* override { return "numeric_literal"; }
    auto str() const -> std::string override;

    auto value() const -> std::int32_t const& { return m_value; }

  private:
    std::int32_t m_value;
};

class string_literal_node : public ast_node {
  public:
    string_literal_node(token tk);

    auto name() const -> char const* override { return "string_literal"; }
    auto str() const -> std::string override;

    auto value() const -> std::string const& { return m_value; }

  private:
    std::string m_value;
};

class assignment_expression_node : public ast_node {
  public:
    assignment_expression_node(token tk, node_ref_t left, node_ref_t right);

    auto name() const -> char const* override { return "assignment_expression"; }
    auto str() const -> std::string override;

    auto operator_type() const -> token_type const& { return m_operator; }

  private:
    token_type m_operator;
};

// https://en.wikipedia.org/wiki/Binary_operation
class binary_expression_node : public ast_node {
  public:
    binary_expression_node(token tk, node_ref_t left, node_ref_t right);

    auto name() const -> char const* override { return "binary_expression"; }
    auto str() const -> std::string override;

    auto operator_type() const -> token_type const& { return m_operator; }

  private:
    token_type m_operator;
};

class unary_expression_node : public ast_node {
  public:
    unary_expression_node(token tk, node_ref_t arg, bool prefix);

    auto name() const -> char const* override { return "unary_expression"; }
    auto str() const -> std::string override;

    auto arg() const -> node_ref_t const& { return m_arg; }
    auto is_prefix() const -> bool const& { return m_prefix; }
    auto operator_type() const -> token_type const& { return m_operator; }

  private:
    node_ref_t m_arg;
    bool       m_prefix;
    token_type m_operator;
};

class call_expression_node : public ast_node {
  public:
    call_expression_node(ref<identifier_node> callee, std::vector<node_ref_t> args);

    auto name() const -> char const* override { return "call_expression"; };
    auto str()  const -> std::string override;

    auto callee() const -> ref<identifier_node> const& { return m_callee; }
    auto args() const -> std::vector<node_ref_t> const& { return m_args; }

  private:
    ref<identifier_node>    m_callee;
    std::vector<node_ref_t> m_args;
};

//class variable_declarator_node : public ast_node {
//  public:
//    variable_declarator_node(node_ref_t id, node_ref_t init);
//
//    auto name() const -> char const* override { return "variable_declarator"; }
//    auto str() const -> std::string override;
//
//    auto id() const -> node_ref_t const& { return m_id; }
//    auto init() const -> node_ref_t const& { return m_init; }
//
//  private:
//    node_ref_t m_id;
//    node_ref_t m_init;
//};
}

#endif  // CATC_AST_HPP
