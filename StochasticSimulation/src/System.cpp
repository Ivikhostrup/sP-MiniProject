//
// Created by Ivik Hostrup on 5/26/2023.
//

#include <iostream>
#include "System.h"


void System::Simulate() {

}

void System::AddSpecies(const std::shared_ptr<Species>& species) {
    // Add species to vector of species
    m_species.push_back(species);
}

void System::AddReaction(const std::shared_ptr<Reaction> &reaction, const size_t &rate_constant) {
    auto new_reaction = std::make_shared<Reaction>(*reaction);
    new_reaction->set_rate_constant(rate_constant);
    m_reactions.push_back(new_reaction);
}

std::vector<std::shared_ptr<Reaction>> System::get_reactions() const {
    return m_reactions;
}

// Overload << for reactions in system
std::ostream& operator<<(std::ostream& os, const System& system) {
    for (const auto& reaction : system.get_reactions()) {
        os << *reaction << std::endl;
    }
    return os;
}
