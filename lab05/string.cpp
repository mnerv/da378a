/**
 * @file string.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @date   2022-10-05
 *
 * @copyright Copyright (c) 2022
 */
#include "string.hpp"
#include <algorithm>
#include <numeric>
#include <stdexcept>

#include <cstring>
#include <iostream>

// std::string memory allocation on different compilers libc++
// https://shaharmike.com/cpp/std-string/

namespace uni {

static constexpr std::size_t STR_START_CAPACITY = 0;
static constexpr std::size_t GROW_RATE          = 2;

string::string() : m_size(0), m_capacity(STR_START_CAPACITY), m_data(new char[m_capacity]) {}
string::string(string const& rhs) : m_size(rhs.m_size), m_capacity(rhs.m_capacity), m_data(new char[m_capacity]) {
    std::memset(m_data, 0, m_capacity);
    std::memcpy(m_data, rhs.m_data, m_size);
}
string::string(char const* cstr) {
    m_size     = std::strlen(cstr);
    m_capacity = m_size + 1;  // allocate extra space for null termination
    m_data     = new char[m_capacity];
    std::memset(m_data, 0, m_capacity);
    std::memcpy(m_data, cstr, m_size);
}
string::~string() { delete[] m_data; }

auto string::operator=(string const& rhs) -> string& {
    m_size = rhs.m_size;
    if (m_capacity < rhs.m_capacity) {
        m_capacity = rhs.m_capacity;
        delete [] m_data;
        m_data = new char[m_capacity];
        std::memset(m_data, 0, m_capacity);
        std::memcpy(m_data, rhs.m_data, m_size);
    } else {
        std::memcpy(m_data, rhs.m_data, m_size);
    }
    return *this;
}
auto string::operator[](std::size_t i) -> char& {
    return m_data[i];
}
auto string::operator[](std::size_t i) const -> char const& {
    return m_data[i];
}
auto string::size() const -> std::size_t {
    return m_size;
}
auto string::capacity() const -> std::size_t {
    return m_capacity;
}

auto string::push_back(char c) -> void {
    auto const old_size = m_size++;
    if (m_size > m_capacity) {
        m_capacity = GROW_RATE * m_size;
        auto tmp = m_data;
        m_data = new char[m_capacity];
        std::memset(m_data, 0, m_capacity);
        std::memcpy(m_data, tmp, old_size);
        m_data[old_size] = c;
        delete[] tmp;
    } else {
        m_data[old_size] = c;
    }
}

auto operator==(string const& lhs, string const& rhs) -> bool {
    if (lhs.m_size != rhs.m_size) return false;
    return std::all_of(lhs.m_data, lhs.m_data + lhs.m_size, [it = rhs.m_data](auto const& c) mutable {
        return c == *(it++);
    });
}
auto operator!=(string const& lhs, string const& rhs) -> bool {
    return !(lhs == rhs);
}

auto string::data() const -> char const* {
    return m_data;
}

auto operator<<(std::ostream& out, string const& rhs) -> std::ostream& {
    std::for_each(rhs.m_data, rhs.m_data + rhs.m_size, [&out](auto const& c) { out.put(c); });
    return out;
}

auto string::at(std::size_t i) -> char& {
    if (i >= m_size) throw std::out_of_range("uni::string index out of range");
    return m_data[i];
}
auto string::at(std::size_t i) const -> char const& {
    if (i >= m_size) throw std::out_of_range("uni::string index out of range");
    return m_data[i];
}
auto string::reserve(std::size_t new_capacity) -> void {
    if (new_capacity <= m_capacity) return;
    auto tmp = m_data;
    m_data = new char[new_capacity];
    std::memset(m_data, 0, new_capacity);
    std::memcpy(m_data, tmp, m_capacity);
    m_capacity = new_capacity;
    delete[] tmp;
}
auto string::shrink_to_fit() -> void {
    if (m_size == m_capacity) return;
    auto tmp   = m_data;
    m_capacity = m_size;
    m_data     = new char[m_capacity];
    std::memcpy(m_data, tmp, m_capacity);
    delete[] tmp;
}

auto string::operator+=(string const& rhs) -> string& {
    auto const new_size     = m_size + rhs.m_size;
    auto const new_capacity = new_size + 1;
    auto tmp = m_data;
    m_data = new char[new_capacity];
    std::memset(m_data, 0, new_capacity);
    std::memcpy(m_data, tmp, m_size);
    std::memcpy(m_data + m_size, rhs.m_data, rhs.m_size);
    delete[] tmp;
    m_size     = new_size;
    m_capacity = new_capacity;
    return *this;
}
auto string::operator+(string const& rhs) -> string {
    string str = *this;
    str += rhs;
    return str;
}
}

