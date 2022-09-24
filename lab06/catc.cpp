/**
 * @file   catc.cpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  catc is a mini project interpreter for the C@ (cat) language.
 *         This program compiles and interpret the C@ code.
 * @date   2022-09-14
 *
 * @copyright Copyright (c) 2022
 */
#include <cstdint>
#include <iostream>
#include <string_view>
#include <array>

namespace cat {

using namespace std::string_view_literals;
[[maybe_unused]]constexpr std::array keywords = {
    "config"sv,
    "print"sv,
};

enum class statement : std::uint32_t {
    none   = 0,
    config = 1,
    print  = 2,
    assign = 3
};
}

auto main([[maybe_unused]]std::int32_t argc, [[maybe_unused]]char const* argv[]) -> std::int32_t {
    std::cout << "Hello, cat!\n";
    return 0;
}

