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

/**
 * Removes a person in the register and pack the array data linearly. This
 * solution keeps the order of the list, another way is to swap the last place
 * and the removing place and set the last place to an empty object. The result
 * of it will be faster, because it is O(1).
 *
 * @param ptr The pointer needs to point into the PersonReg memory space that's allocated.
 */
auto PersonReg::TaBortEntry(Person* ptr) -> void {
    if (m_storlek == 0 || ptr == nullptr) return;
    for (auto it = ptr; it != m_personer + m_max_storlek; ++it) {
        if (it + 1 != m_personer + m_max_storlek)
            *it = *(it + 1);
    }
    m_storlek--;
    m_personer[m_storlek] = {};
}

auto PersonReg::SokNamn(std::string const& namn) const -> Person* {
    for (auto it = m_personer; it != m_personer + m_max_storlek; ++it)
        if (it->namn == namn) return it;
    return nullptr;
}

auto PersonReg::SokFritt(std::string const& search_value, Person* start_search) const -> Person* {
    auto start_ptr = start_search == nullptr ? m_personer : ++start_search;  // Skip the current one if there's a starting point
    for (auto it = start_ptr; it != m_personer + m_max_storlek; ++it) {
        if (it->namn == search_value || it->adress == search_value) return it;
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

