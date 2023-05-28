//
// Created by Ivik Hostrup on 5/28/2023.
//

#ifndef STOCHASTICSIMULATION_SYMBOLTABLE_H
#define STOCHASTICSIMULATION_SYMBOLTABLE_H

#include <string>
#include <memory>
#include <unordered_map>

template <typename T>
class SymbolTable {
public:
    void AddSymbol(std::string& name, const std::shared_ptr<T>& object);
    std::shared_ptr<T> GetSymbol(std::string& name);

private:
    std::unordered_map<std::string, std::shared_ptr<T>> m_symbol_table;
};

template<typename T>
void SymbolTable<T>::AddSymbol(std::string &name, const std::shared_ptr<T> &object) {
    m_symbol_table[name] = object;
}


#endif //STOCHASTICSIMULATION_SYMBOLTABLE_H
