//
// Created by Ivik Hostrup.
//

#include <fstream>
#include <iostream>
#include "CsvWriter.h"

void CsvWriter::WriteToCsv(const std::vector<double>& timepoints, const std::vector<std::vector<double>>& signals) const {
    std::ofstream file;

    file.open(m_filename);
    if (file.fail()) {
        std::cerr << "Failed to open file: " << m_filename << "\n";
        return;
    }
    // Write species names as header
    file << "Time,";
    for (const auto& name : m_species_names) {
        file << name;
        if (&name != &m_species_names.back()) { // Check if not the last element to avoid trailing comma
            file << ',';
        }
    }
    file << '\n';

    // Write signals
    for (size_t t = 0; t < signals[0].size(); ++t) {
        file << timepoints[t] << ',';
        for (size_t j = 0; j < signals.size(); ++j) {
            file << signals[j][t];
            if (j < signals.size() - 1) { // Check if not the last element to avoid trailing comma
                file << ',';
            }
        }
        file << '\n';
    }

    if (file.bad()) {
        std::cerr << "Failed to write to file: " << m_filename << "\n";
    }
    file.close();
}
