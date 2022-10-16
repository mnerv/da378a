/**
 * @file   hello.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Google Test suites for cat language library.
 * @date   2022-10-17
 *
 * @copyright Copyright (c) 2022
 */
#include "gtest/gtest.h"

#include "token.hpp"

[[maybe_unused]]constexpr auto test_source = R"(config dec
print 1 + 1
print 3 + 3 * 3
print ( 3 + 3 ) * 3
x = 2 - -2
y = x
z = y * ( 16 / ( y - 2 ) )
print x
print y
print z
config hex
print z
config bin
print z
)";

[[maybe_unused]]constexpr auto out_source = R"(2
12
18
4
4
32
0x20
0000000000100000
)";

TEST(MUCH, TEST) {
    ASSERT_TRUE(false);
}

auto main([[maybe_unused]]int argc, [[maybe_unused]]char const* argv[]) -> int {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}
