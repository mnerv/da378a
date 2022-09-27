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

Person::Person(std::string const& namn, std::string const& adress) : m_namn(namn), m_adress(adress) {
}

auto Person::Print() const -> void {
    std::cout << "namn: "   << m_namn   << ", ";
    std::cout << "adress: " << m_adress << " \n";
}

auto Person::operator<(Person const& other) const -> bool {
    return m_namn < other.m_namn;
}

