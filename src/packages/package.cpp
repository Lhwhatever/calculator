#include "package.h"

#include <string.h>
#include <stdexcept>
#include <utility>

Package::Package(std::string name) : NAME{name}, latexMap{}, plainMap{} {}

bool Package::addOperator(const std::string& reprPlain,
                          const std::string& reprLaTeX, const int arity,
                          const int precedence) {
    auto token = std::make_shared<OperatorToken>(reprPlain, reprLaTeX, arity,
                                                 precedence);

    // if reprPlain is not the empty string, add it to the map
    if (reprPlain.compare("")) plainMap.insert_or_assign(reprPlain, token);
    latexMap.insert_or_assign(reprLaTeX, token);
}

bool Package::addOperator(const std::string& reprLaTeX, const int arity,
                          const int precedence) {
    addOperator("", reprLaTeX, arity, precedence);
}

OperatorTokenWP Package::getOperatorByPlainRepr(const std::string& repr) {
    try {
        return plainMap.at(repr);
    } catch (std::out_of_range) {
        return {};
    }
}

OperatorTokenWP Package::getOperatorByLaTeXRepr(const std::string& repr) {
    try {
        return latexMap.at(repr);
    } catch (std::out_of_range) {
        return {};
    }
}