//
// Created by Ivik Hostrup on 5/26/2023.
//

#ifndef STOCHASTICSIMULATION_CHEMICALSYSTEM_H
#define STOCHASTICSIMULATION_CHEMICALSYSTEM_H


#include <vector>
#include "Reaction.h"
#include "SymbolTable.h"
#include "Monitor.h"

class ChemicalSystem {
public:
    void Simulate(size_t endTime, Monitor& monitor);
    void ComputeDelay();
    void Reset();

    std::shared_ptr<Species> AddSpecies(const std::string& name, const size_t& initial_amount);
    std::shared_ptr<Species> GetSpecies(const std::string& name) const;
    void AddReaction(const Reaction& reaction, const double& rate_constant);
    [[nodiscard]] std::vector<std::shared_ptr<Reaction>> get_reactions() const;
    std::vector<std::shared_ptr<Species>> get_species() const;

    friend std::ostream& operator<<(std::ostream& os, const ChemicalSystem& system);
private:
    std::vector<std::shared_ptr<Species>> m_species;
    std::vector<std::shared_ptr<Reaction>> m_reactions;
    SymbolTable<Species> m_symbolTable_species;
    SymbolTable<Reaction> m_symbolTable_reactions;
    std::unordered_map<std::string, size_t> m_initial_quantities;
};




#endif //STOCHASTICSIMULATION_CHEMICALSYSTEM_H
