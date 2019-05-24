#include "package.h"

#include <string.h>
#include <stdexcept>
#include <utility>

std::map<const std::string, PackageR> Package::packages{};

Package::Package(std::string name, Callback onInit, Callback onPreload,
                 Callback onLoad)
    : NAME{name}, onInit{onInit}, onPreload{onPreload}, onLoad{onLoad} {
    // packages.insert_or_assign(NAME, std::ref(*this));
}

void Package::addOperator(OperatorTokenSP& oper) {
    mapOper.emplace(oper->getIdentifier(), oper);
}

bool Package::hasOperator(const std::string& id) const {
    return mapOper.find(id) != mapOper.end();
}

bool Package::hasOperator(const std::string& id, int arity) const {
    if (!hasOperator(id)) return false;

    auto [it, end] = mapOper.equal_range(id);
    while (it != end) {
        if (it->second->ARITY == arity) return true;
        ++it;
    }
    return false;
}

OperatorToken& Package::getOperator(const std::string& id, int arity) const {
    auto [it, end] = mapOper.equal_range(id);
    while (it != end) {
        if (it->second->ARITY == arity) return *it->second;
        ++it;
    }
    throw std::out_of_range("no such operator");
}

std::string Package::getName() const { return NAME; }

void Package::init(const Settings& s) { onInit(*this, s); }
void Package::preload(const Settings& s) { onPreload(*this, s); }
void Package::load(const Settings& s) { onLoad(*this, s); }

bool Package::add(Package& p) {
    auto [it, result] = packages.try_emplace(p.getName(), std::ref(p));
    return result;
}