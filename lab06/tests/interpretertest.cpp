/**
 * @file   interpretertest.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Interpreter test suites for cat language library.
 * @date   2022-10-17
 *
 * @copyright Copyright (c) 2022
 */
#include <string>

#include "gtest/gtest.h"

TEST(interpreter, test) {
    ASSERT_TRUE(false);
}

auto main(int argc, char const* argv[]) -> int {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}
