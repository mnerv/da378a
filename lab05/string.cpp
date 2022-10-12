/**
 * @file string.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @date   2022-10-05
 *
 * @copyright Copyright (c) 2022
 */
#include "string.hpp"
#include <cassert>
#include <algorithm>

namespace uni {
string::string() : m_size(0), m_capacity(8), m_data(new char[m_capacity]) {}
string::string(string const& rhs) : m_size(rhs.m_size), m_capacity(rhs.m_capacity), m_data(new char[m_capacity]) {
    std::memset(m_data, 0, m_capacity);
    std::memcpy(m_data, rhs.m_data, m_size);
}
string::string(char const* cstr) {
    m_size     = std::strlen(cstr);
    m_capacity = m_size;
    m_data     = new char[m_capacity];
    std::memset(m_data, 0, m_capacity);
    std::memcpy(m_data, cstr, m_size);
}
string::~string() {
    delete[] m_data;
}

auto string::operator=([[maybe_unused]]string const& rhs) -> string& {
    return *this;
}
auto string::operator[]([[maybe_unused]]std::size_t i) -> char& {
    assert(false);
}
auto string::operator[]([[maybe_unused]]std::size_t i) const -> char const& {
    assert(false);
}
auto string::size() const -> std::size_t {
    return m_size;
}
auto string::capacity() const -> std::size_t {
    return m_capacity;
}

auto string::push_back([[maybe_unused]]char c) -> void {
    assert(false);
}

auto operator==([[maybe_unused]]string const& lhs, [[maybe_unused]]string const& rhs) -> bool {
    assert(false);
}
auto operator!=([[maybe_unused]]string const& lhs, [[maybe_unused]]string const& rhs) -> bool {
    assert(false);
}

auto string::data() const -> char const* {
    return nullptr;
}

auto operator<<(std::ostream& out, string const& rhs) -> std::ostream& {
    std::for_each(rhs.m_data, rhs.m_data + rhs.m_size,
                  [&out](auto const& c) { out.put(c); });
    return out;
}

auto string::at([[maybe_unused]]std::size_t i) -> char& {
    assert(false);
}
auto string::at([[maybe_unused]]std::size_t i) const -> char const& {
    assert(false);
}
auto string::reserve(std::size_t new_capacity) -> void {
    m_capacity = new_capacity;
    assert(false);
}
auto string::shrink_to_fit() -> void {
    assert(false);
}

auto string::operator+=([[maybe_unused]]string const& rhs) -> string& {
    assert(false);
}
auto string::operator+([[maybe_unused]]string const& rhs)  -> string& {
    assert(false);
}
}

