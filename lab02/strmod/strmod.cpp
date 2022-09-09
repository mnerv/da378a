/**
 * @file   strmani.cpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  Task 02 - 04. String manipulation
 *
 *         02. Substitude string using std::string.
 *
 * @date   2022-09-05
 *
 * @copyright Copyright (c) 2022
 */
#include <iostream>
#include <string>

auto substitude_str(std::string& iostr, std::string const& before, std::string const& after) -> void {
    auto match = iostr.find(before);
    while (match != std::string::npos) {
        iostr.replace(match, before.size(), after);
        match = iostr.find(before);
    }
}

auto main([[maybe_unused]]int argc, [[maybe_unused]]char const* argv[]) -> int {
    std::string text = "Hello, World!, World, Hej, Wor";
    substitude_str(text, "Wor", "");
    std::cout << text << "\n";

    return 0;
}

