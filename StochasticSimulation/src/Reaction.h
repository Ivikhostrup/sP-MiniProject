//
// Created by Ivik Hostrup on 5/26/2023.
//

#ifndef STOCHASTICSIMULATION_REACTION_H
#define STOCHASTICSIMULATION_REACTION_H



#include <memory>
#include <vector>
#include "Species.h"
#include "CombinedElements.h"
#include <iostream>

class Reaction {
public:
    void add_reactant(const std::shared_ptr<Species>& species);
    void add_product(const std::shared_ptr<Species>& species);
    void set_rate_constant(const size_t& rate_constant);
    void set_delay(const size_t& delay);
    [[nodiscard]] size_t get_delay() const;
    [[nodiscard]] double compute_delay() const;


    [[nodiscard]] const CombinedElements& get_reactants() const;
    [[nodiscard]] const CombinedElements& get_products() const;

    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Reaction& reaction);
private:
    CombinedElements m_reactants;
    CombinedElements m_products;
    size_t m_rate_constant = 0;
    size_t m_delay = 0;
    void print_reaction(std::ostream& os) const;
};

Reaction operator>>=(const CombinedElements& combinedReactants, const std::shared_ptr<Species>& product);
Reaction operator>>=(const std::shared_ptr<Species>& reactant, const CombinedElements& combinedProducts);
Reaction operator>>=(const CombinedElements& combinedReactants, const CombinedElements& combinedProducts);
Reaction operator>>=(const std::shared_ptr<Species>& reactant, const std::shared_ptr<Species>& product);

#endif //STOCHASTICSIMULATION_REACTION_H
