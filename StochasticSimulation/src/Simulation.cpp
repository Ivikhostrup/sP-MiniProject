//
// Created by Ivik Hostrup on 5/26/2023.
//

#include "Simulation.h"

std::ostream& operator<<(std::ostream& os, const Simulation& simulation) {
    for (const auto& reaction : simulation.m_reactions) {
        os << reaction << std::endl;
    }
    return os;
}