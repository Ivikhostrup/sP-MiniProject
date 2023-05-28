//
// Created by Ivik Hostrup on 5/28/2023.
//

#ifndef STOCHASTICSIMULATION_SYMBOLTABLE_H
#define STOCHASTICSIMULATION_SYMBOLTABLE_H

#include <string>
#include <memory>
#include <unordered_map>
#include <stdexcept>

template <typename T>
class SymbolTable {
public:
    void AddSymbol(const std::string& name, const std::shared_ptr<T>& object);
    std::shared_ptr<T> GetSymbol(const std::string& name);
    const std::unordered_map<std::string, std::shared_ptr<T>>& GetAllSymbols() const;

private:
    std::unordered_map<std::string, std::shared_ptr<T>> m_symbol_table;
};

template<typename T>
std::shared_ptr<T> SymbolTable<T>::GetSymbol(const std::string &name) {
    auto item = m_symbol_table.find(name);
    if (item != m_symbol_table.end()) {
        return item->second;
    } else {
        throw std::runtime_error("Symbol not found");
    }
}

template<typename T>
const std::unordered_map<std::string, std::shared_ptr<T>>& SymbolTable<T>::GetAllSymbols() const {
    return m_symbol_table;
}

template<typename T>
void SymbolTable<T>::AddSymbol(const std::string &name, const std::shared_ptr<T> &object) {
    m_symbol_table[name] = object;
}


#endif //STOCHASTICSIMULATION_SYMBOLTABLE_H
