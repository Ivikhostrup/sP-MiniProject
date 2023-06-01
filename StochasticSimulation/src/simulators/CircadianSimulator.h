//
// Created by Ivik Hostrup on 5/30/2023.
//

#ifndef STOCHASTICSIMULATION_CIRCADIANSIMULATOR_H
#define STOCHASTICSIMULATION_CIRCADIANSIMULATOR_H


#include "../reactions/ChemicalSystem.h"
#include "../reporting/CsvWriter.h"

class CircadianSimulator {
public:
    CircadianSimulator(int numTrajectories, size_t endTime)
        : m_numTrajectories(numTrajectories), m_endTime(endTime) {}

    template<typename CallBackType>
    void RunSimulation(Monitor<CallBackType>& monitor) {
        ChemicalSystem system;

        auto alphaA = 50.0;
        auto alpha_A = 500.0;
        auto alphaR = 0.01;
        auto alpha_R = 50.0;
        auto betaA = 50.0;
        auto betaR = 5.0;
        auto gammaA = 1.0;
        auto gammaR = 1.0;
        auto gammaC = 2.0;
        auto deltaA = 1.0;
        auto deltaR = 0.2;
        auto deltaMA = 10.0;
        auto deltaMR = 0.5;
        auto thetaA = 50.0;
        auto thetaR = 100.0;

        auto DA = system.AddSpecies("DA", 1);
        auto D_A = system.AddSpecies("D_A", 0);
        auto DR = system.AddSpecies("DR", 1);
        auto D_R = system.AddSpecies("D_R", 0);
        auto MA = system.AddSpecies("MA", 0);
        auto MR = system.AddSpecies("MR", 0);
        auto A = system.AddSpecies("A", 0);
        auto R = system.AddSpecies("R", 0);
        auto C = system.AddSpecies("C", 0);
        auto env = system.AddSpecies("env", 0);

        system.AddReaction(A + DA >>= D_A, gammaA);
        system.AddReaction(D_A >>= DA + A, thetaA);
        system.AddReaction(A + DR >>= D_R, gammaR);
        system.AddReaction(D_R >>= DR + A, thetaR);
        system.AddReaction(D_A >>= MA + D_A, alpha_A);
        system.AddReaction(DA >>= MA + DA, alphaA);
        system.AddReaction(D_R >>= MR + D_R, alpha_R);
        system.AddReaction(DR >>= MR + DR, alphaR);
        system.AddReaction(MA >>= MA + A, betaA);
        system.AddReaction(MR >>= MR + R, betaR);
        system.AddReaction(A + R >>= C, gammaC);
        system.AddReaction(C >>= R, deltaA);
        system.AddReaction(A >>= env, deltaA);
        system.AddReaction(R >>= env, deltaR);
        system.AddReaction(MA >>= env, deltaMA);
        system.AddReaction(MR >>= env, deltaMR);


        std::vector<std::string> speciesToMonitor = monitor.GetCallback().GetMonitoredSpecies();
        std::vector<std::vector<double>> runningTotals(speciesToMonitor.size());
        std::vector<std::vector<double>> counts(speciesToMonitor.size());

        for (int i = 0; i < m_numTrajectories; ++i) {
            system.Reset(); // Reset system to initial state

            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            system.Simulate(m_endTime, monitor); // Run simulation
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
    int m_numTrajectories;
    size_t m_endTime;
    std::vector<std::vector<double>> m_signals;
};


#endif //STOCHASTICSIMULATION_CIRCADIANSIMULATOR_H
