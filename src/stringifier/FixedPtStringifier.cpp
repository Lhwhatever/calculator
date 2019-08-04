#include "calculator/FixedPtStringifier.h"
#include "calculator/NumFormatter.h"

#include <iomanip>

#define INITIALIZER(X) \
    X { s.X }

#define ASSIGNER(X) X = s.X

namespace {
using StrConstIt = std::string::const_iterator;
}

FixedPtStringifier::FixedPtStringifier(const SettingsImpl& s)
    : INITIALIZER(grpBefDecimal),
      INITIALIZER(sepBefDecimal),
      INITIALIZER(decimalPt),
      INITIALIZER(grpAftDecimal),
      INITIALIZER(sepAftDecimal),
      INITIALIZER(floatFixedPtDoLeading0),
      INITIALIZER(floatFixedPtPrecisionMode),
      INITIALIZER(autoPrecisionMaxConsecDigits),
      INITIALIZER(floatFixedPtFixedPrecision) {}

std::string FixedPtStringifier::generateOutputBuffer() const {
    std::string output;
    output.reserve(BUFFER_SIZE);
    return output;
}

void FixedPtStringifier::formatNegSign(StrConstIt& srcIt,
                                       std::string& output) const {
    if (*srcIt == '-') {
        output.push_back('-');
        ++srcIt;
    }
}

void FixedPtStringifier::formatBefDecimal(const StrConstIt srcBegin,
                                          const StrConstIt srcEnd,
                                          std::string& output) const {
    auto srcIt{srcBegin};
    auto numDigits{srcEnd - srcBegin};

    if (numDigits == 1 && *srcIt == '0') {
        if (floatFixedPtDoLeading0) output.push_back('0');
        return;
    }

    while (srcIt != srcEnd) {
        output.push_back(*srcIt++);
        if (numDigits-- % grpBefDecimal == 1) output += sepBefDecimal;
    }

    output.erase(output.size() - sepBefDecimal.size());
}

void FixedPtStringifier::formatAftDecimal(const StrConstIt srcItAtDecimal,
                                          const StrConstIt srcEnd,
                                          std::string& output) const {
    if (srcItAtDecimal == srcEnd) {
        output.push_back('0');
        return;
    }
    formatter::DecimalPart part{grpAftDecimal, sepAftDecimal};
    part.append(srcItAtDecimal + 1, srcEnd);
    output += part.get();
}

void FixedPtStringifier::update(const SettingsImpl& s) {
    ASSIGNER(grpBefDecimal);
    ASSIGNER(sepBefDecimal);
    ASSIGNER(decimalPt);
    ASSIGNER(grpAftDecimal);
    ASSIGNER(sepAftDecimal);
    ASSIGNER(floatFixedPtDoLeading0);
    ASSIGNER(floatFixedPtPrecisionMode);
    ASSIGNER(autoPrecisionMaxConsecDigits);
    ASSIGNER(floatFixedPtFixedPrecision);
}
