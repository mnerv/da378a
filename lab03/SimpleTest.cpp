/**
 * @file   PersonRegTest.cpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  Test program for person and person_reg.
 * @date   2022-09-14
 *
 * @copyright Copyright (c) 2022
 */
#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>

#include "PersonReg.hpp"

class PersonMedTel : public Person {
  public:
    PersonMedTel(std::string const& namn, std::string const& adress, std::string const& tel)
        : Person(namn, adress), tel(tel) {}

    auto Print() const -> void override {
        std::cout << "PersonMedTel { ";
        std::cout << "namn: " << namn << ", ";
        std::cout << "adress: " << adress << ", ";
        std::cout << "tel: " << tel << " }";
    }

    std::string tel;
};

auto read_register(PersonReg& reg, std::string filename) -> bool {
    std::string line;
    std::ifstream file{filename};
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << "\n";
        return false;
    }

    while(std::getline(file, line)) {
        while(line.length() == 0 && std::getline(file, line));
        std::string name{line};
        std::string adress;
        std::getline(file, adress);
        Person p{name, adress};
        auto complete = reg.LaggTill(&p);
        if (!complete) return true;
    }

    return true;
}

auto main([[maybe_unused]]std::int32_t argc, [[maybe_unused]]char const* argv[]) -> std::int32_t {
    PersonReg reg{10};
    read_register(reg, "personer.txt");
    reg.Print();
    std::cout << "\n";

    auto a = reg.SokNamn("Eric");
    auto b = reg.SokNamn("Daniel");
    reg.TaBortEntry(a);
    reg.TaBortEntry(b);
    reg.Print();
    std::cout << "\n";

    PersonMedTel te("Hello", "World", "02");
    reg.LaggTill(&te);
    reg.Print();
    return 0;
}

