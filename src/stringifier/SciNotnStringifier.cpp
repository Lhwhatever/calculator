#include "calculator/SciNotnStringifier.h"

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
      INITIALIZER(sciNotnExponent) {}

void SciNotnStringifier::update(const SettingsImpl& s) {
    ASSIGNER(grpAftDecimal);
    ASSIGNER(sepAftDecimal);
    ASSIGNER(decimalPt);
    ASSIGNER(autoPrecisionMaxConsecDigits);
    ASSIGNER(sciNotnExponent);
}

StrConstIt SciNotnStringifier::formatPreMantissa(const StrConstIt srcBegin,
                                                 std::string& output) const {
    auto srcIt{srcBegin};
    for (; *srcIt != '.'; ++srcIt) output.push_back(*srcIt);
    output += decimalPt;
    return srcIt + 1;
}

StrConstIt SciNotnStringifier::formatMantissa(const StrConstIt srcMantissaStart,
                                              std::string& output) const {
    auto srcIt{srcMantissaStart};
    uint8_t sinceLastGrp{};
    while (*srcIt != 'e') {
        output.push_back(*srcIt);
        ++srcIt;
        if (++sinceLastGrp >= grpAftDecimal) {
            output += sepAftDecimal;
            sinceLastGrp = 0;
        }
    }
    if (sinceLastGrp == 0) output.erase(output.size() - sepAftDecimal.size());
    return srcIt;
}

void SciNotnStringifier::formatExponent(const StrConstIt srcItAtExp,
                                        const StrConstIt srcEnd,
                                        std::string& output) const {
    output += sciNotnExponent;
    auto srcIt{srcItAtExp + 1};
    output.push_back(*srcIt);  // append sign of exponent
    while (true) {
        ++srcIt;
        if (srcIt == srcEnd) {
            output.push_back('0');
            return;
        }
        if (*srcIt != '0') break;
    }
    output.append(srcIt, srcEnd);
}