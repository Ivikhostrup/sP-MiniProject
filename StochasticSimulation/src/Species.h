//
// Created by Ivik Hostrup.
// Species class for representing a species in a chemical reaction
// Baseline to satisfy all requirements.
//

#ifndef STOCHASTICSIMULATION_SPECIES_H
#define STOCHASTICSIMULATION_SPECIES_H


#include <string>
#include <iostream>

class Species {
public:
    Species(std::string name, int initialQuantity):
            m_name(std::move(name)), m_quantity(initialQuantity) {}

    const std::string& GetName() const;
    const size_t& GetQuantity() const;
    void SetQuantity(const size_t& quantity);

    friend std::ostream& operator<<(std::ostream& os, const Species& species);
private:
    std::string m_name;
    size_t m_quantity;
};


#endif //STOCHASTICSIMULATION_SPECIES_H
