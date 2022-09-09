/**
 * @file   strmani.cpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  Task 02 - 03. String manipulation
 *
 *         02. Substitute string using std::string.
 *
 *         03. Substitute string using char* (C-style string manipulation)
 *
 * @date   2022-09-05
 *
 * @copyright Copyright (c) 2022
 */
#include <iostream>
#include <string>
#include <limits>

#include <cstring>

auto substitute_str(std::string& iostr, std::string const& before, std::string const& after) -> void {
    auto match = iostr.find(before);
    while (match != std::string::npos) {
        iostr.replace(match, before.size(), after);
        match = iostr.find(before);
    }
}

auto substitute_cstr(char const* input, char const* before, char const* after) -> char* {
    static constexpr auto NPOS = std::numeric_limits<std::size_t>::max();
    auto find_str = [](char const* str, char const* match) {
        std::size_t pos = NPOS;
        auto const str_len   = std::strlen(str);
        auto const match_len = std::strlen(match);
        for (std::size_t i = 0; i < str_len; ++i) {
            auto is_match = std::all_of(match, match + match_len, [&, j = std::size_t(0)](auto const& c) mutable {
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

    while (match != NPOS) {
        // Store the previous allocated string for later copy and cleanup
        auto tmp_str = str;
        auto tmp_len = str_len;

        // Allocate new memory for string output
        str_len = tmp_len - before_len + after_len;
        str     = new char[str_len + 1];

        // Memory copy to the new destination
        //   1. Copy first part before match
        //   2. Copy after string to the new location
        //   3. Copy rest of the previous string data include null termination.
        std::memcpy(str, tmp_str, match);
        std::memcpy(str + match, after, after_len);
        std::memcpy(str + match + after_len, tmp_str + match + before_len, tmp_len - match - before_len + 1);

        match = find_str(str, before);
        delete[] tmp_str;
    }

    return str;
}


auto main([[maybe_unused]]int argc, [[maybe_unused]]char const* argv[]) -> int {
    auto str = substitute_cstr("Hello, World!", "World", "Charlie");
    std::cout << str << "\n";
    delete[] str;

    str = substitute_cstr("Hello, World!", ", World!", ".");
    std::cout << str << "\n";
    delete[] str;
    return 0;
}

