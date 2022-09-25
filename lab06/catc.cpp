/**
 * @file   catc.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  catc is a mini project interpreter for the C@ (cat) language.
 *         This program compiles and interpret the C@ code.
 * @date   2022-09-14
 *
 * @copyright Copyright (c) 2022
 */
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <optional>

namespace cat {
enum class keyword : std::uint32_t {
    none = 0,
    config,
    print,
};

std::unordered_map<keyword, std::string> keyword_strs{
    {keyword::config, "config"},
    {keyword::print,  "print" },
};

/**
 * C@ lang program statements. At the moment the program only supports three
 * basic statements.
 */
enum class statement : std::uint32_t {
    none   = 0,
    config = 1,
    print  = 2,
    assign = 3
};

/**
 * C@ only supports one expression and it is the math expression.
 */
enum class expression : std::uint32_t {
    none = 0,
    math = 1,
};

enum class token_t : std::uint32_t {
    none       = 0,
    statement  = 1,
    expression = 2,  // Different operators
};

constexpr auto token_t_str(token_t const& type) -> std::string {
    switch (type) {
        case token_t::statement:  return "statement";
        case token_t::expression: return "expression";
        default:
        case token_t::none:       return "none";
    }
}

/**
 * Token container, describe what type of token it is and what value it has.
 */
struct token {
    std::string value;
    token_t     type;

    auto str() const -> std::string {
        using namespace std::string_literals;
        std::string str{"token { "};
        str += "value: " + value + ", ";
        str += "type: "  + token_t_str(type);
        str += " }";
        return str;
    }
};

/**
 * Lexer or Tokenizer, here we use the two naming interchangeable. The purpose
 * of this is to generate tokenize for the parser to create an
 * AST(Abstract Syntax Tree).
 */
class lexer {
  public:
    lexer(std::string const& source) : m_source(source), m_cursor(0) {}
    ~lexer() = default;

    auto tokenize() -> std::vector<token> {
        std::vector<token> tokens{};
        return tokens;
    }

  private:
    auto next_token() -> std::optional<token> {
        if (!has_next()) return {};
        if (is_space()) ++m_cursor;
        if (!has_next()) return {};
        std::string res{};  // Eaten results

        // TODO: Handle strings source code
        return {};
    }

  private:
    auto is_space()   const -> bool { return m_source[m_cursor] == ' '; }
    auto is_newline() const -> bool { return m_source[m_cursor] == '\n'; }
    auto has_next()   const -> bool { return m_cursor < m_source.size(); }

  private:
    std::string m_source;
    std::size_t m_cursor;
    std::size_t m_line;
};

/**
 * Parser takes in the tokenize from the lexer/tokenizer to create an
 * AST(Abstract Syntax Tree).
 */
class parser {
  public:
  private:
};
}

[[maybe_unused]]constexpr auto test_source = R"(config dec
print 1 + 1
print 3 + 3 * 3
x = 2 - -2
y = x
z = y * (16 / (y - 2))
print x
print y
print z
config hex
print z
config bin
print z
)";

auto main([[maybe_unused]]std::int32_t argc, [[maybe_unused]]char const* argv[]) -> std::int32_t {
    std::cout << "Hello, cat!\n";
    cat::lexer lexer{test_source};
    auto tokens = lexer.tokenize();
    return 0;
}

