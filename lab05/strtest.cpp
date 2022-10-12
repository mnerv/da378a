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

#include "gtest/gtest.h"
#include "string.hpp"

// G

TEST(destructor, deallocate_memory) {
    ASSERT_TRUE(false);
}

TEST(constructor, default) {
    ASSERT_TRUE(false);
}
TEST(constructor, c_string) {
    ASSERT_TRUE(false);
}
TEST(constructor, copy_assignment_operator) {
    ASSERT_TRUE(false);
}

TEST(string_operation, index_no_range_check) {
    ASSERT_TRUE(false);
}
TEST(string_operation, index_no_range_check_const) {
    ASSERT_TRUE(false);
}

TEST(string_capacity, size) {
    ASSERT_TRUE(false);
}
TEST(string_capacity, capacity) {
    ASSERT_TRUE(false);
}
TEST(string_operation, push_back) {
    ASSERT_TRUE(false);
}

TEST(string_operation, equal_equal) {
    ASSERT_TRUE(false);
}
TEST(string_operation, not_equal) {
    ASSERT_TRUE(false);
}

TEST(string_data, data) {
    ASSERT_TRUE(false);
}

TEST(string_data, ostream_output) {
    ASSERT_TRUE(false);
}

// VG

TEST(string_at, bounds) {
    ASSERT_TRUE(false);
}
TEST(string_at, bounds_const) {
    ASSERT_TRUE(false);
}

TEST(string_capacity, reserve) {
    ASSERT_TRUE(false);
}
TEST(string_capacity, shrink) {
    ASSERT_TRUE(false);
}

TEST(string_operation, plus_equal) {
    ASSERT_TRUE(false);
}
TEST(string_operation, plus) {
    ASSERT_TRUE(false);
}

auto main([[maybe_unused]]std::int32_t argc, [[maybe_unused]]char const* argv[]) -> std::int32_t {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}

