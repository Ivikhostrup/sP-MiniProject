//
// Created by Ivik Hostrup on 5/26/2023.
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

CombinedElements operator+(const std::shared_ptr<Species>& leftElement, const std::shared_ptr<Species>& rightElement) {
    CombinedElements combination;

    combination.Add(leftElement);
    combination.Add(rightElement);

    return combination;
}


#endif //STOCHASTICSIMULATION_COMBINEDELEMENTS_H
