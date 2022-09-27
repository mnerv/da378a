/**
 * @file   sortperson.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Task 2 - Sort Person from Lab03
 * @date   2022-09-21
 *
 * @copyright Copyright (c) 2022
 */
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <random>

#include "PersonReg/PersonReg.hpp"

auto main([[maybe_unused]]std::int32_t argc, [[maybe_unused]]char const* argv[]) -> std::int32_t {
    PersonReg reg{5};
    reg.LaggTillTest("Eric", "100");
    reg.LaggTillTest("Charlie", "200");
    reg.LaggTillTest("Linnéa", "300");
    reg.LaggTillTest("Felix", "400");
    reg.LaggTillTest("Yosef", "500");

    std::random_device rd{};
    std::mt19937 rng{rd()};
    std::shuffle(reg.begin(), reg.end(), rng);

    // Task 2.a
    std::cout << "Shuffled persons\n";
    reg.Print();
    std::cout << "\n";

    std::cout << "Sorted persons\n";
    std::sort(std::begin(reg), std::end(reg));
    reg.Print();
    std::cout << "\n";

    // Task 2.b
    std::shuffle(reg.begin(), reg.end(), rng);

    return 0;
}

