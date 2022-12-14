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

Person::Person(std::string const& namn, std::string const& adress) : namn(namn), adress(adress) {
}
Person::~Person() = default;

auto Person::Print() const -> void {
    std::cout << "namn: "   << namn   << ", ";
    std::cout << "adress: " << adress << " \n";
}

