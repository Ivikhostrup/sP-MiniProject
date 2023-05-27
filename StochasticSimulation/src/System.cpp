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
    // Add reaction to vector of reactions
    m_reactions.push_back(reaction);
    m_rate_constant = rate_constant;
}

