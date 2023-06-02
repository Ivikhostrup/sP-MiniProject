//
// Created by Ivik Hostrup on 5/30/2023.
//

#ifndef STOCHASTICSIMULATION_CIRCADIANSIMULATOR_H
#define STOCHASTICSIMULATION_CIRCADIANSIMULATOR_H


#include "ChemicalSystem.h"
#include "plot.hpp"


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
            system.Simulate(m_endTime, monitor, true); // Run simulation
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

            // Save signals at each time point
            const auto &signals = monitor.GetCallback().GetSignals();

            if (i == 0) {
                // Initialize running totals and counts with the same structure as signals
                runningTotals = std::vector<std::vector<double>>(signals.size());
                counts = std::vector<std::vector<double>>(signals.size());
            }

            for (size_t j = 0; j < signals.size(); ++j) {
                try {
                    if (i == 0) {
                        // Initialize running totals and counts for the first trajectory
                        runningTotals.at(j) = std::vector<double>(signals.at(j).size(), 0);
                        counts.at(j) = std::vector<double>(signals.at(j).size(), 0);
                    } else if (signals.at(j).size() > runningTotals.at(j).size()) {
                        // If signals[j] for the current trajectory has more elements than runningTotals[j] and counts[j],
                        // extend the size of runningTotals[j] and counts[j] to match that of signals[j].
                        runningTotals.at(j).resize(signals.at(j).size(), 0);
                        counts.at(j).resize(signals.at(j).size(), 0);
                    }

                    // Update running totals and counts
                    for (size_t k = 0; k < signals.at(j).size(); ++k) {
                        runningTotals.at(j).at(k) += signals.at(j).at(k);
                        counts.at(j).at(k) += 1;
                    }
                } catch (const std::out_of_range& e) {
                    std::cerr << "Out of Range error: " << e.what() << '\n';
                }
            }

            //print out running totals with species


            //monitor.GetCallback().Reset();
        }

        // Create map for species and their quantities
        std::unordered_map<std::string, std::vector<double>> quantetiesOfSpecies;

        // Now calculate the averages for each species and store them in quantetiesOfSpecies
        for(size_t i = 0; i < speciesToMonitor.size(); ++i) {
            std::vector<double> averageSignals(runningTotals.at(i).size());

            for (size_t j = 0; j < runningTotals.at(i).size(); ++j) {
                averageSignals.at(j) = runningTotals.at(i).at(j) / counts.at(i).at(j);
            }
            quantetiesOfSpecies[speciesToMonitor.at(i)] = averageSignals;
        }


        // Create plot instance
        Plot plot("Circadian Simulation", "Time", "Quantity", 800, 600);

        // Get timepoints from the monitor
        auto time = monitor.GetCallback().GetTimepoints();

        // Add data to plot
        plot.plot_data(time, quantetiesOfSpecies);

        // Show the plot
        plot.process();
        plot.save_to_png("CircadianSimulation.png");
    }

    std::vector<std::vector<double>> GetAverageSignals() const;



private:
    int m_numTrajectories;
    size_t m_endTime;
    std::vector<std::vector<double>> m_signals;
};


#endif //STOCHASTICSIMULATION_CIRCADIANSIMULATOR_H
