//
// Created by Ivik Hostrup on 5/26/2023.
//

#ifndef STOCHASTICSIMULATION_COMBINEDREACTANTS_H
#define STOCHASTICSIMULATION_COMBINEDREACTANTS_H



#include <vector>
#include "Species.h"

class CombinedReactants {
public:
    void Add(const Species& species);
    std::vector<Species> GetCombinedSpecies() const;
private:
    std::vector<Species> m_combined_species;
};

CombinedReactants operator+(const Species& l, const Species& r) {
    CombinedReactants combination;

    combination.Add(l);
    combination.Add(r);

    return combination;
}


#endif //STOCHASTICSIMULATION_COMBINEDREACTANTS_H
