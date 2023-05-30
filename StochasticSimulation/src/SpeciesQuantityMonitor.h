//
// Created by Ivik Hostrup on 5/29/2023.
//

#ifndef STOCHASTICSIMULATION_SPECIESQUANTITYMONITOR_H
#define STOCHASTICSIMULATION_SPECIESQUANTITYMONITOR_H


#include "Monitor.h"
#include "Species.h"

class SpeciesQuantityMonitor : public Monitor {
public:
    SpeciesQuantityMonitor(std::vector<std::string>& speciesName)
        : m_species_names(speciesName), m_signals(speciesName.size()) {}

        void OnStateChange(double time, const ChemicalSystem& chemicalSystem) override;
private:
    std::vector<std::string>& m_species_names;
    std::vector<std::vector<double>> m_signals;
};


#endif //STOCHASTICSIMULATION_SPECIESQUANTITYMONITOR_H
