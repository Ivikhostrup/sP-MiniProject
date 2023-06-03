//
// Created by Ivik Hostrup on 6/2/2023.
//


#include "doctest.h"
#include "../src/ChemicalSystem.h"

TEST_CASE("Testing Reaction class") {
    ChemicalSystem system;
    auto S = system.AddSpecies("S", 10);
    auto E = system.AddSpecies("E", 20);
    auto I = system.AddSpecies("I", 30);

    auto constructedReaction = system.AddReaction(S+E >>= I, 0.5);

    SUBCASE("Testing AddReactant and get_reactants") {
        Reaction reaction;
        reaction.AddReactant(S);
        CHECK(reaction.get_reactants().GetCombinedSpecies().size() == 1);
    }

    SUBCASE("Testing AddProduct and get_products") {
        Reaction reaction;
        reaction.AddProduct(E);
        CHECK(reaction.get_products().GetCombinedSpecies().size() == 1);
    }

    SUBCASE("Testing reaction pretty print") {
        CHECK(constructedReaction->to_string() == "S + E -> I");
    }
}
