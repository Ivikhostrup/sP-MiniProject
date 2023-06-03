//
// Created by Ivik Hostrup on 5/29/2023.
//

#ifndef STOCHASTICSIMULATION_SPECIESQUANTITYMONITORCALLBACK_H
#define STOCHASTICSIMULATION_SPECIESQUANTITYMONITORCALLBACK_H


#include <vector>
#include <mutex>
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
    void CreatePlot(const std::string& plotName = "Covid Simulation",
                    const std::string& xAxisLabel = "Time",
                    const std::string& yAxisLabel = "Quantity",
                    int width = 800, int height = 600) const;
    double GetPeak(const std::string& speciesName) const;
private:
    std::vector<std::string> m_species_names;
    std::vector<std::vector<double>> m_signals_monitor;
    std::vector<double> m_timepoints;
    std::mutex m_mutex;
};


#endif //STOCHASTICSIMULATION_SPECIESQUANTITYMONITORCALLBACK_H
