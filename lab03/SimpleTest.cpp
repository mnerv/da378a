/**
 * @file   PersonRegTest.cpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  Test program for person and person_reg.
 * @date   2022-09-14
 *
 * @copyright Copyright (c) 2022
 */
#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>

#include "PersonReg.hpp"

auto read_register(PersonReg& reg, std::string filename) -> bool {
    std::string line;
    std::ifstream file{filename};
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << "\n";
        return false;
    }

    while(std::getline(file, line)) {
        while(line.length() == 0 && std::getline(file, line));
        std::string name{line};
        std::string adress;
        std::getline(file, adress);
        Person p{name, adress};
        auto complete = reg.LaggTill(&p);
        if (!complete) return true;
    }

    return true;
}

auto main([[maybe_unused]]std::int32_t argc, [[maybe_unused]]char const* argv[]) -> std::int32_t {
    PersonReg reg{10};
    read_register(reg, "/Users/k/Downloads/personer.txt");
    reg.Print();
    return 0;
}

