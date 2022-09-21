/**
 * @file   sortint.cpp
 * @author Pratchaya Khansomboon <me@mononerv.dev>
 * @brief  Task 1 - Sort integers with STL algorithm
 *
 *         a. Generate random numbers into std::vector and sort it with std::sort.
 *            Print out the results between the steps.
 *
 *         b. Random numbers and sort with C style array
 *
 *         c. Reverse sort the numbers with std::vector
 *
 *         d. Reverse sort the numbers with C style array
 * @date   2022-09-18
 *
 * @copyright Copyright (c) 2022
 */
#include <iostream>
#include <cstdint>
#include <random>
#include <vector>
#include <algorithm>

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
    std::random_device rdev;  // Create random device for later usage
    std::mt19937 rng{0};      // Pass in random device to generate the random number
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 255);
    constexpr std::size_t MAX_NUM = 32;

    // Task 01.a - Sort integers with std::vector
    std::vector<std::int32_t> nums{};
    std::generate_n(std::back_inserter(nums), MAX_NUM, [&] { return dist(rng); });

    std::cout << "Random integer numbers (std::vector)\n";
    print_container(std::begin(nums), std::end(nums));
    std::cout << "\n";

    std::cout << "Sorted integer numbers (std::vector)\n";
    std::sort(std::begin(nums), std::end(nums));
    print_container(std::begin(nums), std::end(nums));
    std::cout << "\n\n";

    // Task 01.b - Sort integers with C style array
    std::int32_t c_nums[MAX_NUM]{0};
    std::generate_n(c_nums, MAX_NUM, [&] { return dist(rng); });

    std::cout << "Random integer numbers (C style array)\n";
    print_container(c_nums, c_nums + MAX_NUM);
    std::cout << "\n";

    std::cout << "Sorted integer numbers (C style array)\n";
    std::sort(c_nums, c_nums + MAX_NUM);
    print_container(c_nums, c_nums + MAX_NUM);
    std::cout << "\n\n";

    // Task 01.c - Sort integers in reverse order (std::vector)
    std::vector<std::int32_t> rnums{};
    std::generate_n(std::back_inserter(rnums), MAX_NUM, [&] { return dist(rng); });

    std::cout << "Random integer numbers reverse (std::vector)\n";
    print_container(std::begin(rnums), std::end(rnums));
    std::cout << "\n";

    std::cout << "Sorted integer numbers reverse (std::vector)\n";
    std::sort(std::rbegin(rnums), std::rend(rnums));
    print_container(std::begin(rnums), std::end(rnums));
    std::cout << "\n\n";

    // Task 01.d - Sort integers reverse with C style array
    std::int32_t c_rnums[MAX_NUM]{0};
    std::generate_n(c_rnums, MAX_NUM, [&] { return dist(rng); });

    std::cout << "Random integer numbers reverse (C style array)\n";
    print_container(c_rnums, c_rnums + MAX_NUM);
    std::cout << "\n";

    std::cout << "Sorted integer numbers reverse (C style array)\n";
    std::sort(c_rnums, c_rnums + MAX_NUM, [](auto const& a, auto const& b) { return a > b; });
    print_container(c_rnums, c_rnums + MAX_NUM);
    std::cout << "\n";

    return 0;
}

