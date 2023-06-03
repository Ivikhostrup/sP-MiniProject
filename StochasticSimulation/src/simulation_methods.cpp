#include <future>
#include "CovidSimulator.h"
#include "SpeciesQuantityMonitorCallBack.h"
#include "CircadianSimulator.h"
#include "SimpleSimulator.h"

//
// Created by Ivik Hostrup on 6/3/2023.
//

void plotSimple(){
    std::vector<std::string> speciesToMonitor = {"A", "B", "C"};
    SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
    Monitor monitor(speciesMonitorCallBack);

    SimpleSimulator simulator(1000);
    simulator.RunFirstSimulation(monitor);
    monitor.GetCallback().CreatePlot();
};

void plotCircadian(){
    std::vector<std::string> speciesToMonitor = {"A", "R", "C"};
    SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
    Monitor monitor(speciesMonitorCallBack);

    CircadianSimulator simulator(100);
    simulator.RunSimulation(monitor);
    monitor.GetCallback().CreatePlot();
};

void plotCovid(double N = 10000){
    std::vector<std::string> speciesToMonitor = {"S", "E", "I","H","R"};
    SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
    Monitor monitor(speciesMonitorCallBack);

    CovidSimulator simulator(N, 100);
    simulator.RunCovidSimulator(monitor);
    monitor.GetCallback().CreatePlot();
};

void multithreadedCovid(size_t numSimulations = 20, size_t numThreads = std::thread::hardware_concurrency()){
    std::vector<std::string> speciesToMonitor = {"S", "E", "I","H","R"};


    std::vector<std::future<double>> futures(numSimulations);

    for(size_t i = 0; i < numSimulations; ++i) {
        futures[i] = std::async(std::launch::async, [&speciesToMonitor] {
            // Create a new callback and monitor for each thread
            SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
            Monitor monitor(speciesMonitorCallBack);

            // Create a new simulator for each thread
            CovidSimulator simulator(10000, 100);
            simulator.RunCovidSimulator(monitor);

            // Compute and return the peak hospitalized number
            return speciesMonitorCallBack.GetPeak("H");
        });
    }

    std::vector<double> peakValues(numSimulations);
    for (size_t i = 0; i < numSimulations; ++i) {
        peakValues[i] = futures[i].get();
    }

    double mean = std::accumulate(peakValues.begin(), peakValues.end(), 0.0) / numSimulations;
    //std::cout << "Mean peak hospitalized number: " << mean << std::endl;
}