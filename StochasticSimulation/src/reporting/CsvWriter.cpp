//
// Created by Ivik Hostrup on 6/1/2023.
//

#include <fstream>
#include "CsvWriter.h"

void CsvWriter::WriteToCsv(const std::vector<std::vector<double>>& signals) const {
    std::ofstream file;

    file.open(m_filename);
    // Write species names as header
    for (const auto& name : m_species_names) {
        file << name;
        if (&name != &m_species_names.back()) { // Check if not the last element to avoid trailing comma
            file << ',';
        }
    }
    file << '\n';

    // Write signals
    for (size_t t = 0; t < m_species_names[0].size(); ++t) {
        for (size_t j = 0; j < m_species_names.size(); ++j) {
            file << m_species_names[j][t];
            if (j < m_species_names.size() - 1) { // Check if not the last element to avoid trailing comma
                file << ',';
            }
        }
        file << '\n';
    }

    file.close();
}
