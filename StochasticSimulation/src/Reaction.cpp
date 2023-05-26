//
// Created by Ivik Hostrup on 5/26/2023.
//

#include "Reaction.h"

Reaction Reaction::add_reactant(Species species){
    auto sharedSpecies = std::make_shared<Species>(species);
    m_reactants.push_back(sharedSpecies);
    return *this;
}

Reaction Reaction::add_product(Species species) {
    auto sharedSpecies = std::make_shared<Species>(species);
    m_products.push_back(sharedSpecies);
    return *this;
}

float Reaction::get_rate_constant() const {
    return m_rate_constant;
}

void Reaction::set_rate_constant(float rate_constant) {
    m_rate_constant = rate_constant;
}

float Reaction::get_delay() const {
    return m_delay;
}

void Reaction::set_delay(float delay) {
    m_delay = delay;
}

[[nodiscard]] const std::list<std::shared_ptr<Species>>& Reaction::get_reactants() const {
    return m_reactants;
}

[[nodiscard]] const std::list<std::shared_ptr<Species>>& Reaction::get_products() const {
    return m_products;
}