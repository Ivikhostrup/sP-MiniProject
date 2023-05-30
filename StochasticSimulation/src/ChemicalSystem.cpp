//
// Created by Ivik Hostrup on 5/26/2023.
//

#include <iostream>
#include <algorithm>
#include "ChemicalSystem.h"


void ChemicalSystem::Simulate(double endTime) {
    double startTime = 0.0;

    while (startTime < endTime){
        ComputeDelay();


        auto reaction_map = m_symbolTable_reactions.GetAllSymbols();
        auto reaction_with_min_delay = reaction_map.begin()->second;


        for (const auto& [_, reaction] : reaction_map) {
            if (reaction->get_delay() < reaction_with_min_delay->get_delay()) {
                reaction_with_min_delay = reaction;
            }
        }

        startTime += reaction_with_min_delay->get_delay();

        // Proceed with the reaction
        for (const auto& reactant : reaction_with_min_delay->get_reactants().GetCombinedSpecies()) {
            if(std::all_of(reaction_with_min_delay->get_reactants().GetCombinedSpecies().begin(),
                           reaction_with_min_delay->get_reactants().GetCombinedSpecies().end(),
                           [](const auto& reactant) {
                               return reactant->GetQuantity() > 0;
                           })) {
                reactant->SetQuantity(reactant->GetQuantity() - 1);
            }
        }

        for (const auto& product : reaction_with_min_delay->get_products().GetCombinedSpecies()) {
            product->SetQuantity(product->GetQuantity() + 1);
        }

        std::cout << *reaction_with_min_delay;

    }
}

std::shared_ptr<Species> ChemicalSystem::AddSpecies(const std::string& name, const size_t& initial_amount) {
    auto new_species = std::make_shared<Species>(name, initial_amount);
    m_symbolTable_species.AddSymbol(name, new_species);
    return new_species;
}

void ChemicalSystem::AddReaction(const Reaction &reaction, const double& rate_constant) {
    auto new_reaction = std::make_shared<Reaction>(reaction);
    new_reaction->SetRateConstant(rate_constant);
    auto reaction_name = new_reaction->to_string();
    m_symbolTable_reactions.AddSymbol(reaction_name, new_reaction);
}

std::vector<std::shared_ptr<Reaction>> ChemicalSystem::get_reactions() const {
    return m_reactions;
}

// Overload << for reactions in system
std::ostream& operator<<(std::ostream& os, const ChemicalSystem& system) {
    for (const auto& reaction : system.get_reactions()) {
        os << *reaction << std::endl;
    }
    return os;
}

void ChemicalSystem::ComputeDelay() {
    auto reaction_map = m_symbolTable_reactions.GetAllSymbols();

    std::random_device rd;
    std::mt19937 gen(rd());

    for(const auto& [name, reaction] : reaction_map){
        reaction->ComputeDelay(gen);
    }
}

std::vector<std::shared_ptr<Species>> ChemicalSystem::get_species() const {
    return m_species;
}
