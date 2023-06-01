//
// Created by Ivik Hostrup on 5/29/2023.
//

#include "SpeciesQuantityMonitorCallBack.h"


void SpeciesQuantityMonitorCallBack::operator()(double time, const ChemicalSystem &chemicalSystem) {
    std::vector<double> quantities;
    quantities.reserve(m_species_names.size());

    for (const auto& name : m_species_names) {
        quantities.push_back(static_cast<double>(chemicalSystem.GetSpecies(name)->GetQuantity()));
    }

    m_records.emplace_back(time, quantities);
}

const std::vector<std::string> &SpeciesQuantityMonitorCallBack::GetMonitoredSpecies() const {
    return m_species_names;
}

const std::vector<std::vector<double>> &SpeciesQuantityMonitorCallBack::GetSignals() const {
    return m_signals_monitor;
}

const std::vector<DataRecord> &SpeciesQuantityMonitorCallBack::GetRecords() const {
    return m_records;
}


