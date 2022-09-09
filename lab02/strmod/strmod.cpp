/**
 * @file   strmani.cpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  Task 02 - 04. String manipulation
 *
 *         02. Substitude string using std::string.
 *
 *         03. Substitude string using char* (C-style string manipulation)
 *
 * @date   2022-09-05
 *
 * @copyright Copyright (c) 2022
 */
#include <iostream>
#include <string>

#include <cstring>

auto substitude_str(std::string& iostr, std::string const& before, std::string const& after) -> void {
    auto match = iostr.find(before);
    while (match != std::string::npos) {
        iostr.replace(match, before.size(), after);
        match = iostr.find(before);
    }
}

constexpr auto operator "" _z(unsigned long long n) -> std::size_t { return n; }

auto substitude_cstr(char const* input, char const* before, char const* after) -> char* {
    auto find_str = [](char const* str, char const* match) {
        std::size_t pos = SIZE_T_MAX;
        auto const str_len   = std::strlen(str);
        auto const match_len = std::strlen(match);
        for (std::size_t i = 0; i < str_len; ++i) {
            auto is_match = std::all_of(match, match + match_len, [&, j = 0_z](auto const& c) mutable {
                return i + j < str_len && str[i + (j++)] == c;
            });
            if (is_match) {
                pos = i;
                break;
            }
        }
        return pos;
    };
    // Find the first
    auto str_len = std::strlen(input);
    auto str     = new char[str_len + 1];
    std::memcpy(str, input, str_len + 1);
    auto match   = find_str(str, before);

    auto const before_len = std::strlen(before);
    auto const after_len  = std::strlen(after);

    while (match != SIZE_T_MAX) {
        // Store the previous allocated string for later copy and cleanup
        auto tmp_str = str;
        auto tmp_len = str_len;

        // Allocate new memory for string output
        str_len = tmp_len - before_len + after_len;
        str     = new char[str_len + 1];

        // Memory copy to the new destination
        //   1. Copy first part before match
        //   2. Copy after string to the new location
        //   3. Copy rest of the previous string data.
        std::memcpy(str, tmp_str, match);
        std::memcpy(str + match, after, after_len);
        std::memcpy(str + match + after_len, tmp_str + match + before_len, tmp_len - match - before_len + 1);

        match = find_str(str, before);
        delete[] tmp_str;
    }

    return str;
}


auto main([[maybe_unused]]int argc, [[maybe_unused]]char const* argv[]) -> int {
    std::string text = "Hello, World!, World, Hej, Wor";
    std::string out = text;
    substitude_str(out, "Wor", "");
    std::cout << "Task02: ";
    std::cout << out << "\n";

    auto str = substitude_cstr(text.c_str(), "World", "");
    std::cout << "Task03: ";
    std::cout << str << "\n";
    delete[] str;

    return 0;
}

