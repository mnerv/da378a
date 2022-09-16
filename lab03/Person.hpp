/**
 * @file   Person.hpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  Person is the datastructure that holds Person informations.
 * @date   2022-09-14
 *
 * @copyright Copyright (c) 2022
 */
#ifndef PERSON_HPP
#define PERSON_HPP
#include <string>

struct Person {
    std::string namn;
    std::string adress;

    auto Print() const -> void;
};

#endif

