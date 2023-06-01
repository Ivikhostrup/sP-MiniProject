//
// Created by Ivik Hostrup on 5/30/2023.
//


#include <fstream>
#include "CircadianSimulator.h"
#include "SpeciesQuantityMonitorCallBack.h"
#include "CsvWriter.h"



std::vector<std::vector<double>> CircadianSimulator::GetAverageSignals() const {
    return m_signals;
}








