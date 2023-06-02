//
// Created by Ivik Hostrup on 5/29/2023.
//

#ifndef STOCHASTICSIMULATION_SPECIESQUANTITYMONITORCALLBACK_H
#define STOCHASTICSIMULATION_SPECIESQUANTITYMONITORCALLBACK_H


#include <vector>
#include "Monitor.h"
#include "Species.h"
#include "ChemicalSystem.h"
#include "MonitorCallBack.h"

class SpeciesQuantityMonitorCallBack : public MonitorCallBack {
public:
    explicit SpeciesQuantityMonitorCallBack(const std::vector<std::string>& speciesName)
        : m_species_names(speciesName), m_signals_monitor(speciesName.size()), m_timepoints() {}

        void operator()(double time, const ChemicalSystem& chemicalSystem) override;


        const std::vector<std::vector<double>>& GetSignals() const;
        const std::vector<std::string>& GetMonitoredSpecies() const;
        const std::vector<double>& GetTimepoints() const;
private:
    std::vector<std::string> m_species_names;
    std::vector<std::vector<double>> m_signals_monitor;
    std::vector<double> m_timepoints;
};


#endif //STOCHASTICSIMULATION_SPECIESQUANTITYMONITORCALLBACK_H
