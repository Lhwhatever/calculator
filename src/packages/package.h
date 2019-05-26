#ifndef TOKENS__PACKAGES__PACKAGE_H_
#define TOKENS__PACKAGES__PACKAGE_H_

#include <map>

#include "../settings.h"
#include "../tokens/operators/operatorToken.h"
#include "defaultPackages.h"

using OperatorTokenSP = std::shared_ptr<OperatorToken>;
using OperatorMap = std::multimap<std::string, OperatorTokenSP>;

class Package;

namespace {
using Callback = void (*)(Package&, const Settings&);
using PackageR = std::reference_wrapper<Package>;
void pass(Package&, const Settings&) {}
}  // namespace

class Package {
   private:
    const std::string NAME;
    static std::map<const std::string, PackageR> packages;
    static Package basePackage;

   private:
    OperatorMap mapOper;
    Callback onInit;
    Callback onPreload;
    Callback onLoad;
    Callback onReload;

   public:
    Package(std::string, Callback onInit = pass, Callback onPreload = pass,
            Callback onLoad = pass, Callback onReload = pass);

   public:
    static bool add(Package&);

    void addOperator(OperatorTokenSP&);
    std::string getName() const;

    bool hasOperator(const std::string& identifier) const;
    bool hasOperator(const std::string& identifier, unsigned int arity) const;
    int count(const std::string& identifier) const;
    OperatorToken& getOperator(const std::string& identifier,
                               unsigned int arity) const;

    void init(const Settings&);
    void preload(const Settings&);
    void load(const Settings&);
    void reload(const Settings&);

    friend class Session;
    friend void default_packages::add();
};

#endif