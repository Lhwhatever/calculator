#ifndef CALC__TOKENS__OPERATORS__FUNC_SET_H_
#define CALC__TOKENS__OPERATORS__FUNC_SET_H_

#include "funcToken.h"

using FuncTokenSP = std::shared_ptr<FuncToken>;
using FuncTokenSPC = std::shared_ptr<const FuncToken>;
using FTMap = std::map<std::string, FuncTokenSP>;

struct FuncSet {
    enum FuncType : char { TYPE_OP_PREFIX, TYPE_OP_POSTFIX, TYPE_OP_INFIX };

    FTMap opPrefix;
    FTMap opPostfix;
    FTMap opInfix;
    FTMap opRPN;

    FuncSet();
    FuncSet(const FuncSet&);

    void merge(FuncSet&);
    FTMap& getRelevant(FuncType);
    const FTMap& getRelevant(FuncType) const;

    static std::string describe(FuncType);
};

#endif