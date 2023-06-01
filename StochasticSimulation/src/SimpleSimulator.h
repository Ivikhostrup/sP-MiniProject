//
// Created by Ivik Hostrup on 6/1/2023.
//

#ifndef STOCHASTICSIMULATION_SIMPLESIMULATOR_H
#define STOCHASTICSIMULATION_SIMPLESIMULATOR_H

#include <cstddef>
#include "Monitor.h"
#include "ChemicalSystem.h"
#include "CsvWriter.h"

class SimpleSimulator {
public:
    SimpleSimulator(size_t endTime) : m_endTime(endTime) {}

    template<typename CallBackType>
    void RunSimulation(Monitor<CallBackType>& monitor) const {
        ChemicalSystem system;

        auto A = system.AddSpecies("A", 100);
        auto B = system.AddSpecies("B", 0);
        auto C = system.AddSpecies("C", 1);

        system.AddReaction(A + C >>= B + C, 0.001);

        std::vector<std::string> speciesToMonitor = monitor.GetCallback().GetMonitoredSpecies();
        system.Simulate(m_endTime, monitor, false);

        auto records = monitor.GetCallback().GetRecords();

        std::vector<std::string> headers = {"Time"};
        for(const auto& species : monitor.GetCallback().GetMonitoredSpecies()) {
            headers.push_back(species);
        }

        CsvWriter writer("simpleSimulator1.csv", headers);

        for (const auto& record : records) {
            std::vector<double> row;
            row.push_back(record.timestamp);

            for (size_t i = 0; i < monitor.GetCallback().GetMonitoredSpecies().size(); ++i) {
                const auto& species = monitor.GetCallback().GetMonitoredSpecies()[i];
                row.push_back(record.quantities.at(i));
            }

            writer.WriteRow(row);
        }
    }


private:
    size_t m_endTime;
    std::vector<std::vector<double>> m_signals;
};


#endif //STOCHASTICSIMULATION_SIMPLESIMULATOR_H
