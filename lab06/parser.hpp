/**
 * @file   parser.hpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Parser C@ language.
 * @date   2022-09-27
 *
 * @copyright Copyright (c) 2022
 */
#ifndef CATC_PARSER_HPP
#define CATC_PARSER_HPP

#include <vector>
#include <memory>

#include "token.hpp"
#include "ast.hpp"

namespace cat {

class parser {
  public:
    parser(std::vector<token> const& tokens);
    ~parser();

    auto parse() -> node_ref_t;
    auto nodes() const -> std::vector<node_ref_t> const&;

  private:
    auto next_token() -> void;
    auto peek() const -> token const&;

  private:
    std::size_t             m_cursor;
    std::vector<token>      m_tokens;
    std::vector<node_ref_t> m_nodes;
};

}

#endif  // CATC_PARSER_HPP
