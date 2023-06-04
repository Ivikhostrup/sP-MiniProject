//
// Created by Ivik Hostrup.
//

#include <iostream>
#include <algorithm>
#include <chrono>
#include "ChemicalSystem.h"
#include "Monitor.h"


std::shared_ptr<Species> ChemicalSystem::AddSpecies(const std::string& name, const size_t& initial_amount) {
    auto new_species = std::make_shared<Species>(name, initial_amount);
    m_symbolTable_species.AddSymbol(name, new_species);

    m_initial_quantities[name] = initial_amount;
    return new_species;
}

std::shared_ptr<Species> ChemicalSystem::GetSpecies(const std::string& name) const {
    return m_symbolTable_species.GetSymbol(name);
}


std::shared_ptr<Reaction> ChemicalSystem::AddReaction(const Reaction &reaction, const double& rate_constant) {
    auto new_reaction = std::make_shared<Reaction>(reaction);
    new_reaction->SetRateConstant(rate_constant);
    auto reaction_name = new_reaction->to_string();
    m_symbolTable_reactions.AddSymbol(reaction_name, new_reaction);

    return new_reaction;
}

std::vector<std::shared_ptr<Reaction>> ChemicalSystem::GetReactions() const {
    return m_reactions;
}

// Overload << for reactions in system
std::ostream& operator<<(std::ostream& os, const ChemicalSystem& system) {
    for (const auto& reaction : system.GetReactions()) {
        os << *reaction << std::endl;
    }
    return os;
}

void ChemicalSystem::ComputeDelay() {
    auto reaction_map = m_symbolTable_reactions.GetAllSymbols();

    for(const auto& [name, reaction] : reaction_map){
        reaction->ComputeDelay(m_gen);
    }
}

void ChemicalSystem::Reset() {
    for (const auto& [name, species] : m_symbolTable_species.GetAllSymbols()) {
        species->SetQuantity(m_initial_quantities[name]);
    }
}
