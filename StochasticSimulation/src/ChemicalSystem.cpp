//
// Created by Ivik Hostrup on 5/26/2023.
//

#include <iostream>
#include <algorithm>
#include <chrono>
#include "ChemicalSystem.h"
#include "Monitor.h"


void ChemicalSystem::Simulate(size_t endTime, Monitor& monitor) {
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

        auto combinedSpecies = reaction_with_min_delay->get_reactants().GetCombinedSpecies();

        bool reactantsSufficient = true;
        for (const auto& reactant : combinedSpecies) {
            if(reactant->GetQuantity() < 1) { // If amount agents is less than 1, then the reaction cannot proceed
                reactantsSufficient = false;
                break;
            }
        }

        if(reactantsSufficient) {
            for (const auto& reactant : combinedSpecies) {
                reactant->SetQuantity(reactant->GetQuantity() - 1);
            }

            for (const auto& product : reaction_with_min_delay->get_products().GetCombinedSpecies()) {
                product->SetQuantity(product->GetQuantity() + 1);
            }
        }

        monitor.OnStateChange(startTime, *this);
    }
}

std::shared_ptr<Species> ChemicalSystem::AddSpecies(const std::string& name, const size_t& initial_amount) {
    auto new_species = std::make_shared<Species>(name, initial_amount);
    m_symbolTable_species.AddSymbol(name, new_species);

    m_initial_quantities[name] = initial_amount;
    return new_species;
}

std::shared_ptr<Species> ChemicalSystem::GetSpecies(const std::string& name) const {
    return m_symbolTable_species.GetSymbol(name);
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

void ChemicalSystem::Reset() {
    for (const auto& [name, species] : m_symbolTable_species.GetAllSymbols()) {
        species->SetQuantity(m_initial_quantities[name]);
    }
}
