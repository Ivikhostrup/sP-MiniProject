//
// Created by Ivik Hostrup on 5/26/2023.
//

#ifndef STOCHASTICSIMULATION_CHEMICALSYSTEM_H
#define STOCHASTICSIMULATION_CHEMICALSYSTEM_H

#include <chrono>
#include <vector>
#include "Reaction.h"
#include "SymbolTable.h"
#include "Monitor.h"

class ChemicalSystem {
public:
    ChemicalSystem() : m_gen(m_rd()) {};

    template <typename CallBackType>
    void Simulate(size_t endTime, Monitor<CallBackType>& monitor) {
        double startTime = 0.0;

        while (startTime <= endTime){
            ComputeDelay();

            auto reaction_map = m_symbolTable_reactions.GetAllSymbols();
            auto reaction_with_min_delay = reaction_map.begin()->second;

            for (const auto& [_, reaction] : reaction_map) {
                if (reaction->get_delay() < reaction_with_min_delay->get_delay()) {
                    reaction_with_min_delay = reaction;
                }
            }

            startTime += reaction_with_min_delay->get_delay();
            //std::cout << startTime << std::endl;
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

    void ComputeDelay();
    void Reset();

    std::shared_ptr<Species> AddSpecies(const std::string& name, const size_t& initial_amount);
    std::shared_ptr<Species> GetSpecies(const std::string& name) const;
    std::shared_ptr<Reaction> AddReaction(const Reaction& reaction, const double& rate_constant);
    [[nodiscard]] std::vector<std::shared_ptr<Reaction>> get_reactions() const;
    std::vector<std::shared_ptr<Species>> get_species() const;

    friend std::ostream& operator<<(std::ostream& os, const ChemicalSystem& system);
private:
    std::vector<std::shared_ptr<Species>> m_species;
    std::vector<std::shared_ptr<Reaction>> m_reactions;
    SymbolTable<Species> m_symbolTable_species;
    SymbolTable<Reaction> m_symbolTable_reactions;
    std::unordered_map<std::string, size_t> m_initial_quantities;
    std::random_device m_rd;
    std::mt19937 m_gen;
};




#endif //STOCHASTICSIMULATION_CHEMICALSYSTEM_H
