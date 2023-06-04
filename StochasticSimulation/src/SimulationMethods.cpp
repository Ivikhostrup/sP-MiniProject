//
// Created by Ivik Hostrup.
//


#include <future>
#include "CovidSimulator.h"
#include "SpeciesQuantityMonitorCallBack.h"
#include "CircadianSimulator.h"
#include "SimpleSimulator.h"

void PlotSimple(){
    std::vector<std::string> speciesToMonitor = {"A", "B", "C"};
    SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
    Monitor monitor(speciesMonitorCallBack);

    SimpleSimulator simulator(1000);
    simulator.RunFirstSimulation(monitor);
    monitor.GetCallback().CreatePlot("Simple Simulation");
};

void PlotCircadian(){
    std::vector<std::string> speciesToMonitor = {"A", "R", "C"};
    SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
    Monitor monitor(speciesMonitorCallBack);

    CircadianSimulator simulator(100);
    simulator.RunSimulation(monitor);
    monitor.GetCallback().CreatePlot("Circadian Simulation");
};

void PlotCovid(double N = 10000, const std::string& title = "Covid Simulation"){
    std::vector<std::string> speciesToMonitor = {"S", "E", "I","H","R"};
    SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
    Monitor monitor(speciesMonitorCallBack);

    CovidSimulator simulator(N, 100);
    simulator.RunCovidSimulator(monitor);

    auto [peak, mean] = speciesMonitorCallBack.GetPeakAndMean("H");

    std::cout << "Peak hospitalized: " << peak << std::endl;
    std::cout << "Mean hospitalized: " << mean << std::endl;

    monitor.GetCallback().CreatePlot(title);
};

void MultithreadedCovid(size_t numSimulations = 20, size_t numThreads = std::thread::hardware_concurrency()){
    std::vector<std::string> speciesToMonitor = {"S", "E", "I","H","R"};

    std::vector<std::future<std::pair<double, double>>> futures(numSimulations);

    for(size_t i = 0; i < numSimulations; ++i) {
        futures[i] = std::async(std::launch::async, [&speciesToMonitor] {
            // Create a new callback and monitor for each thread
            SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
            Monitor monitor(speciesMonitorCallBack);

            // Create a new simulator for each thread
            CovidSimulator simulator(10000, 100);
            simulator.RunCovidSimulator(monitor);

            // Compute and return the peak hospitalized number
            return speciesMonitorCallBack.GetPeakAndMean("H");
        });
    }

    std::vector<double> peakValues(numSimulations);
    for (size_t i = 0; i < numSimulations; ++i) {
        auto [peaks, _] = futures[i].get();
        peakValues[i] = peaks;
    }

    double meanPeakAcrossSimulations = std::accumulate(peakValues.begin(), peakValues.end(), 0.0) / numSimulations;

    std::cout << "Mean peak hospitalized number: " << meanPeakAcrossSimulations << std::endl;
}
