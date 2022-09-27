/**
 * @file   PersonReg.cpp
 * @author Pratchaya Khansomboon (me@mononerv.dev)
 * @brief  Person register implementations.
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

auto PersonReg::LaggTill(Person const* const person) -> bool {
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
    if (m_storlek == 0 || ptr == nullptr) return;
    *ptr = m_personer[--m_storlek];
    m_personer[m_storlek] = {};
}

auto PersonReg::SokNamn(std::string const& namn) const -> Person* {
    for (auto it = m_personer; it != m_personer + m_max_storlek; ++it)
        if (it->Namn() == namn) return it;
    return nullptr;
}

auto PersonReg::SokFritt(std::string const& search_value, Person* start_search) const -> Person* {
    auto start_ptr = start_search == nullptr ? m_personer : ++start_search;  // Skip the current one if there's a starting point
    for (auto it = start_ptr; it != m_personer + m_max_storlek; ++it) {
        if (it->Namn() == search_value || it->Adress() == search_value) return it;
    }
    return nullptr;
}

auto PersonReg::Print() const -> void {
    for (auto it = m_personer; it != m_personer + m_storlek; ++it)
        it->Print();
}

/**
 * Set the current size to zero and all the object in the list are set to empty,
 * in this case the 'namn' and 'adress' is set to empty string.
 */
auto PersonReg::Tom() -> void {
    for (auto it = m_personer; it != m_personer + m_max_storlek; ++it)
        *it = {};
    m_storlek = 0;
}

auto PersonReg::begin() -> Person* {
    return m_personer;
}

auto PersonReg::end() -> Person* {
    return m_personer + m_storlek;
}

