#include "funcSet.h"

FuncSet::FuncSet(){};
FuncSet::FuncSet(const FuncSet& funcSet)
    : opPrefix{funcSet.opPrefix},
      opPostfix{funcSet.opPostfix},
      opInfix{funcSet.opInfix},
      opRPN{funcSet.opRPN} {}

void FuncSet::merge(FuncSet& funcSet) {
    opPrefix.merge(funcSet.opPrefix);
    opPostfix.merge(funcSet.opPostfix);
    opInfix.merge(funcSet.opInfix);
    opRPN.merge(funcSet.opRPN);
}

FTMap& FuncSet::getRelevant(const FuncType ftype) {
    switch (ftype) {
        case TYPE_OP_PREFIX:
            return opPrefix;
        case TYPE_OP_POSTFIX:
            return opPostfix;
        case TYPE_OP_INFIX:
            return opInfix;
    }
    throw std::out_of_range("unknown enum value");
}

const FTMap& FuncSet::getRelevant(const FuncType ftype) const {
    switch (ftype) {
        case TYPE_OP_PREFIX:
            return opPrefix;
        case TYPE_OP_POSTFIX:
            return opPostfix;
        case TYPE_OP_INFIX:
            return opInfix;
    }
    throw std::out_of_range("unknown enum value");
}

std::string FuncSet::describe(const FuncType ftype) {
    switch (ftype) {
        case TYPE_OP_PREFIX:
            return "prefix";
        case TYPE_OP_POSTFIX:
            return "postfix";
        case TYPE_OP_INFIX:
            return "infix";
        default:
            return "???";
    }
}