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

class Person {
  public:
    Person(std::string const& namn = "", std::string const& adress = "");

    auto Print() const -> void;
    auto Namn()   const -> std::string const& { return m_namn; }
    auto Adress() const -> std::string const& { return m_adress; }

    auto operator<(Person const& other) const -> bool;

  private:
    std::string m_namn;
    std::string m_adress;
};

#endif

