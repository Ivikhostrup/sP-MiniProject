//
// Created by Ivik Hostrup on 5/26/2023.
//

#ifndef STOCHASTICSIMULATION_SYSTEM_H
#define STOCHASTICSIMULATION_SYSTEM_H


#include <vector>
#include "Reaction.h"

class System {
public:
    void Simulate();
    std::shared_ptr<Species> AddSpecies(const std::string& name, const size_t& initial_amount);
    void AddReaction(const Reaction& reaction, const size_t& rate_constant);
    [[nodiscard]] std::vector<std::shared_ptr<Reaction>> get_reactions() const;

    friend std::ostream& operator<<(std::ostream& os, const System& system);
private:
    std::vector<std::shared_ptr<Species>> m_species;
    std::vector<std::shared_ptr<Reaction>> m_reactions;
};




#endif //STOCHASTICSIMULATION_SYSTEM_H
