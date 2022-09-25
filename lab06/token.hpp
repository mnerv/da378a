/**
 * @file   token.hpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Token C@ language.
 * @date   2022-09-25
 *
 * @copyright Copyright (c) 2022
 */
#ifndef CATC_TOKEN_HPP
#define CATC_TOKEN_HPP
#include <string>

namespace cat {
// Preprocessor magic for automatically setting up enumerations
#define __ENUMERATOR_CATLANG_TOKENS                   \
        __ENUMERATOR_CATLANG_TOKEN(config, keyword)   \
        __ENUMERATOR_CATLANG_TOKEN(print, keyword)    \
        __ENUMERATOR_CATLANG_TOKEN(assign, keyword)   \
        __ENUMERATOR_CATLANG_TOKEN(invalid, invalid)

enum class token_type : std::uint32_t {
#define __ENUMERATOR_CATLANG_TOKEN(type, category) type,
    __ENUMERATOR_CATLANG_TOKENS
#undef  __ENUMERATOR_CATLANG_TOKEN
    _count
};

auto token_type_str(token_type const& type) -> std::string;

enum class token_category : std::uint32_t {
    invalid,
    number,
    keyword,
    driver,  // operator (+-/*, etc)
    _count
};

auto token_category_str(token_category const& type) -> std::string;

/**
 * Token container, describe what type of token it is and what value it has.
 */
class token {
  public:
    token() = default;
    token(std::string const& value, token_type const& type);

    auto str() const -> std::string;

  private:
    std::string m_value{};
    token_type  m_type{token_type::invalid};
};
}
#endif  // CATC_TOKEN_HPP
