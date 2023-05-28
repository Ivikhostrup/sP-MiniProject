//
// Created by Ivik Hostrup on 5/26/2023.
//

#include "Reaction.h"
#include <iostream>

void Reaction::add_reactant(const std::shared_ptr<Species>& species){
    m_reactants.Add(species);
}

void Reaction::add_product(const std::shared_ptr<Species>& species) {
    m_products.Add(species);
}

[[nodiscard]] const CombinedElements& Reaction::get_reactants() const {
    return m_reactants;
}

[[nodiscard]] const CombinedElements& Reaction::get_products() const {
    return m_products;
}

// << overload to print reaction and products
std::ostream& operator<<(std::ostream& os, const Reaction& reaction) {
    // Print reactants
    size_t count = 0;
    for (const auto& reactant : reaction.get_reactants().GetCombinedSpecies()) {
        os << *reactant;
        if(++count < reaction.get_reactants().GetCombinedSpecies().size()){
            os << " + ";
        }
    }
    os << " -> "; // separator for reaction

    // Print products
    count = 0;
    for (const auto& product : reaction.get_products().GetCombinedSpecies()) {
        os << *product;
        if(++count < reaction.get_products().GetCombinedSpecies().size()){
            os << " + ";
        }
    }
    os << " (rate constant: " << reaction.m_rate_constant << ")";
}

void Reaction::set_rate_constant(const size_t& rate_constant){
    m_rate_constant = rate_constant;
}

// Multiple reactants and single products
Reaction operator>>=(const CombinedElements& combinedReactants, const std::shared_ptr<Species>& product){
    Reaction reaction;

    for(auto const& reactant : combinedReactants.GetCombinedSpecies()){
        reaction.add_reactant(reactant);
    }

    reaction.add_product(product);

    return reaction;
}

// single reactactant and multiple products
Reaction operator>>=(const std::shared_ptr<Species>& reactant, const CombinedElements& combinedProducts){
    Reaction reaction;

    reaction.add_reactant(reactant);

    for(auto const& product : combinedProducts.GetCombinedSpecies()){
        reaction.add_product(product);
    }

    return reaction;
}

// Multiple reactants and multiple products
Reaction operator>>=(const CombinedElements& combinedReactants, const CombinedElements& combinedProducts){
    Reaction reaction;

    for(auto const& reactant : combinedReactants.GetCombinedSpecies()){
        reaction.add_reactant(reactant);
    }

    for(auto const& product : combinedProducts.GetCombinedSpecies()){
        reaction.add_product(product);
    }

    return reaction;
}

// single reactactant and a single product
Reaction operator>>=(const std::shared_ptr<Species>& reactant, const std::shared_ptr<Species>& product){
    Reaction reaction;

    reaction.add_reactant(reactant);
    reaction.add_product(product);

    return reaction;
}