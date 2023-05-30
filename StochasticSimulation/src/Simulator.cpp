//
// Created by Ivik Hostrup on 5/30/2023.
//

#include <chrono>
#include "Simulator.h"
#include "SpeciesQuantityMonitor.h"

void Simulator::RunSimulation(const std::vector<std::string>& speciesToMonitor) {
    m_signals.resize(speciesToMonitor.size());


    for (int i = 0; i < m_numTrajectories; ++i) {
        //m_system.Reset(); // Reset system to initial state


        // Create a new monitor for this trajectory
        SpeciesQuantityMonitor monitor(speciesToMonitor);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        m_system.Simulate(m_endTime, monitor); // Run simulation
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

        // Save signals at each time point
        const auto &signals = monitor.GetSignals();


        for (size_t j = 0; j < signals.size(); ++j) {
            m_signals[j].push_back(signals[j].back());
        }

    }

    auto averages = GetAverageSignals();
    for (auto avg : averages) {
        std::cout << "Average: " << avg << std::endl;
    }
}

double Simulator::ComputeAverageSignal(const std::vector<double>& signal) const {
    double avg = 0.0;
    for (const auto& element : signal) {
        avg += element;
    }
    return avg / signal.size();
}

std::vector<double> Simulator::GetAverageSignals() const {
    std::vector<double> avgSignals(m_signals.size());
    for (size_t i = 0; i < m_signals.size(); ++i) {
        avgSignals[i] = ComputeAverageSignal(m_signals[i]);
    }
    return avgSignals;
}





