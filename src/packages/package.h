#ifndef TOKENS__PACKAGES__PACKAGE_H_
#define TOKENS__PACKAGES__PACKAGE_H_

#include "../settings.h"
#include "../tokens/operators/funcSet.h"

class Package;

using Callback = void (*)(Package&, const Settings&);
using PackageR = std::reference_wrapper<Package>;

class Package {
    static std::map<const std::string, PackageR> packages;
    static Package basePackage;

    const Callback onInit;
    const Callback onPreload;
    const Callback onLoad;
    const Callback onReload;

    FuncSet functions;

   public:
    const std::string NAME;

    static void doNothing(Package&, const Settings&) {}

   public:
    Package(const std::string&, Callback onInit = doNothing,
            Callback onPreload = doNothing, Callback onLoad = doNothing,
            Callback onReload = doNothing);

   private:
    FuncTokenSP createOp(FTMap&, const std::string& name, unsigned short arity,
                         short precLevel, Precedence::Associativity assoc,
                         const std::string& symbol, std::string symbolRPN);

   public:
    static bool add(Package&);

    bool hasOperatorWithName(FuncSet::FuncType type, const std::string& name);
    FuncTokenSP createPrefixOperator(const std::string& name, short precLevel,
                                     const std::string& symbol,
                                     const std::string& symbolRPN = "");
    FuncTokenSP createPostfixOperator(const std::string& name, short precLevel,
                                      const std::string& symbol,
                                      const std::string& symbolRPN = "");
    FuncTokenSP createInfixOperator(const std::string& name, short precLevel,
                                    Precedence::Associativity assoc,
                                    const std::string& symbol,
                                    const std::string& symbolRPN = "");

    bool hasOperatorWithSymbol(const FuncSet::FuncType ftype,
                               const std::string& symbol) const;
    bool hasOperatorWithRPNSymbol(const std::string& symbolRPN) const;

    FuncTokenSPC getOperator(const FuncSet::FuncType ftype,
                             const std::string& symbol) const;
    FuncTokenSPC getOperator(const std::string& symbolRPN) const;
    FuncTokenSP getOperator(const FuncSet::FuncType ftype,
                            const std::string& symbol);
    FuncTokenSP getOperator(const std::string& symbolRPN);

    void init(const Settings&);
    void preload(const Settings&);
    void load(const Settings&);
    void reload(const Settings&);

    friend class Session;
};

#endif