//
// Created by Ivik Hostrup on 5/26/2023.
//

#ifndef STOCHASTICSIMULATION_REACTION_H
#define STOCHASTICSIMULATION_REACTION_H



#include <memory>
#include <vector>
#include "Species.h"
#include "CombinedElements.h"
#include <iostream>

class Reaction {
public:
    Reaction add_reactant(const std::shared_ptr<Species>& species);
    Reaction add_product(const std::shared_ptr<Species>& species);

    [[nodiscard]] const std::vector<std::shared_ptr<Species>>& get_reactants() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Species>>& get_products() const;

    friend std::ostream& operator<<(std::ostream& os, const Reaction& reaction);
private:
    std::vector<std::shared_ptr<Species>> m_reactants;
    std::vector<std::shared_ptr<Species>> m_products;
};

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

#endif //STOCHASTICSIMULATION_REACTION_H
