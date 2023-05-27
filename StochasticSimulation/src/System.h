//
// Created by Ivik Hostrup on 5/26/2023.
//

#ifndef STOCHASTICSIMULATION_SYSTEM_H
#define STOCHASTICSIMULATION_SYSTEM_H


#include <vector>
#include "Reaction.h"

class System {
public:
    void Simulate();
    void AddSpecies(const std::shared_ptr<Species>& species);
    void AddReaction(const std::shared_ptr<Reaction>& reaction, const size_t& rate_constant);


private:
    std::vector<std::shared_ptr<Species>> m_species;
    std::vector<std::shared_ptr<Reaction>> m_reactions;
    size_t m_rate_constant = 0;
    size_t m_delay = 0.0;
};

// Constructor til at tage start state og reactions ind



#endif //STOCHASTICSIMULATION_SYSTEM_H
