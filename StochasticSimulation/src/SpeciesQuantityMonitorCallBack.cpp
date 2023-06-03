//
// Created by Ivik Hostrup on 5/29/2023.
//

#include "SpeciesQuantityMonitorCallBack.h"


void SpeciesQuantityMonitorCallBack::operator()(double time, const ChemicalSystem &chemicalSystem) {
    m_timepoints.push_back(time);
    for(size_t i = 0; i < m_species_names.size(); ++i) {
        m_signals_monitor[i].push_back(chemicalSystem.GetSpecies(m_species_names[i])->GetQuantity());
    }
}

const std::vector<std::string>& SpeciesQuantityMonitorCallBack::GetMonitoredSpecies() const {
    return m_species_names;
}

const std::vector<std::vector<double>>& SpeciesQuantityMonitorCallBack::GetSignals() const {
    return m_signals_monitor;
}

const std::vector<double>& SpeciesQuantityMonitorCallBack::GetTimepoints() const {
    return m_timepoints;
}



