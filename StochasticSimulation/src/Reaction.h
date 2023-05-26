//
// Created by Ivik Hostrup on 5/26/2023.
//

#ifndef STOCHASTICSIMULATION_REACTION_H
#define STOCHASTICSIMULATION_REACTION_H



#include <memory>
#include <vector>
#include "Species.h"
#include "CombinedReactants.h"

class Reaction {
public:
    //explicit Reaction(float rate_constant) : m_rate_constant(rate_constant){}

    Reaction add_reactant(Species species); // Might need to update this
    Reaction add_product(Species species); // Might need to update this

    float get_rate_constant() const;
    void set_rate_constant(float rate_constant);
    float get_delay() const;
    void set_delay(float delay);
    [[nodiscard]] const std::vector<std::shared_ptr<Species>>& get_reactants() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Species>>& get_products() const;

private:
    std::vector<std::shared_ptr<Species>> m_reactants;
    std::vector<std::shared_ptr<Species>> m_products;
    float m_rate_constant;
    float m_delay = 0.0;
};

Reaction operator>>=(const CombinedReactants& combinedReactants, const Species& species){
    Reaction reaction;

    for(auto const& reactant : combinedReactants.GetCombinedSpecies()){
        reaction.add_reactant(reactant);
    }

    reaction.add_product(species);

    return reaction;
}


#endif //STOCHASTICSIMULATION_REACTION_H
