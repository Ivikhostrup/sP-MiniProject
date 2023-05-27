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
    

private:
    std::vector<std::shared_ptr<Species>> m_species;
    size_t m_delay = 0.0;
};

// Constructor til at tage start state og reactions ind



#endif //STOCHASTICSIMULATION_SYSTEM_H
