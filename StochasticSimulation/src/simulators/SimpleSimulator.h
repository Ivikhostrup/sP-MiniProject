//
// Created by Ivik Hostrup on 6/1/2023.
//

#ifndef STOCHASTICSIMULATION_SIMPLESIMULATOR_H
#define STOCHASTICSIMULATION_SIMPLESIMULATOR_H

#include <cstddef>
#include "../monitors/Monitor.h"
#include "../reactions/ChemicalSystem.h"
#include "../reporting/CsvWriter.h"

class SimpleSimulator {
public:
    SimpleSimulator(size_t endTime) : m_endTime(endTime) {}

    template<typename CallBackType>
    void RunSimulation(Monitor<CallBackType>& monitor) {
        ChemicalSystem system;

        auto A = system.AddSpecies("A", 100);
        auto B = system.AddSpecies("B", 0);
        auto C = system.AddSpecies("C", 1);

        system.AddReaction(A + C >>= B + C, 0.001);

        std::vector<std::string> speciesToMonitor = monitor.GetCallback().GetMonitoredSpecies();
        system.Simulate(m_endTime, monitor, false);

        const auto &signals = monitor.GetCallback().GetSignals();

        for (const auto& signal : signals) {
            m_signals.push_back(signal);
        }

        CsvWriter writer("simpleSimulator1.csv", speciesToMonitor);
        writer.WriteToCsv(m_signals);
    }


private:
    size_t m_endTime;
    std::vector<std::vector<double>> m_signals;
};


#endif //STOCHASTICSIMULATION_SIMPLESIMULATOR_H
