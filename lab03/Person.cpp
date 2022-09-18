/**
 * @file   Person.cpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  Person implementation
 * @date   2022-09-16
 *
 * @copyright Copyright (c) 2022
 */
#include "Person.hpp"
#include <iostream>

auto Person::Print() const -> void {
    std::cout << "Person { ";
    std::cout << "namn: "   << namn   << ", ";
    std::cout << "adress: " << adress << " }\n";
}
