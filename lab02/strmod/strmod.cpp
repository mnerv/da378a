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
#include <algorithm>

#include <cstring>

/**
 * Simple find and replace all using std::string find and replace api.
 *
 * @iostr  The input string and also the output.
 * @before Match string to find.
 * @after  Replacement string.
 */
auto substitute_str(std::string& iostr, std::string const& before, std::string const& after) -> void {
    auto match = iostr.find(before);
    while (match != std::string::npos) {
        iostr.replace(match, before.size(), after);
        match = iostr.find(before);
    }
}

/**
 * A naive find and replace all using C style string with null termination.
 * This solution behaves like the substitute_str std::string version but
 * manually mangaging the menory. The return string of this needs to be later
 * free with delete[]. The replacing parts will delete the old string and
 * allocate new memory space everytime there's a match. This might be a problem
 * if it is a requirement that there should be as little memory allocation as
 * possible.
 *
 * @input  String we should search in.
 * @before Matching string.
 * @after  Replacement string.
 *
 * @return C style string with null termination, NEEDS TO BE FREE!
 */
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
    using namespace std::string_literals;
    auto str1    = "Hello, World and World!"s;
    auto before1 = "World"s;
    auto after1  = "Charlie"s;
    std::cout << "Task 02.\n";
    std::cout << "Text: \"" << str1 << "\"\n";
    std::cout << "Before: \"" << before1 << "\", After: \"" << after1 << "\"\n";
    substitute_str(str1, before1, after1);
    std::cout << "Out: \"" << str1 << "\"\n\n";

    auto str2 = "Hello, World, World, World!";
    auto before2 = "World";
    auto after2  = "KOMIGEN!";
    std::cout << "Task 03.\n";
    std::cout << "Text: \"" << str2 << "\"\n";
    std::cout << "Before: \"" << before2 << "\", After: \"" << after2 << "\"\n";
    auto task2_out = substitute_cstr(str2, before2, after2);
    std::cout << "Out: \"" << task2_out << "\"\n";
    delete[] task2_out;
    return 0;
}

