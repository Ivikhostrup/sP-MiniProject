//
// Created by Ivik Hostrup on 5/26/2023.
//

#include "CombinedReactants.h"

void CombinedReactants::Add(const Species& species) {
    m_combined_species.push_back(species);
}

std::vector<Species> CombinedReactants::GetCombinedSpecies() const{
    return m_combined_species;
}

std::ostream& operator<<(std::ostream& os, const CombinedReactants& combinedReactants) {
    // Print the Species objects in the CombinedReactants object
    for (const auto& species : combinedReactants.GetCombinedSpecies()) {
        os << species << " + ";
    }
    return os;
}