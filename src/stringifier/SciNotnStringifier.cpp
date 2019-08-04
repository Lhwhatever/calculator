#include "calculator/SciNotnStringifier.h"

#include <iostream>

#define INITIALIZER(X) \
    X { s.X }

#define ASSIGNER(X) X = s.X

namespace {
using StrConstIt = std::string::const_iterator;
}

SciNotnStringifier::SciNotnStringifier(const SettingsImpl& s)
    : INITIALIZER(grpAftDecimal),
      INITIALIZER(sepAftDecimal),
      INITIALIZER(decimalPt),
      INITIALIZER(autoPrecisionMaxConsecDigits),
      INITIALIZER(omitPlusInExponent),
      INITIALIZER(sciNotnExponent),
      INITIALIZER(sciNotnPrecision) {}

void SciNotnStringifier::update(const SettingsImpl& s) {
    ASSIGNER(grpAftDecimal);
    ASSIGNER(sepAftDecimal);
    ASSIGNER(decimalPt);
    ASSIGNER(autoPrecisionMaxConsecDigits);
    ASSIGNER(omitPlusInExponent);
    ASSIGNER(sciNotnExponent);
    ASSIGNER(sciNotnPrecision);
}

StrConstIt SciNotnStringifier::formatSignificand(const StrConstIt srcBegin,
                                                 std::string& output) const {
    auto srcIt{srcBegin};
    for (;;) {
        auto ch{*srcIt++};
        if (ch == '.') break;
        output.push_back(ch);
    }
    output += decimalPt;

    uint8_t sinceLastGrp{};
    for (;;) {
        auto ch{*srcIt++};
        if (ch == 'e') break;
        output.push_back(ch);
        if (++sinceLastGrp >= grpAftDecimal) {
            output += sepAftDecimal;
            sinceLastGrp = 0;
        }
    }
    if (sinceLastGrp == 0) output.erase(output.size() - sepAftDecimal.size());
    return srcIt;
}

void SciNotnStringifier::formatExponent(const StrConstIt srcItAftExp,
                                        const StrConstIt srcEnd,
                                        std::string& output) const {
    output += sciNotnExponent;
    auto srcIt{srcItAftExp};
    auto signOfExp{*srcIt++};
    if (!omitPlusInExponent || signOfExp != '+') output.push_back(signOfExp);

    while (*srcIt == '0')
        if (++srcIt == srcEnd) {
            output.push_back('0');
            return;
        }

    output.append(srcIt, srcEnd);
}