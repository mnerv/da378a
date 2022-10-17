/**
 * @file   catc.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  catc is a mini project interpreter for the C@ (cat) language.
 *         This program compiles and interpret the C@ code.
 *
 *         Functionality requirements:
 *           - Read code from a source file
 *           - Parse and execute according to the C@ grammar. Add your own code
 *             (or code suggested by a teacher)
 *           - Output sends to the std::ostream, such as std::cout (standard out)
 *           - Terminals defined by regular expressions (int and variable)
 *             should be matched properly to the provided pattern. int-tokens
 *             should be matched before being ast to C++ integers.
 * @date   2022-09-15
 *
 * @copyright Copyright (c) 2022
 */
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <ios>

#include "lexer.hpp"
#include "parser.hpp"

namespace nrv {
auto read_text(std::string const& filename) -> std::string {
    std::ifstream input{filename, std::ios::in};
    if (!input.is_open() || input.fail())
        throw std::runtime_error("ERROR: Loading textfile!");
    return {
        std::istreambuf_iterator<char>(input),
        std::istreambuf_iterator<char>()
    };
}
}

auto main([[maybe_unused]]int argc, [[maybe_unused]]char const* argv[]) -> int {
    if (argc < 2) {
        std::cout << "No input file\n";
        std::cout << "usage: " << argv[0] << " {source_file}\n";
        std::cout << "    {source_file} - cat language source code\n";
        return 1;
    }

    std::filesystem::path source_file{argv[1]};
    if (!std::filesystem::exists(source_file)) {
        std::cerr << "File does not exist!\n";
        return 1;
    }

    auto const source = nrv::read_text(source_file.string());
    cat::lexer lexer{source};
    auto tokens = lexer.tokenize();
    cat::parser parse(tokens);
    return 0;
}

