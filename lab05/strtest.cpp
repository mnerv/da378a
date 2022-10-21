/**
 * @file   strtest.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Google Test suites for custom string implementation.
 * @date   2022-10-05
 *
 * @copyright Copyright (c) 2022
 */
#include <type_traits>
#include <stdexcept>
#include <string>

#include "gtest/gtest.h"
#include "string.hpp"

namespace nrv {
// https://notes.mnerv.dev/cpp.html#type-safe-length-of-c-array
// If you're using with char const[] then know that it will include the null
// termination in the size.
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

TEST(constructor, trivial_default) {
    uni::string str;
    ASSERT_EQ(0, str.size());
}
TEST(constructor, c_string) {
    constexpr char hello[] = "Hello, World!";
    uni::string str(hello);
    // TODO: Check if string is equal
    ASSERT_EQ(nrv::length_of(hello) - 1, str.size());
}
TEST(constructor, copy_assignment_operator) {
    constexpr char hello[] = "Hello, World!";
    uni::string a(hello);
    uni::string b = a;
    a = "";
    ASSERT_NE(a.size(), b.size());
}
// Lower out, One size smaller string
// This should test that there are no reallocation when assignment smaller string.
TEST(constructor, copy_assignment_operator_bounds_lower_out) {
    constexpr char texta[] = "Hello, World!";
    constexpr char textb[] = "Hello, World";
    uni::string a(texta);
    uni::string b(textb);
    auto ptr = a.data();
    a = b;
    ASSERT_EQ(ptr, a.data());
    ASSERT_EQ(nrv::length_of(textb) - 1, a.size());
}
// Upper in,  Same string
// Should be the same as the lower bound out when assigning same size string there should be no reallocation.
TEST(constructor, copy_assignment_operator_bounds_upper_in) {
    constexpr char text[] = "Hello, World!";
    uni::string a(text);
    uni::string b(text);
    auto ptr = a.data();
    a = b;
    ASSERT_EQ(ptr, a.data());
    ASSERT_EQ(nrv::length_of(text) - 1, a.size());
}
// Upper out, One size bigger string
// Should test for reallocation when assigning larger string.
TEST(constructor, copy_assignment_operator_bounds_out) {
    constexpr char texta[]     = "Hello, World!";
    constexpr std::size_t size = 64;
    static char textb[size]{0};
    for (std::size_t i = 0; i < size - 1; ++i)
        textb[i] = static_cast<char>(65 + (i % 25));
    uni::string a(texta);
    uni::string b(textb);
    auto const ptr = a.data();
    a = b;
    ASSERT_NE(ptr, a.data());
    ASSERT_EQ(nrv::length_of(textb) - 1, a.size());
}

TEST(string_operation, index_no_range_check_lower_in) {
    constexpr char hello[] = "Hello, World!";
    uni::string a{hello};
    ASSERT_EQ(hello[0], a[0]);
}
TEST(string_operation, index_no_range_check_upper_in) {
    constexpr char hello[] = "Hello, World!";
    uni::string a{hello};
    ASSERT_EQ(hello[nrv::length_of(hello) - 1], a[nrv::length_of(hello) - 1]);
}
TEST(string_operation, index_no_range_check_const_lower_in) {
    constexpr char hello[] = "Hello, World!";
    uni::string const a{hello};
    static_assert(std::is_const<decltype(a)>::value, "not const here");
    auto& b = a[0];
    ASSERT_TRUE((std::is_same<decltype(b), char const&>::value));
}
TEST(string_operation, index_no_range_check_const_upper_in) {
    constexpr char hello[] = "Hello, World!";
    uni::string const a{hello};
    static_assert(std::is_const<decltype(a)>::value, "not const here");
    auto& b = a[nrv::length_of(hello) - 1];
    ASSERT_TRUE((std::is_same<decltype(b), char const&>::value));
}

TEST(string_capacity, size) {
    constexpr char hello[] = "Hello, World!";
    uni::string str{hello};
    ASSERT_EQ(nrv::length_of(hello) - 1, str.size());
}
// TODO: Growth rate
TEST(string_capacity, capacity) {
    constexpr char hello[] = "Hello, World!";
    uni::string str{hello};
    ASSERT_EQ(nrv::length_of(hello), str.capacity());
}

TEST(string_operation, push_back) {
    constexpr char hello[] = "Hello, World!";
    constexpr auto size    = nrv::length_of(hello);
    uni::string str;
    for (std::size_t i = 0; i < size; ++i) str.push_back(hello[i]);
    ASSERT_EQ(size, str.size());
    ASSERT_STREQ(hello, str.data());
}
TEST(string_operation, equal_equal) {
    constexpr char hello[] = "Hello";
    uni::string a{hello};
    uni::string b{hello};
    ASSERT_EQ(a, b);
}
TEST(string_operation, equal_equal_diff_size) {
    constexpr char texta[] = "Hello";
    constexpr char textb[] = "World!";
    uni::string a{texta};
    uni::string b{textb};
    ASSERT_NE(a, b);
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
    ASSERT_NO_THROW(a.at(nrv::length_of(hello) - 2));
}
// No need to check lower bound outside because you can't pass negative value with std::size_t
TEST(string_at, bounds_upper_out) {
    constexpr char hello[] = "Hello, World!";
    uni::string a{hello};
    ASSERT_THROW(a.at(nrv::length_of(hello) - 1), std::out_of_range);
}
TEST(string_at, bounds_lower_const_in) {
    constexpr char hello[] = "Hello, World!";
    uni::string const a{hello};
    static_assert(std::is_const<decltype(a)>::value, "not const here");
    ASSERT_NO_THROW(a.at(0));
    auto& b = a.at(0);
    //static_assert(std::is_const<std::remove_reference<decltype(b)>::type>::value, "Not const");
    ASSERT_TRUE((std::is_same<decltype(b), char const&>::value));
}
TEST(string_at, bounds_upper_const_in) {
    constexpr char hello[] = "Hello, World!";
    uni::string const a{hello};
    static_assert(std::is_const<decltype(a)>::value, "not const here");
    ASSERT_NO_THROW(a.at(nrv::length_of(hello) - 2));
    auto& b = a.at(nrv::length_of(hello) - 2);
    ASSERT_TRUE((std::is_same<decltype(b), char const&>::value));
}
// No need to check lower bound outside because you can't pass negative value with std::size_t
TEST(string_at, bounds_upper_const_out) {
    constexpr char hello[] = "Hello, World!";
    uni::string const a{hello};
    static_assert(std::is_const<decltype(a)>::value, "not const here");
    ASSERT_THROW(a.at(nrv::length_of(hello) - 1), std::out_of_range);
}

TEST(string_capacity, reserve_size) {
    uni::string str;
    constexpr std::size_t size = 128;
    str.reserve(size);
    ASSERT_EQ(size, str.capacity());
}
TEST(string_capacity, reserve_data) {
    constexpr char hello[] = "Hello, World!";
    uni::string str;
    constexpr std::size_t size = 128;
    str.reserve(size);
    auto ptr = str.data();
    str = hello;
    ASSERT_EQ(ptr, str.data());
}
// TODO: Fix boundary tests for reserve
//TEST(string_capacity, reserve_boundary_upper_out) {
//    constexpr char hello[]     = "Hello, World!";
//    constexpr std::size_t size = nrv::length_of(hello);
//    uni::string str(hello);
//    str.reserve(size - 9);
//    auto ptr = str.data();
//    ASSERT_EQ(hello[0], ptr[0]);
//}
//TEST(string_capacity, reserve_boundary_lower_in) {
//    constexpr char hello[]     = "Hello, World!";
//    constexpr std::size_t size = nrv::length_of(hello);
//    uni::string str(hello);
//    str.reserve(size);
//    auto ptr = str.data();
//    ASSERT_EQ(hello[0], ptr[0]);
//}
TEST(string_capacity, shrink) {
    constexpr char hello[] = "Hello, World! From a afar";
    constexpr std::size_t size = 128;
    uni::string str;
    str.reserve(size);
    str = hello;
    str.shrink_to_fit();
    ASSERT_NE(size, str.capacity());
    ASSERT_EQ(nrv::length_of(hello) - 1, str.capacity());
}
TEST(string_capacity, shrink_bounds_upper_in) {
    constexpr char hello[] = "Hello, World!";
    constexpr std::size_t size = nrv::length_of(hello);
    uni::string str(hello);
    str.reserve(size);
    str = hello;
    str.shrink_to_fit();
    ASSERT_NE(size, str.capacity());
}

TEST(string_operation, plus_equal) {
    constexpr char hello[] = "Hello, World!";
    uni::string str;
    str += hello;
    ASSERT_EQ(nrv::length_of(hello) - 1, str.size());
    ASSERT_EQ(hello, str);
}
TEST(string_operation, plus) {
    constexpr char hello[] = "Hello";
    constexpr char world[] = "World";
    uni::string a{hello};
    uni::string b{hello};
    uni::string str = a + b;
    ASSERT_EQ((nrv::length_of(hello) - 1), a.size());
    ASSERT_EQ((nrv::length_of(hello) - 1) + (nrv::length_of(world) - 1), str.size());
}

TEST(string_operation, push_back_million) {
    constexpr std::size_t SIZE = 100'000;
    uni::string a{};
    for (std::size_t i = 0; i < SIZE; ++i) {
        a.push_back('a');
    }
    ASSERT_LE(a.capacity(), 1'000'000);
}

auto main([[maybe_unused]]std::int32_t argc, [[maybe_unused]]char const* argv[]) -> std::int32_t {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}

