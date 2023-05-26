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