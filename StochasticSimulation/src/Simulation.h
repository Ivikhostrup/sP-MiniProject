//
// Created by Ivik Hostrup on 5/26/2023.
//

#ifndef STOCHASTICSIMULATION_SIMULATION_H
#define STOCHASTICSIMULATION_SIMULATION_H


#include <vector>
#include "Reaction.h"

class Simulation {
public:

    Simulation operator()(const CombinedReactants& reactants, const Species& product) {
        AddCombinedReactants(reactants);
        AddProduct(product);

        return *this;
    }

    void AddCombinedReactants(const CombinedReactants& reactants);
    void AddProduct(const Species& product);

    friend std::ostream& operator<<(std::ostream& os, const Simulation& simulation);
private:
    CombinedReactants m_combinedReactants;
    Species m_species;
};




#endif //STOCHASTICSIMULATION_SIMULATION_H
