//
// Created by Ivik Hostrup on 6/2/2023.
//

#include "doctest.h"
#include "../src/ChemicalSystem.h"

TEST_CASE("Testing SymbolTable class") {
    ChemicalSystem system;
    auto S = system.AddSpecies("S", 10);

    SUBCASE("Testing AddSymbol and GetSymbol") {
        SymbolTable<Species> table;
        table.AddSymbol("S", S);
        CHECK(table.GetSymbol("S")->GetQuantity() == 10);
    }

    SUBCASE("Testing GetAllSymbols") {
        SymbolTable<Species> table;
        table.AddSymbol("S", S);
        CHECK(table.GetAllSymbols().size() == 1);
    }
}
