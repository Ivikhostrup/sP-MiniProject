//
// Created by Ivik Hostrup.
// CSV writer class that can be used to write the results of a simulation to a csv file
// Early implementation to satisfy requirement 6.
//

#ifndef STOCHASTICSIMULATION_CSVWRITER_H
#define STOCHASTICSIMULATION_CSVWRITER_H


#include <string>
#include <vector>

class CsvWriter {
public:
    CsvWriter(const std::string& filename, const std::vector<std::string>& speciesNames)
        : m_filename(filename), m_species_names(speciesNames) {}

    void WriteToCsv(const std::vector<double>& timepoints, const std::vector<std::vector<double>>& signals) const;
private:
    const std::string m_filename;
    const std::vector<std::string> m_species_names;
};


#endif //STOCHASTICSIMULATION_CSVWRITER_H
