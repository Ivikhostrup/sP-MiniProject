//
// Created by Ivik Hostrup on 5/30/2023.
//

#include <chrono>
#include <fstream>
#include "Simulator.h"
#include "SpeciesQuantityMonitor.h"

void Simulator::RunSimulation(const std::vector<std::string>& speciesToMonitor) {
    std::vector<std::vector<double>> runningTotals(speciesToMonitor.size());
    std::vector<std::vector<double>> counts(speciesToMonitor.size());

    for (int i = 0; i < m_numTrajectories; ++i) {
        m_system.Reset(); // Reset system to initial state

        // Create a new monitor for this trajectory
        SpeciesQuantityMonitor monitor(speciesToMonitor);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        m_system.Simulate(m_endTime, monitor); // Run simulation
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

        // Save signals at each time point
        const auto &signals = monitor.GetSignals();

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


}

std::vector<std::vector<double>> Simulator::GetAverageSignals() const {
    return m_signals;
}


void Simulator::WriteToCsv(const std::string &filename, const std::vector<std::string>& speciesNames) const {
    std::ofstream file;

    file.open(filename);
    // Write species names as header
    for (const auto& name : speciesNames) {
        file << name;
        if (&name != &speciesNames.back()) { // Check if not the last element to avoid trailing comma
            file << ',';
        }
    }
    file << '\n';

    // Write signals
    for (size_t t = 0; t < m_signals[0].size(); ++t) {
        for (size_t j = 0; j < m_signals.size(); ++j) {
            file << m_signals[j][t];
            if (j < m_signals.size() - 1) { // Check if not the last element to avoid trailing comma
                file << ',';
            }
        }
        file << '\n';
    }

    file.close();
}





