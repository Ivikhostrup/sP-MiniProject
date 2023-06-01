#include <iostream>
#include "Species.h"
#include "CombinedElements.h"
#include "Reaction.h"
#include "ChemicalSystem.h"
#include "SpeciesQuantityMonitorCallBack.h"
#include "CircadianSimulator.h"

int main() {
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


    std::vector<std::string> speciesToMonitor = {"A", "R", "C"};
    SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
    Monitor<SpeciesQuantityMonitorCallBack> monitor(speciesMonitorCallBack);

    CircadianSimulator simulator(system, 100, 100);
    simulator.RunSimulation(monitor);

    return 0;
}
