#include "calculator/EngNotnStringifier.h"

#define INITIALIZER(X) \
    X { s.X }

#define ASSIGNER(X) X = s.X

namespace {
using StrConstIt = std::string::const_iterator;
}

EngNotnStringifier::EngNotnStringifier(const SettingsImpl& s)
    : INITIALIZER(grpAftDecimal),
      INITIALIZER(sepAftDecimal),
      INITIALIZER(decimalPt),
      INITIALIZER(autoPrecisionMaxConsecDigits),
      INITIALIZER(sciNotnExponent) {}

void EngNotnStringifier::update(const SettingsImpl& s) {
    ASSIGNER(grpAftDecimal);
    ASSIGNER(sepAftDecimal);
    ASSIGNER(decimalPt);
    ASSIGNER(autoPrecisionMaxConsecDigits);
    ASSIGNER(sciNotnExponent);
}

void EngNotnStringifier::formatSignificand(StrConstIt srcBegin, int shift,
                                           std::string& output) const {
    auto srcIt{srcBegin};
    bool skipDecimal{false};
    output.push_back(*srcIt++);
    while (shift-- > 0) {
        auto ch{*++srcIt};
        if (ch == 'e') {
            skipDecimal = true;
            break;
        }
        output.push_back(ch);
    }

    if (skipDecimal) {
        output.append(shift, '0');
        return;
    }

    output += decimalPt;
    uint8_t sinceLastGrp{};

    for (;;) {
        auto ch{*++srcIt};
        if (ch == 'e') break;
        output.push_back(ch);
        if (++sinceLastGrp >= grpAftDecimal) {
            output += sepAftDecimal;
            sinceLastGrp = 0;
        }
    }

    if (sinceLastGrp == 0) output.erase(output.size() - sepAftDecimal.size());
}