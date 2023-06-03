//
// Created by Ivik Hostrup on 5/30/2023.
//

#ifndef STOCHASTICSIMULATION_CIRCADIANSIMULATOR_H
#define STOCHASTICSIMULATION_CIRCADIANSIMULATOR_H


#include "ChemicalSystem.h"
#include "plot.hpp"


class CircadianSimulator {
public:
    CircadianSimulator(size_t endTime) : m_endTime(endTime) {}

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

        system.Simulate(m_endTime, monitor); // Run simulation

        auto signals = monitor.GetCallback().GetSignals();
        auto time = monitor.GetCallback().GetTimepoints();

        // Create map for species and their quantities
        std::unordered_map<std::string, std::vector<double>> speciesQuantities;
        auto monitoredSpecies = monitor.GetCallback().GetMonitoredSpecies();

        for(size_t i = 0; i < monitoredSpecies.size(); ++i) {
            speciesQuantities[monitoredSpecies[i]] = signals[i];
        }

        // Create plot instance
        Plot plot("Circadian Simulation", "Time", "Quantity", 800, 600);

        // Add data to plot
        plot.plot_data(time, speciesQuantities);

        // Show the plot
        plot.process();
        plot.save_to_png("CircadianSimulation.png");
    }

private:
    int m_numTrajectories;
    size_t m_endTime;
    std::vector<std::vector<double>> m_signals;
};


#endif //STOCHASTICSIMULATION_CIRCADIANSIMULATOR_H
