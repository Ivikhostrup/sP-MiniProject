//
// Created by Ivik Hostrup on 6/3/2023.
//

#ifndef STOCHASTICSIMULATION_SIMULATION_METHODS_H
#define STOCHASTICSIMULATION_SIMULATION_METHODS_H

#include <string>
#include <vector>
#include <thread>
#include "SpeciesQuantityMonitorCallBack.h"
#include "CircadianSimulator.h"
#include "SimpleSimulator.h"
#include "CovidSimulator.h"
#include "plot.hpp"

void plotSimple();
void plotCircadian();
void plotCovid(double N = 10000);
void multithreadedCovid(size_t numSimulations = 20, size_t numThreads = std::thread::hardware_concurrency());

#endif //STOCHASTICSIMULATION_SIMULATION_METHODS_H
