//
// Created by Ivik Hostrup.
// Container for all simulation methods
// Part of all requirements
//

#ifndef STOCHASTICSIMULATION_SIMULATIONMETHODS_H
#define STOCHASTICSIMULATION_SIMULATIONMETHODS_H

#include <string>
#include <vector>
#include <thread>
#include "SpeciesQuantityMonitorCallBack.h"
#include "CircadianSimulator.h"
#include "SimpleSimulator.h"
#include "CovidSimulator.h"
#include "plot.hpp"

void PlotSimple();
void PlotCircadian();
void PlotCovid(double N = 10000);
void MultithreadedCovid(size_t numSimulations = 20, size_t numThreads = std::thread::hardware_concurrency());

#endif //STOCHASTICSIMULATION_SIMULATIONMETHODS_H
