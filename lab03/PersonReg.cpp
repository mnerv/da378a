/**
 * @file   PersonReg.cpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  Person register implementations
 * @date   2022-09-14
 *
 * @copyright Copyright (c) 2022
 */
#include "PersonReg.hpp"

PersonReg::PersonReg(int const& max_storlek)
    : m_max_storlek(static_cast<std::size_t>(max_storlek)), m_storlek(0) {
    m_personer = new Person[m_max_storlek];
}

PersonReg::~PersonReg() {
    delete[] m_personer;
}

auto PersonReg::LaggTill([[maybe_unused]]Person const* const person) -> bool {
    if (m_storlek == m_max_storlek) return false;
    m_personer[m_storlek++] = *person;
    return true;
}

auto PersonReg::LaggTillTest(std::string const& namn, std::string const& adress) -> bool {
    if (m_storlek == m_max_storlek) return false;
    m_personer[m_storlek++] = {namn, adress};
    return true;
}

auto PersonReg::TaBortEntry(Person* ptr) -> void {
    if (m_storlek == 0) return;
    Person* found = nullptr;
    for (auto it = m_personer; it != m_personer + m_max_storlek; ++it) {
        if (it->namn == ptr->namn && it->adress == ptr->adress) {
            found = it;
            break;
        }
    }
    for (auto it = found; it != m_personer + m_max_storlek; ++it) {
        if (it + 1 != m_personer + m_max_storlek)
            *it = *(it + 1);
    }
    m_storlek--;
    m_personer[m_storlek] = {};
}

auto PersonReg::SokNamn([[maybe_unused]]std::string const& namn) const -> Person* {
    for (auto ptr = m_personer; ptr != m_personer + m_max_storlek; ++ptr) {
        if (ptr->namn == namn) return ptr;
    }
    return nullptr;
}

auto PersonReg::SokFritt(std::string const& namn, Person* start_search) const -> Person* {
    if (start_search > m_personer + m_max_storlek) return nullptr;
    auto start_ptr = start_search == nullptr ? m_personer : start_search;
    for (auto it = start_ptr; it != m_personer + m_max_storlek; ++it) {
        if (it->namn == namn) return it;
    }
    return nullptr;
}

auto PersonReg::Print() const -> void {
    for (auto person = m_personer; person != m_personer + m_max_storlek; ++person) {
        if (!person->namn.empty()) person->Print();
    }
}

auto PersonReg::Tom() -> void {
    for (auto ptr = m_personer; ptr != m_personer + m_max_storlek; ++ptr)
        *ptr = {};
    m_storlek = 0;
}
