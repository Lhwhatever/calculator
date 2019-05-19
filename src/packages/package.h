#ifndef TOKENS__PACKAGES__PACKAGE_H_
#define TOKENS__PACKAGES__PACKAGE_H_

#include <map>
#include <memory>

#include "../values/valueToken.h"
#include "operatorToken.h"

using OperatorTokenSP = std::shared_ptr<OperatorToken>;
using OperatorTokenWP = std::weak_ptr<OperatorToken>;
using OperatorMap = std::map<std::string, OperatorTokenSP>;

class Package {
   public:
    const std::string NAME;

    static Package basePackage;

   private:
    OperatorMap latexMap;
    OperatorMap plainMap;

   public:
    Package(std::string);

   public:
    bool addOperator(const std::string& reprPlain, const std::string& reprLaTeX,
                     const int arity, const int precedence);
    bool addOperator(const std::string& reprLaTeX, const int arity,
                     const int precedence);

    OperatorTokenWP getOperatorByPlainRepr(const std::string&);
    OperatorTokenWP getOperatorByLaTeXRepr(const std::string&);
};

#endif