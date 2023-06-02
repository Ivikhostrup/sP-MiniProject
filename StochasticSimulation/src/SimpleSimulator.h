//
// Created by Ivik Hostrup on 6/1/2023.
//

#ifndef STOCHASTICSIMULATION_SIMPLESIMULATOR_H
#define STOCHASTICSIMULATION_SIMPLESIMULATOR_H

#include <cstddef>
#include "Monitor.h"
#include "ChemicalSystem.h"
#include "CsvWriter.h"
#include "plot.hpp"

class SimpleSimulator {
public:
    SimpleSimulator(size_t endTime) : m_endTime(endTime) {}

    template<typename CallBackType>
    void RunFirstSimulation(Monitor<CallBackType>& monitor) {
        ChemicalSystem system;

        auto A = system.AddSpecies("A", 100);
        auto B = system.AddSpecies("B", 0);
        auto C = system.AddSpecies("C", 1);

        system.AddReaction(A + C >>= B + C, 0.001);

        std::vector<std::string> speciesToMonitor = monitor.GetCallback().GetMonitoredSpecies();
        system.Simulate(m_endTime, monitor, false);

        auto signals = monitor.GetCallback().GetSignals();
        auto time = monitor.GetCallback().GetTimepoints();

        // Create map for species and their quantities
        std::unordered_map<std::string, std::vector<double>> speciesQuantities;

        for(size_t i = 0; i < speciesToMonitor.size(); ++i) {
            speciesQuantities[speciesToMonitor[i]] = signals[i];
        }

        // Create plot instance
        Plot plot("Simple Simulation", "Time", "Quantity", 800, 600);

        // Add data to plot
        plot.plot_data(time, speciesQuantities);

        // Show the plot
        plot.process();
        plot.save_to_png("SimpleSimulation.png");
    }

    template<typename CallBackType>
    void RunSecondSimulation(Monitor<CallBackType>& monitor) {
        ChemicalSystem system;

        auto A = system.AddSpecies("A", 100);
        auto B = system.AddSpecies("B", 0);
        auto C = system.AddSpecies("C", 2);

        system.AddReaction(A + C >>= B + C, 0.001);

        std::vector<std::string> speciesToMonitor = monitor.GetCallback().GetMonitoredSpecies();
        system.Simulate(m_endTime, monitor, false);

        auto signals = monitor.GetCallback().GetSignals();
        auto time = monitor.GetCallback().GetTimepoints();

        // Create map for species and their quantities
        std::unordered_map<std::string, std::vector<double>> speciesQuantities;

        for(size_t i = 0; i < speciesToMonitor.size(); ++i) {
            speciesQuantities[speciesToMonitor[i]] = signals[i];
        }

        // Create plot instance
        Plot plot("Simple Simulation", "Time", "Quantity", 800, 600);

        // Add data to plot
        plot.plot_data(time, speciesQuantities);

        // Show the plot
        plot.process();
        plot.save_to_png("SimpleSimulation.png");
    }

    template<typename CallBackType>
    void RunThirdSimulation(Monitor<CallBackType>& monitor) {
        ChemicalSystem system;

        auto A = system.AddSpecies("A", 50);
        auto B = system.AddSpecies("B", 50);
        auto C = system.AddSpecies("C", 1);

        system.AddReaction(A + C >>= B + C, 0.001);

        std::vector<std::string> speciesToMonitor = monitor.GetCallback().GetMonitoredSpecies();
        system.Simulate(m_endTime, monitor, false);

        auto signals = monitor.GetCallback().GetSignals();
        auto time = monitor.GetCallback().GetTimepoints();

        // Create map for species and their quantities
        std::unordered_map<std::string, std::vector<double>> speciesQuantities;

        for(size_t i = 0; i < speciesToMonitor.size(); ++i) {
            speciesQuantities[speciesToMonitor[i]] = signals[i];
        }

        // Create plot instance
        Plot plot("Simple Simulation", "Time", "Quantity", 800, 600);

        // Add data to plot
        plot.plot_data(time, speciesQuantities);

        // Show the plot
        plot.process();
        plot.save_to_png("SimpleSimulation.png");
    }

private:
    size_t m_endTime;
    std::vector<std::vector<double>> m_signals;
};


#endif //STOCHASTICSIMULATION_SIMPLESIMULATOR_H
