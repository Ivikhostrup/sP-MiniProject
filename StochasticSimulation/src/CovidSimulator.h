//
// Created by Ivik Hostrup.
// Covid simulator class that can be used to simulate the spread of covid-19
// Subtask A.2
//

#ifndef STOCHASTICSIMULATION_COVIDSIMULATOR_H
#define STOCHASTICSIMULATION_COVIDSIMULATOR_H


#include <cstddef>
#include "Monitor.h"
#include "ChemicalSystem.h"
#include "CsvWriter.h"
#include "plot.hpp"

class CovidSimulator {
public:
    CovidSimulator(size_t N, size_t endTime) : m_N(N), m_endTime(endTime) {}

    template<typename CallBackType>
    void RunCovidSimulator(Monitor<CallBackType>& monitor){
        ChemicalSystem system;

        const auto eps = 0.0009;
        const auto I0 = size_t(std::round(eps*m_N));
        const auto E0 = size_t(std::round(eps*m_N*15));
        const auto S0 = m_N-I0-E0;
        const auto R0 = 2.4;
        const auto alpha = 1.0 / 5.1;
        const auto gamma = 1.0 / 3.1;
        const auto beta = R0 * gamma;
        const auto P_H = 0.9e-3;
        const auto kappa = gamma * P_H*(1.0-P_H);
        const auto tau = 1.0/10.12;

        auto S = system.AddSpecies("S", S0);
        auto E = system.AddSpecies("E", E0);
        auto I = system.AddSpecies("I", I0);
        auto H = system.AddSpecies("H", 0);
        auto R = system.AddSpecies("R", 0);

        system.AddReaction(S+I >>= E+I, beta/m_N);
        system.AddReaction(E >>= I, alpha);
        system.AddReaction(I >>= R, gamma);
        system.AddReaction(I >>= H, kappa);
        system.AddReaction(H >>= R, tau);

        system.Simulate(m_endTime, monitor);
    };
private:
    size_t m_N;
    size_t m_endTime;
    std::vector<std::vector<double>> m_signals;
};


#endif //STOCHASTICSIMULATION_COVIDSIMULATOR_H
