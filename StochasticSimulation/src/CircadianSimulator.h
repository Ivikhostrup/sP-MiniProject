//
// Created by Ivik Hostrup on 5/30/2023.
//

#ifndef STOCHASTICSIMULATION_CIRCADIANSIMULATOR_H
#define STOCHASTICSIMULATION_CIRCADIANSIMULATOR_H


#include "ChemicalSystem.h"
#include "CsvWriter.h"
#include "Simulator.h"

class CircadianSimulator : public Simulator {
public:
    CircadianSimulator(ChemicalSystem& system, int numTrajectories, size_t endTime)
        : m_system(system), m_numTrajectories(numTrajectories), m_endTime(endTime) {}

    template<typename CallBackType>
    void RunSimulation(Monitor<CallBackType>& monitor) {
        std::vector<std::string> speciesToMonitor = monitor.GetCallback().GetMonitoredSpecies();
        std::vector<std::vector<double>> runningTotals(speciesToMonitor.size());
        std::vector<std::vector<double>> counts(speciesToMonitor.size());

        for (int i = 0; i < m_numTrajectories; ++i) {
            m_system.Reset(); // Reset system to initial state

            // Create a new monitor for this trajectory


            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            m_system.Simulate(m_endTime, monitor); // Run simulation
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

            // Save signals at each time point
            const auto &signals = monitor.GetCallback().GetSignals();

            for (size_t j = 0; j < signals.size(); ++j) {
                if (i == 0) {
                    // Initialize running totals with the value of the signals from the first trajectory and count by 1
                    runningTotals[j] = signals[j];
                    counts[j] = std::vector<double>(signals[j].size(), 1);
                } else {
                    // Update running totals and counts
                    for (size_t k = 0; k < signals[j].size(); ++k) {
                        runningTotals[j][k] += signals[j][k];
                        counts[j][k] += 1;
                    }
                }
            }
        }

        // Resize the outer vector to match the number of species we're monitoring
        m_signals.resize(runningTotals.size());

        // Calculate the average signal for each trajectory
        for (size_t j = 0; j < runningTotals.size(); ++j) {
            // Resize the inner vector to match the number of time points for which we have data
            m_signals[j].resize(runningTotals[j].size());

            for (size_t k = 0; k < runningTotals[j].size(); ++k) {
                m_signals[j][k] = runningTotals[j][k] / counts[j][k];
            }
        }

        CsvWriter writer("test.csv", speciesToMonitor);
        writer.WriteToCsv(m_signals);
    }

    std::vector<std::vector<double>> GetAverageSignals() const;



private:
    ChemicalSystem& m_system;
    int m_numTrajectories;
    size_t m_endTime;
    std::vector<std::vector<double>> m_signals;
};


#endif //STOCHASTICSIMULATION_CIRCADIANSIMULATOR_H
