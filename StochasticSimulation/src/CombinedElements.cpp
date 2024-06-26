//
// Created by Ivik Hostrup.
//

#include "CombinedElements.h"
#include <iostream>

void CombinedElements::Add(const std::shared_ptr<Species>& species) {
    if(species){
        m_combined_species.push_back(species);
    } else {
        std::cout << "Species is null" << std::endl;
    }
}

std::vector<std::shared_ptr<Species>> CombinedElements::GetCombinedSpecies() const{
    return m_combined_species;
}

std::ostream& operator<<(std::ostream& os, const CombinedElements& combinedReactants) {
    // Print the Species objects in the CombinedElements object
    for (const auto& species : combinedReactants.GetCombinedSpecies()) {
        os << *species;
    }
    return os;
}

CombinedElements operator+(const std::shared_ptr<Species>& leftElement, const std::shared_ptr<Species>& rightElement) {
    CombinedElements combination;
    combination.Add(leftElement);
    combination.Add(rightElement);

    return std::move(combination);
}