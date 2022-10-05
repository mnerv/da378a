/**
 * @file   string.hpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  string container class.
 * @date   2022-10-05
 *
 * @copyright Copright (c) 2022
 */

#include <cstddef>
#include <ostream>

namespace lab {
class string {
  public:
    string();
    string(string const& rhs);
    string(char const* cstr);
    ~string();

  public:
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
    auto operator+(string const& rhs)  -> string&;
};
}

