#include "package.h"

#include <string.h>
#include <stdexcept>
#include <utility>

#include "../except/illegalOverrideException.h"

std::map<const std::string, PackageR> Package::packages{};

Package::Package(const std::string& name, Callback onInit, Callback onPreload,
                 Callback onLoad, Callback onReload)
    : onInit{onInit},
      onPreload{onPreload},
      onLoad{onLoad},
      onReload{onReload},
      NAME{name} {}

bool Package::hasOperatorWithName(const FuncSet::FuncType opType,
                                  const std::string& name) {
    auto& map{functions.getRelevant(opType)};
    return map.find(name) != map.end();
}

FuncTokenSP Package::createOp(FTMap& map, const std::string& name,
                              const unsigned short arity, const short precLevel,
                              const Precedence::Associativity assoc,
                              const std::string& symbol,
                              std::string symbolRPN) {
    if (map.find(symbol) != map.end())
        throw IllegalOverrideException{"operator with symbol " + name};

    if (symbolRPN == "") symbolRPN = symbol;
    if (functions.opRPN.find(symbolRPN) != functions.opRPN.end())
        throw IllegalOverrideException{"operator with RPN symbol " + name};

    auto ft{std::make_shared<FuncToken>(name, arity, precLevel, assoc)};

    map.try_emplace(symbol, ft);
    functions.opRPN.try_emplace(symbolRPN, ft);
    return ft;
}

FuncTokenSP Package::createPrefixOperator(const std::string& name,
                                          const short precLevel,
                                          const std::string& symbol,
                                          const std::string& symbolRPN) {
    return createOp(functions.opPrefix, name, 1u, precLevel,
                    Precedence::ASSOC_R2L, symbol, symbolRPN);
}

FuncTokenSP Package::createPostfixOperator(const std::string& name,
                                           const short precLevel,
                                           const std::string& symbol,
                                           const std::string& symbolRPN) {
    return createOp(functions.opPostfix, name, 1u, precLevel,
                    Precedence::ASSOC_L2R, symbol, symbolRPN);
}

FuncTokenSP Package::createInfixOperator(const std::string& name,
                                         const short precLevel,
                                         const Precedence::Associativity assoc,
                                         const std::string& symbol,
                                         const std::string& symbolRPN) {
    return createOp(functions.opInfix, name, 2u, precLevel, assoc, symbol,
                    symbolRPN);
}

bool Package::hasOperatorWithSymbol(const FuncSet::FuncType ftype,
                                    const std::string& symbol) const {
    auto& map{functions.getRelevant(ftype)};
    return map.find(symbol) != map.end();
}

bool Package::hasOperatorWithRPNSymbol(const std::string& symbolRPN) const {
    return functions.opRPN.find(symbolRPN) != functions.opRPN.end();
}

FuncTokenSPC Package::getOperator(const FuncSet::FuncType ftype,
                                  const std::string& symbol) const {
    return functions.getRelevant(ftype).at(symbol);
}

FuncTokenSPC Package::getOperator(const std::string& symbolRPN) const {
    return functions.opRPN.at(symbolRPN);
}

FuncTokenSP Package::getOperator(const FuncSet::FuncType ftype,
                                 const std::string& symbol) {
    return functions.getRelevant(ftype).at(symbol);
}

FuncTokenSP Package::getOperator(const std::string& symbolRPN) {
    return functions.opRPN.at(symbolRPN);
}

void Package::init(const Settings& s) { onInit(*this, s); }
void Package::preload(const Settings& s) { onPreload(*this, s); }
void Package::load(const Settings& s) { onLoad(*this, s); }
void Package::reload(const Settings& s) { onReload(*this, s); }

bool Package::add(Package& p) {
    std::cout << p.NAME << '\n';
    return packages.try_emplace(p.NAME, std::ref(p)).second;
}