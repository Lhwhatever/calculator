#include "package.h"

#include <utility>

Package::Package(std::string name) : NAME{name}, latexMap{}, plainMap{} {}

bool Package::addOperator(const std::string& reprPlain,
                          const std::string& reprLaTeX, const int arity,
                          const int precedence) {
    auto token = std::make_shared<OperatorToken>(reprPlain, reprLaTeX, arity,
                                                 precedence);

    plainMap.insert_or_assign(reprPlain, token);
    latexMap.insert_or_assign(reprLaTeX, token);
};