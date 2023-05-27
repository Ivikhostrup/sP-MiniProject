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
    void AddSpecies(const std::string& name, int initialQuantity);

    friend std::ostream& operator<<(std::ostream& os, const System& simulation);

    System& operator()(const std::string& name, int initialQuantity) {
        AddSpecies(name, initialQuantity);
        ;
    }


    /*System operator()(const Reaction& reaction, const) {
        AddCombinedReactants(reactants);
        AddProduct(product);

        return *this;
    }*/
private:
    std::vector<Species> m_species;
    //std::vector<Reaction> m_reactions;
    float m_delay = 0.0;
};




#endif //STOCHASTICSIMULATION_SYSTEM_H
