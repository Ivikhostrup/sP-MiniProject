//
// Created by Ivik Hostrup on 5/26/2023.
//

#include "Reaction.h"
#include <iostream>
#include <sstream>
#include <random>

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


void Reaction::set_rate_constant(const double& rate_constant){
    m_rate_constant = rate_constant;
}

std::ostream& operator<<(std::ostream& os, const Reaction& reaction) {
    reaction.print_reaction(os);
    os << " (rate constant: " << reaction.m_rate_constant << ")";
    return os;
}

std::string Reaction::to_string() const {
    std::ostringstream os;
    print_reaction(os);
    return os.str();
}

void Reaction::print_reaction(std::ostream &os) const {
    // Print reactants
    size_t count = 0;
    for (const auto& reactant : this->get_reactants().GetCombinedSpecies()) {
        os << *reactant;
        if(++count < this->get_reactants().GetCombinedSpecies().size()){
            os << " + ";
        }
    }
    os << " -> "; // separator for reaction

    // Print products
    count = 0;
    for (const auto& product : this->get_products().GetCombinedSpecies()) {
        os << *product;
        if(++count < this->get_products().GetCombinedSpecies().size()){
            os << " + ";
        }
    }
}

void Reaction::set_delay(const double& delay) {
    m_delay = delay;
}

double Reaction::get_delay() const {
    return m_delay;
}

void Reaction::ComputeDelay(std::mt19937& gen) {
    auto lambda = static_cast<double>(m_rate_constant);

    for(const auto& reactant : m_reactants.GetCombinedSpecies()){
        lambda *= static_cast<double>(reactant->GetQuantity());
    }

    std::exponential_distribution distribution(lambda);

    m_delay = distribution(gen);
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