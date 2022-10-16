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
#include "lexer.hpp"
#include "ast.hpp"

namespace cat {

class parser {
  public:
    parser(std::vector<token> const& tokens);
    ~parser();

  private:
    std::vector<token> m_tokens;
    std::vector<std::shared_ptr<ast_node>> m_nodes;
};

}

#endif  // CATC_PARSER_HPP
