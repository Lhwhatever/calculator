#ifndef TOKENS__PACKAGE_H_
#define TOKENS__PACKAGE_H_

#include <map>
#include <memory>

#include "operatorToken.h"
#include "values/valueToken.h"

using OperatorTokenSP = std::shared_ptr<OperatorToken>;
using OperatorMap = std::map<std::string, OperatorTokenSP>;

class Package {
   public:
    const std::string NAME;
    OperatorMap latexMap;
    OperatorMap plainMap;
    static Package basePackage;

   public:
    Package(std::string);

   public:
    bool addOperator(const std::string& reprPlain, const std::string& reprLaTeX,
                     const int arity, const int precedence);
};

#endif