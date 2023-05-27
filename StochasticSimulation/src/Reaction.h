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
    Reaction add_reactant(const std::shared_ptr<Species>& species);
    Reaction add_product(const std::shared_ptr<Species>& species);
    void set_rate_constant(const size_t& rate_constant);

    [[nodiscard]] const std::vector<std::shared_ptr<Species>>& get_reactants() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Species>>& get_products() const;

    friend std::ostream& operator<<(std::ostream& os, const Reaction& reaction);
private:
    std::vector<std::shared_ptr<Species>> m_reactants;
    std::vector<std::shared_ptr<Species>> m_products;
    size_t m_rate_constant = 0;
};

Reaction operator>>=(const CombinedElements& combinedReactants, const std::shared_ptr<Species>& product);
Reaction operator>>=(const std::shared_ptr<Species>& reactant, const CombinedElements& combinedProducts);
Reaction operator>>=(const CombinedElements& combinedReactants, const CombinedElements& combinedProducts);
Reaction operator>>=(const std::shared_ptr<Species>& reactant, const std::shared_ptr<Species>& product);

#endif //STOCHASTICSIMULATION_REACTION_H
