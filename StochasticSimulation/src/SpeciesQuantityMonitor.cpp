//
// Created by Ivik Hostrup on 5/29/2023.
//

#include "SpeciesQuantityMonitor.h"


void SpeciesQuantityMonitor::OnStateChange(double time, const ChemicalSystem &chemicalSystem) {
        for(size_t i = 0; i < m_species_names.size(); ++i) {
            m_signals[i].push_back(chemicalSystem.GetSpecies(m_species_names[i])->GetQuantity())
        }
}

const std::vector<std::vector<double>> &SpeciesQuantityMonitor::GetSignals() const {
    return m_signals;
}
