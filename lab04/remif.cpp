/**
 * @file   remif.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Task 3 - Usage of std::remove_if
 * @date   2022-09-28
 *
 * @copyright Copyright (c) 2022
 */
#include <cstdint>
#include <iostream>
#include <vector>
#include <random>
#include <numeric>

/**
 * Prints with space separated values.
 *
 * @param begin Where to start iterate from.
 * @param end   Where to end, this will check it one iterator down to insert space.
 */
auto print_container(auto const& begin, auto const& end) -> void {
    for (auto it = begin; it != end; ++it) {
        std::cout << *it;
        if (it != end - 1) std::cout << " ";
        else std::cout << "\n";
    }
}

auto main([[maybe_unused]]std::int32_t argc, [[maybe_unused]]char const* argv[]) -> std::int32_t {
    std::size_t NUM_COUNT = 10;
    std::vector<std::int32_t> nums{};
    std::random_device rdev;  // Create random device for later usage
    std::mt19937 rng{rdev()};   // Pass in random device to generate the random number


    std::cout << "Generate numbers from 0 to " << NUM_COUNT << "\n";
    std::generate_n(std::back_inserter(nums), NUM_COUNT, [n = 0]() mutable { return n++; });
    print_container(std::begin(nums), std::end(nums));

    std::cout << "Shuffle numbers with random\n";
    std::shuffle(std::begin(nums), std::end(nums), rng);
    print_container(std::begin(nums), std::end(nums));

    std::cout << "Erase all numbers that's divisible by 2\n";
    nums.erase(std::remove_if(std::begin(nums), std::end(nums), [](auto const& n) { return n % 2 == 0; }),
               std::end(nums));

    print_container(std::begin(nums), std::end(nums));

    return 0;
}

