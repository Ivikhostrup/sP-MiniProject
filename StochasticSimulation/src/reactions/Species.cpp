//
// Created by Ivik Hostrup on 5/26/2023.
//

#include <stdexcept>
#include "Species.h"
#include <iostream>

const std::string& Species::GetName() const {
    return m_name;
}

void Species::IncreaseQuantity() {
    m_quantity++;
}

void Species::DecreaseQuantity() {
    if (m_quantity < 0) {
        throw std::runtime_error("Cannot have negative quantity");
    }

    m_quantity--;
}

std::ostream& operator<<(std::ostream& os, const Species& species) {
    os << species.GetName() << ":" << species.GetQuantity() << " ";
    return os;
}

const size_t& Species::GetQuantity() const {
    return m_quantity;
}

void Species::SetQuantity(const size_t &quantity) {
    m_quantity = quantity;
}