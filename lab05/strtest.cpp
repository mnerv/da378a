/**
 * @file   strtest.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @date   2022-10-05
 *
 * @copyright Copyright (c) 2022
 */
#include <cstdint>
#include <iostream>
#include <cassert>
#include <type_traits>
#include <stdexcept>
#include <string>

#include "gtest/gtest.h"
#include "string.hpp"

namespace nrv {
// https://notes.mnerv.dev/cpp.html#type-safe-length-of-c-array
template <typename T, std::size_t N>
constexpr auto length_of(T (&)[N]) -> std::size_t {
    return N;
}
}

// G

//// Don't know how to test this
//TEST(destructor, deallocate_memory) {
//    ASSERT_TRUE(false);
//}

TEST(constructor, default) {
    uni::string str;
    ASSERT_EQ(0, str.size());
}
TEST(constructor, c_string) {
    constexpr char hello[] = "Hello, World!";
    uni::string str{hello};
    // TODO: Check if string is equal
    ASSERT_EQ(nrv::length_of(hello), str.size());
}
TEST(constructor, copy_assignment_operator) {
    constexpr char hello[] = "Hello, World!";
    uni::string a{hello};
    uni::string b = a;
    a = "";
    ASSERT_NE(a.size(), b.size());
}

TEST(string_operation, index_no_range_check_lower) {
    constexpr char hello[] = "Hello, World!";
    uni::string a{hello};
    ASSERT_EQ(hello[0], a[0]);
}
TEST(string_operation, index_no_range_check_upper) {
    constexpr char hello[] = "Hello, World!";
    uni::string a{hello};
    ASSERT_EQ(hello[nrv::length_of(hello) - 1], a[nrv::length_of(hello) - 1]);
}
// TODO: Inside boundary test
TEST(string_operation, index_no_range_check_const) {
    constexpr char hello[] = "Hello, World!";
    uni::string const a{hello};
    auto const b = a[0];
    ASSERT_TRUE(std::is_const<decltype(b)>::value);
}

TEST(string_capacity, size) {
    constexpr char hello[] = "Hello, World!";
    uni::string str{hello};
    ASSERT_EQ(nrv::length_of(hello), str.size());
}
// TODO: Growth rate
TEST(string_capacity, capacity) {
    constexpr char hello[] = "Hello, World!";
    uni::string str{hello};
    ASSERT_EQ(nrv::length_of(hello), str.capacity());
}
TEST(string_operation, push_back) {
    constexpr char hello[] = "Hello, World!";
    uni::string str{hello};
    str.push_back('C');
    ASSERT_EQ(nrv::length_of(hello) + 1, str.size());
}

// TODO: Inside boundary test
TEST(string_operation, equal_equal) {
    constexpr char hello[] = "Hello";
    uni::string a{hello};
    uni::string b{hello};
    ASSERT_EQ(a, b);
}
TEST(string_operation, not_equal) {
    constexpr char hello1[] = "Hello";
    constexpr char hello2[] = "World";
    uni::string a{hello1};
    uni::string b{hello2};
    ASSERT_NE(a, b);
}

TEST(string_data, data) {
    constexpr char hello[] = "Hello";
    uni::string a{hello};
    ASSERT_NE(nullptr, a.data());
}

TEST(string_data, ostream_output) {
    constexpr char hello[] = "Hello, World!";
    uni::string a{hello};
    std::stringstream ss;
    ss << a;
    ASSERT_EQ(a.size(), ss.str().size());
}

// VG

TEST(string_at, bounds_lower_in) {
    constexpr char hello[] = "Hello, World!";
    uni::string a{hello};
    ASSERT_NO_THROW(a.at(0));
}
TEST(string_at, bounds_upper_in) {
    constexpr char hello[] = "Hello, World!";
    uni::string a{hello};
    ASSERT_NO_THROW(a.at(nrv::length_of(hello) - 1));
}
// No need to check lower bound outside because you can't pass negative value with std::size_t
TEST(string_at, bounds_upper_out) {
    constexpr char hello[] = "Hello, World!";
    uni::string a{hello};
    ASSERT_THROW(a.at(nrv::length_of(hello)), std::out_of_range);
}
TEST(string_at, bounds_lower_const_in) {
    constexpr char hello[] = "Hello, World!";
    uni::string a{hello};
    ASSERT_NO_THROW(a.at(0));
    auto const b = a.at(0);
    ASSERT_TRUE(std::is_const<decltype(b)>::value);
}
TEST(string_at, bounds_upper_const_in) {
    constexpr char hello[] = "Hello, World!";
    uni::string a{hello};
    ASSERT_NO_THROW(a.at(nrv::length_of(hello) - 1));
    auto const b = a.at(nrv::length_of(hello) - 1);
    ASSERT_TRUE(std::is_const<decltype(b)>::value);
}
// No need to check lower bound outside because you can't pass negative value with std::size_t
TEST(string_at, bounds_upper_const_out) {
    constexpr char hello[] = "Hello, World!";
    uni::string a{hello};
    ASSERT_THROW(a.at(nrv::length_of(hello)), std::out_of_range);
}

TEST(string_capacity, reserve) {
    uni::string str;
    constexpr std::size_t size = 128;
    str.reserve(size);
    ASSERT_EQ(size, str.size());
}
TEST(string_capacity, shrink) {
    constexpr std::size_t size = 128;
    uni::string str;
    str.reserve(size);
    str[0] = 'H';
    str.shrink_to_fit();
    ASSERT_EQ(1, str.capacity());
}

TEST(string_operation, plus_equal) {
    constexpr char hello[] = "Hello, World!";
    uni::string str;
    str += hello;
    ASSERT_EQ(nrv::length_of(hello), str.size());
}
TEST(string_operation, plus) {
    constexpr char hello[] = "Hello";
    constexpr char world[] = "World";
    uni::string a{hello};
    uni::string b{hello};
    uni::string str = a + b;
    ASSERT_EQ(nrv::length_of(hello) + nrv::length_of(world), str.size());
}

auto main([[maybe_unused]]std::int32_t argc, [[maybe_unused]]char const* argv[]) -> std::int32_t {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}

