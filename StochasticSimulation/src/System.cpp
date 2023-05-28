//
// Created by Ivik Hostrup on 5/26/2023.
//

#include <iostream>
#include "System.h"


void System::Simulate() {

}

void System::AddSpecies(const std::string& name, const size_t& initial_amount) {
    auto new_species = std::make_shared<Species>(name, initial_amount);
    m_species.push_back(new_species);
}

void System::AddReaction(const Reaction &reaction, const size_t &rate_constant) {
    auto new_reaction = std::make_shared<Reaction>(reaction);
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
