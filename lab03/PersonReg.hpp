/**
 * @file   PersonReg.hpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  PersonReg is the Person Register which holds and has api to search for Person.
 * @date   2022-09-14
 *
 * @copyright Copyright (c) 2022
 */
#ifndef PERSON_REG_HPP
#define PERSON_REG_HPP

#include <string>
#include "Person.hpp"

class PersonReg {
  public:
    PersonReg(int max_storlek);
    ~PersonReg();

    auto LaggTill(Person const* const Person) -> bool;
    auto LaggTillTest(std::string const& namn, std::string const& adress) -> bool;
    auto TaBortEntry(Person* ptr) -> void;
    auto SokNamn(std::string const& namn) const -> Person*;
    auto SokFritt(std::string const& namn, Person* start) const -> Person*;
    auto Print() const -> void;
    auto Tom() -> void;

  private:
    Person* m_Personer;
};

#endif

