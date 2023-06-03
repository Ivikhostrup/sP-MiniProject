//
// Created by Ivik Hostrup on 5/29/2023.
//

#include <algorithm>
#include "SpeciesQuantityMonitorCallBack.h"
#include "plot.hpp"


void SpeciesQuantityMonitorCallBack::operator()(double time, const ChemicalSystem &chemicalSystem) {
    std::scoped_lock lock(m_mutex);

    m_timepoints.push_back(time);
    for(size_t i = 0; i < m_species_names.size(); ++i) {
        m_signals_monitor[i].push_back(chemicalSystem.GetSpecies(m_species_names[i])->GetQuantity());
    }

    // Mutex unlocks when going out of scope
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

void SpeciesQuantityMonitorCallBack::CreatePlot(const std::string &plotName,
                                                const std::string &xAxisLabel,
                                                const std::string &yAxisLabel,
                                                int width, int height) const {

    // Create map for species and their quantities
    std::unordered_map<std::string, std::vector<double>> speciesQuantities;

    for(size_t i = 0; i < m_species_names.size(); ++i) {
        std::vector<double> signals = m_signals_monitor[i];
        if(m_species_names[i] == "H") {
            for(size_t j = 0; j < signals.size(); ++j) {
                signals[j] *= 1000;
            }
        }
        speciesQuantities[m_species_names[i]] = signals;
    }

    // Create plot instance
    Plot plot(plotName, xAxisLabel, yAxisLabel, width, height);

    // Add data to plot
    plot.plot_data(m_timepoints, speciesQuantities);

    // Show the plot
    plot.process();
    plot.save_to_png("CovidSimulation.png");
}

double SpeciesQuantityMonitorCallBack::GetPeak(const std::string& speciesName) const {

    auto it = std::find(m_species_names.begin(), m_species_names.end(), speciesName);

    if(it != m_species_names.end()) {
        size_t index = std::distance(m_species_names.begin(), it);

        return *std::max_element(m_signals_monitor[index].begin(), m_signals_monitor[index].end());
    } else {
        throw std::invalid_argument("Species name not found");
    }
}




