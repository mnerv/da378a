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
#include <unordered_map>
#include <optional>

namespace cat {
// Preprocessor magic for automatically setting up enumerations.
// notes:
//   - asterisk  = multiplication
//   - equals    = assignment
//   - operator_ = operator (reserved keyword in C++)
#define ENUMERATOR_CATLANG_TOKENS                               \
        ENUMERATOR_CATLANG_TOKEN(asterisk       , operator_  )  \
        ENUMERATOR_CATLANG_TOKEN(equals         , operator_  )  \
        ENUMERATOR_CATLANG_TOKEN(invalid        , invalid    )  \
        ENUMERATOR_CATLANG_TOKEN(minus          , operator_  )  \
        ENUMERATOR_CATLANG_TOKEN(numeric_literal, number     )  \
        ENUMERATOR_CATLANG_TOKEN(newline        , punctuation)  \
        ENUMERATOR_CATLANG_TOKEN(paren_open     , punctuation)  \
        ENUMERATOR_CATLANG_TOKEN(paren_close    , punctuation)  \
        ENUMERATOR_CATLANG_TOKEN(plus           , operator_  )  \
        ENUMERATOR_CATLANG_TOKEN(identifier     , identifier )  \
        ENUMERATOR_CATLANG_TOKEN(slash          , operator_  )

enum class token_type : std::uint32_t {
#define ENUMERATOR_CATLANG_TOKEN(type, category) type,
    ENUMERATOR_CATLANG_TOKENS
#undef  ENUMERATOR_CATLANG_TOKEN
    _count
};

auto token_type_str(token_type const& type) -> std::string;

enum class token_category : std::uint32_t {
    identifier,
    invalid,
    number,
    keyword,
    operator_,
    punctuation,
    _count
};

auto token_category_str(token_category const& type) -> std::string;
auto token_type_category(token_type const& type) -> token_category;

struct source_position {
    std::size_t line;
    std::size_t column;
    std::size_t offset;
};

struct source_range {
    std::string filename;
    source_position start;
    source_position end;
};

/**
 * Token container, describe what type of token it is and what value it has.
 */
class token {
  public:
    token() = default;
    token(std::string value, token_type const& type, std::string const& filename = "", std::size_t const& line = 0, std::size_t const& column = 0, std::size_t const& offset = 0);

    auto category() const -> token_category;
    auto type() const -> token_type;
    auto value() const -> std::string;
    auto filename() const->std::string;
    auto str() const -> std::string;

  public:
    static auto str_token(std::string const& str) -> std::optional<token_type>;
    static auto is_numeric(std::string const& str) -> bool;
    static auto is_float(std::string const& str) -> bool;
    static auto is_identifier(std::string const& str) -> bool;

  private:
    std::string    m_value{};
    token_type     m_type{token_type::invalid};
    token_category m_category{token_category::invalid};
    std::string    m_filename;
    std::size_t    m_line;
    [[maybe_unused]]std::size_t    m_column;
    [[maybe_unused]]std::size_t    m_offset;

  private:
    static std::unordered_map<std::string, token_type> s_token_strs;
};
}
#endif  // CATC_TOKEN_HPP
