//
// Created by Ivik Hostrup on 6/1/2023.
//

#ifndef STOCHASTICSIMULATION_COVIDSIMULATOR_H
#define STOCHASTICSIMULATION_COVIDSIMULATOR_H


#include <cstddef>
#include "Monitor.h"
#include "ChemicalSystem.h"

class CovidSimulator {
public:
    CovidSimulator(size_t N) : m_N(N) {}

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

        system.AddSpecies("S", S0);
        system.AddSpecies("E", E0);
        system.AddSpecies("I", I0);
        system.AddSpecies("H", 0);
        system.AddSpecies("R", 0);



    };
private:
    size_t m_N;
};


#endif //STOCHASTICSIMULATION_COVIDSIMULATOR_H
