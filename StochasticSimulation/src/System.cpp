//
// Created by Ivik Hostrup on 5/26/2023.
//

#include <iostream>
#include "System.h"

// Ostream operator overload for System class
std::ostream& operator<<(std::ostream& os, const System& simulation) {
    for (const auto& reaction : simulation.m_reactions) {
        os << reaction << std::endl;
    }
    return os;
}

void System::Simulate() {

}

void System::AddSpecies(const std::string& name, int initialQuantity) {
    // Add species to vector of species
    m_species.push_back(Species(name, initialQuantity));
}
