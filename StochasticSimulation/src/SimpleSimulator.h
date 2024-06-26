//
// Created by Ivik Hostrup.
// Simple simulation class that can be used to run a simulation with a simple chemical system.
// Requirement 4.
//

#ifndef STOCHASTICSIMULATION_SIMPLESIMULATOR_H
#define STOCHASTICSIMULATION_SIMPLESIMULATOR_H

#include <cstddef>
#include "Monitor.h"
#include "ChemicalSystem.h"
#include "CsvWriter.h"
#include "plot.hpp"

class SimpleSimulator {
public:
    SimpleSimulator(size_t endTime) : m_endTime(endTime) {}

    template<typename CallBackType>
    void RunFirstSimulation(Monitor<CallBackType>& monitor) {
        ChemicalSystem system;

        auto A = system.AddSpecies("A", 100);
        auto B = system.AddSpecies("B", 0);
        auto C = system.AddSpecies("C", 1);

        system.AddReaction(A + C >>= B + C, 0.001);

        std::vector<std::string> speciesToMonitor = monitor.GetCallback().GetMonitoredSpecies();
        system.Simulate(m_endTime, monitor);
    }

    template<typename CallBackType>
    void RunSecondSimulation(Monitor<CallBackType>& monitor) {
        ChemicalSystem system;

        auto A = system.AddSpecies("A", 100);
        auto B = system.AddSpecies("B", 0);
        auto C = system.AddSpecies("C", 2);

        system.AddReaction(A + C >>= B + C, 0.001);

        system.Simulate(m_endTime, monitor, false);
    }

    template<typename CallBackType>
    void RunThirdSimulation(Monitor<CallBackType>& monitor) {
        ChemicalSystem system;

        auto A = system.AddSpecies("A", 50);
        auto B = system.AddSpecies("B", 50);
        auto C = system.AddSpecies("C", 1);

        system.AddReaction(A + C >>= B + C, 0.001);

        system.Simulate(m_endTime, monitor, false);
    }

private:
    size_t m_endTime;
    std::vector<std::vector<double>> m_signals;
};


#endif //STOCHASTICSIMULATION_SIMPLESIMULATOR_H
