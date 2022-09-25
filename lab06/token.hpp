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
#define __ENUM_CAT_TOKENS                   \
        __ENUM_CAT_TOKEN(config, keyword)   \
        __ENUM_CAT_TOKEN(print, keyword)    \
        __ENUM_CAT_TOKEN(assign, keyword)   \
        __ENUM_CAT_TOKEN(invalid, invalid)

enum class token_type : std::uint32_t {
#define __ENUM_CAT_TOKEN(type, category) type,
    __ENUM_CAT_TOKENS
#undef  __ENUM_CAT_TOKEN
    _count
};

constexpr auto token_type_str(token_type const& type) -> std::string {
    switch (type) {
#define __ENUM_CAT_TOKEN(_type, category) case token_type::_type: return #_type;
        __ENUM_CAT_TOKENS
#undef  __ENUM_CAT_TOKEN
        default: return "invalid";
    }
}

enum class token_category : std::uint32_t {
    invalid,
    number,
    keyword,
    driver,  // operator
    _count
};

constexpr auto token_category_str(token_category const& type) -> std::string {
    switch (type) {
        case token_category::number:  return "number";
        case token_category::keyword: return "keyword";
        case token_category::driver:  return "operator";
        default:
        case token_category::invalid: return "invalid";
    }
}
#undef __ENUM_CAT_TOKENS

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
#endif //CATC_TOKEN_HPP
