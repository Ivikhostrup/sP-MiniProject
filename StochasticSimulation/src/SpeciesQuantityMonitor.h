//
// Created by Ivik Hostrup on 5/29/2023.
//

#ifndef STOCHASTICSIMULATION_SPECIESQUANTITYMONITOR_H
#define STOCHASTICSIMULATION_SPECIESQUANTITYMONITOR_H


#include <vector>
#include "Monitor.h"
#include "Species.h"
#include "ChemicalSystem.h"

class SpeciesQuantityMonitor : public Monitor {
public:
    SpeciesQuantityMonitor(const std::vector<std::string>& speciesName)
        : m_species_names(speciesName), m_signals_monitor(speciesName.size()) {}

        void OnStateChange(double time, const ChemicalSystem& chemicalSystem) override;
        const std::vector<std::vector<double>>& GetSignals() const;
private:
    std::vector<std::string> m_species_names;
    std::vector<std::vector<double>> m_signals_monitor;
};


#endif //STOCHASTICSIMULATION_SPECIESQUANTITYMONITOR_H