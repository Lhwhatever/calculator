#include "calculator/TokenStringifer.h"

TokenStringifier::TokenStringifier(const SettingsImpl& settings)
    : s{settings}, fixedPtStringify{s} {}

void TokenStringifier::onUpdate(const SettingsImpl& settings) { s = settings; }

std::string TokenStringifier::operator()(
    const refactor::IntegerToken& token) const {
    return fixedPtStringify(token.value);
}
