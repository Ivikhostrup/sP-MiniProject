//
// Created by Ivik Hostrup on 5/26/2023.
//

#include "Reaction.h"

Reaction Reaction::add_reactant(Species species){
    m_reactants.push_back(species);
    return *this;
}

Reaction Reaction::add_product(Species species) {
    m_product.push_back(species);
    return *this;
}