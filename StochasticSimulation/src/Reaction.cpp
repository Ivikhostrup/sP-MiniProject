//
// Created by Ivik Hostrup on 5/26/2023.
//

#include "Reaction.h"
#include <iostream>

Reaction Reaction::add_reactant(const std::shared_ptr<Species>& species){
    m_reactants.push_back(species);
    return *this;
}

Reaction Reaction::add_product(const std::shared_ptr<Species>& species) {
    m_products.push_back(species);
    return *this;
}

[[nodiscard]] const std::vector<std::shared_ptr<Species>>& Reaction::get_reactants() const {
    return m_reactants;
}

[[nodiscard]] const std::vector<std::shared_ptr<Species>>& Reaction::get_products() const {
    return m_products;
}

std::ostream& operator<<(std::ostream& os, const Reaction& reaction) {
    // Print reactants
    for (const auto& reactant : reaction.get_reactants()) {
        os << *reactant << " + ";
    }
    os << " -> "; // separator for reaction

    // Print products
    for (const auto& product : reaction.get_products()) {
        os << *product << " + ";
    }
    return os;
}
