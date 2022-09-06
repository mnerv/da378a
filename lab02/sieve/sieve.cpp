/**
 * @file   sieve.cpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  Task 01 - Eratosthenes Sieve
 *         Eratosthenes Sieve prime calculation algorithm.
 *         https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 * @date   2022-09-05
 *
 * @copyright Copyright (c) 2022
 */
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <cmath>

auto main([[maybe_unused]]int argc, [[maybe_unused]]char const* argv[]) -> int {
    constexpr std::int32_t P = 2;          // Start
    constexpr std::int32_t E = 1'000;      // End
    constexpr std::size_t  N = E - P + 1;  // Length - Inclusive end
    std::int32_t primes[N]{0};
    std::generate_n(primes, N, [n = P]() mutable { return n++; });

    std::int32_t p = P;
    for (std::size_t i = 0; i < N && std::size_t(p * p) < N; i++) {
        if (primes[i] == 0) continue;
        else p = primes[i];

        std::replace_if(primes + i, primes + N, [&p](auto const& n) {
            return n > p && n % p == 0;
        }, 0);
    }

    // Print out the prime numbers
    for (std::size_t i = 0; i < N; i++) {
        if (primes[i] == 0) continue;
        std::cout << primes[i];
        if (i < N - 1) std::cout << " ";
    }
    std::cout << "\n";
    return 0;
}

