//
// Created by Ivik Hostrup on 5/26/2023.
//

#ifndef STOCHASTICSIMULATION_SPECIES_H
#define STOCHASTICSIMULATION_SPECIES_H


#include <string>

class Species {
public:
    Species(std::string name, int initialQuantity):
            m_name(std::move(name)), m_quantity(initialQuantity) {}

    //std::string getName() { return name; } Maybe necessary later
    //int getQuantity() { return quantity; }
private:
    std::string m_name;
    int m_quantity;
};


#endif //STOCHASTICSIMULATION_SPECIES_H
