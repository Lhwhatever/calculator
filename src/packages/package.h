#ifndef TOKENS__PACKAGES__PACKAGE_H_
#define TOKENS__PACKAGES__PACKAGE_H_

#include <map>
#include <memory>

#include "../tokens/operators/operatorToken.h"

using OperatorTokenSP = std::shared_ptr<OperatorToken>;
using OperatorTokenWP = std::weak_ptr<OperatorToken>;
using OperatorMap = std::map<std::string, OperatorTokenSP>;
using Runnable = std::function<void()>;

class Package {
   public:
    const std::string NAME;

    static Package basePackage;

   private:
    OperatorMap latexMap;
    OperatorMap plainMap;
    Runnable onInit;
    Runnable onLoad;

   public:
    Package(std::string, Runnable onInit = []() {}, Runnable onLoad = []() {});

   public:
    bool addOperator();

    OperatorTokenWP getOperatorByPlainRepr(const std::string&);
    OperatorTokenWP getOperatorByLaTeXRepr(const std::string&);
};

#endif