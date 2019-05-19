#ifndef TOKENS__PACKAGES__PACKAGE_H_
#define TOKENS__PACKAGES__PACKAGE_H_

#include <map>

#include "../tokens/operators/operatorToken.h"

using OperatorTokenR = std::reference_wrapper<OperatorToken>;
using OperatorMap = std::map<std::string, OperatorTokenR>;

class Package;

namespace {
using byte = unsigned char;
using Callback = std::function<void(Package)>;
using PackageR = std::reference_wrapper<Package>;
void pass(Package) {}
}  // namespace

class Package {
   public:
    const std::string NAME;

    static Package basePackage;
    static std::map<const std::string, PackageR> packages;

   private:
    OperatorMap latexMap;
    OperatorMap plainMap;
    Callback onInit;
    Callback onPreload;
    Callback onLoad;

   public:
    Package(std::string, Callback onInit = pass, Callback onPreload = pass,
            Callback onLoad = pass);

   public:
    byte addOperator(const OperatorToken&);

    OperatorToken& getOperatorByPlainRepr(const std::string&);
    OperatorToken& getOperatorByLaTeXRepr(const std::string&);
};

#endif