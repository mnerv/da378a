/**
 * @file   asttest.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Google Test suites for cat language library.
 * @date   2022-10-17
 *
 * @copyright Copyright (c) 2022
 */
#include <string>

#include "gtest/gtest.h"

#include "parser.hpp"

TEST(parser, numeric_literal) {
    ASSERT_TRUE(false);
}

auto main(int argc, char const* argv[]) -> int {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}
