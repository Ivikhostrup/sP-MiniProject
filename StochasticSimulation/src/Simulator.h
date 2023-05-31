//
// Created by Ivik Hostrup on 5/30/2023.
//

#ifndef STOCHASTICSIMULATION_SIMULATOR_H
#define STOCHASTICSIMULATION_SIMULATOR_H


#include "ChemicalSystem.h"

class Simulator {
public:
    Simulator(ChemicalSystem& system, int numTrajectories, size_t endTime)
        : m_system(system), m_numTrajectories(numTrajectories), m_endTime(endTime) {}

    void RunSimulation(const std::vector<std::string>& speciesToMonitor);
    std::vector<std::vector<double>> GetAverageSignals() const;
    void WriteToCsv(const std::string& filename, const std::vector<std::string>& speciesNames) const;


private:
    ChemicalSystem& m_system;
    int m_numTrajectories;
    size_t m_endTime;
    std::vector<std::vector<double>> m_signals;
};


#endif //STOCHASTICSIMULATION_SIMULATOR_H
