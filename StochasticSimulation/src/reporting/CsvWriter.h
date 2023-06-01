//
// Created by Ivik Hostrup on 6/1/2023.
//

#ifndef STOCHASTICSIMULATION_CSVWRITER_H
#define STOCHASTICSIMULATION_CSVWRITER_H


#include <string>
#include <vector>

class CsvWriter {
public:
    CsvWriter(const std::string& filename, const std::vector<std::string>& speciesNames)
        : m_filename(filename), m_species_names(speciesNames) {}

    void WriteToCsv(const std::vector<std::vector<double>>& signals) const;
private:
    const std::string& m_filename;
    const std::vector<std::string>& m_species_names;
};


#endif //STOCHASTICSIMULATION_CSVWRITER_H