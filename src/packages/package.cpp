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

bool Package::addOperator(OperatorTokenSP& oper) {
    auto [it, result] = mapOper.try_emplace(oper->getIdentifier(), oper);
    return result;
}

OperatorToken& Package::getOperator(const std::string& id) const {
    return *(mapOper.at(id));
}

std::string Package::getName() const { return NAME; }

void Package::init(const Settings& s) { onInit(*this, s); }
void Package::preload(const Settings& s) { onPreload(*this, s); }
void Package::load(const Settings& s) { onLoad(*this, s); }

bool Package::add(Package& p) {
    auto [it, result] = packages.try_emplace(p.getName(), std::ref(p));
    return result;
}