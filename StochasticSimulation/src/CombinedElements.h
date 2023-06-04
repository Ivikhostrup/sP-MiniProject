//
// Created by Ivik Hostrup.
// Combined elements are used to represent the reactants and products of a reaction.
// Baseline to satisfy all requirements.
//

#ifndef STOCHASTICSIMULATION_COMBINEDELEMENTS_H
#define STOCHASTICSIMULATION_COMBINEDELEMENTS_H



#include <vector>
#include <memory>
#include "Species.h"
#include <iostream>

class CombinedElements {
public:
    void Add(const std::shared_ptr<Species>& species);
    [[nodiscard]] std::vector<std::shared_ptr<Species>> GetCombinedSpecies() const;

    friend std::ostream& operator<<(std::ostream& os, const CombinedElements& combinedReactants);
private:
    std::vector<std::shared_ptr<Species>> m_combined_species;
};

CombinedElements operator+(const std::shared_ptr<Species>& leftElement, const std::shared_ptr<Species>& rightElement);


#endif //STOCHASTICSIMULATION_COMBINEDELEMENTS_H
