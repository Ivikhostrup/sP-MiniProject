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

    // function definition for increasing quantity
    void IncreaseQuantity();
    void DecreaseQuantity();

    friend std::ostream& operator<<(std::ostream& os, const Species& species);
private:
    std::string m_name;
    int m_quantity;
};

#endif //STOCHASTICSIMULATION_SPECIES_H
