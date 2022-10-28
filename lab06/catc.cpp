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
#include <string>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>

#include "lexer.hpp"
#include "parser.hpp"
#include "interpreter.hpp"

namespace nrv {
/**
 * Simple read textfile.
 *
 * @link   http://notes.mnerv.dev/cpp.html#read-text-into-stdstring
 * @param  filename Path to text file.
 * @return Text content.
 */
static auto read_text(std::string const& filename) -> std::string {
    std::ifstream input{filename, std::ios::in};
    if (!input.is_open() || input.fail())
        throw std::runtime_error("ERROR: Loading textfile!");
    return {
        std::istreambuf_iterator<char>(input),
        std::istreambuf_iterator<char>()
    };
}
}

auto main(int argc, char const* argv[]) -> int {
    if (argc < 2) {
        std::cout << "catc: error: no input file!\n";
        return 1;
    }

    std::filesystem::path source_file{argv[1]};
    if (!std::filesystem::exists(source_file)) {
        std::cerr << "catc: error: file does not exist!\n";
        return 1;
    }

    [[maybe_unused]]auto const source = nrv::read_text(source_file.string());
    cat::lexer lexer{source, source_file.string()};
    //cat::lexer lexer{"((3+3)/2)*3"};
    auto const tokens = lexer.tokenize();
    cat::parser parser{tokens};
    cat::interpreter interpreter(std::cout);
    parser.parse();
    for (auto const& token : tokens) {
        std::cout << token.str() << "\n";
    }
    auto program = parser.program();
    for (auto const& node : program) {
        cat::recursive_print(std::cout, node);
//        if (!interpreter.eval(node)) {
//            std::cout << "Error!\n";
//        }
    }

    return 0;
}

