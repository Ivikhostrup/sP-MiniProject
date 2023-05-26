//
// Created by Ivik Hostrup on 5/26/2023.
//

#ifndef STOCHASTICSIMULATION_REACTION_H
#define STOCHASTICSIMULATION_REACTION_H


#include <list>
#include "Species.h"

class Reaction {
public:
    Reaction add_reactant(Species species);
    Reaction add_product(Species species);
private:
    std::list<Species> m_reactants;
    std::list<Species> m_product;
    float m_rate_constant;
    float m_delay;
};


#endif //STOCHASTICSIMULATION_REACTION_H
