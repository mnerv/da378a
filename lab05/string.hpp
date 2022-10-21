/**
 * @file   string.hpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  string container class.
 *
 *         For our string class we applies the rule of three.
 *           - Destructor
 *           - Copy constructor
 *           - Copy assignment operator
 *         https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)
 * @date   2022-10-05
 *
 * @copyright Copright (c) 2022
 */

#ifndef UNI_STRING_HPP
#define UNI_STRING_HPP

#include <cstddef>
#include <ostream>

namespace uni {
/**
 * Custom string implementation with value-semantic. This container tries to
 * imitate the std::string with strip down features.
 */
class string {
  public:
    string();
    string(string const& rhs);
    string(char const* cstr);
    ~string();

  public:
    auto operator=(string const& rhs) -> string&;
    auto operator[](std::size_t i) -> char&;
    auto operator[](std::size_t i) const -> char const&;
    auto size()     const -> std::size_t;
    auto capacity() const -> std::size_t;

    auto push_back(char c) -> void;

    friend auto operator==(string const& lhs, string const& rhs) -> bool;
    friend auto operator!=(string const& lhs, string const& rhs) -> bool;

    auto data() const -> char const*;

    friend auto operator<<(std::ostream& out, string const& rhs) -> std::ostream&;

  public:
    auto at(std::size_t i) -> char&;
    auto at(std::size_t i) const -> char const&;
    auto reserve(std::size_t new_capacity) -> void;
    auto shrink_to_fit() -> void;

    auto operator+=(string const& rhs) -> string&;
    auto operator+(string const& rhs)  -> string;

  private:
    std::size_t m_size;
    std::size_t m_capacity;
    char*       m_data;
};
}

#endif  // UNI_STRING_HPP
