#include "calculator/FixedPtStringifier.h"

#include <iomanip>

#define INITIALIZER(X) \
    X { s.X }

#define ASSIGNER(X) X = s.X

FixedPtStringifier::FixedPtStringifier(const SettingsImpl& s)
    : INITIALIZER(grpBefDecimal),
      INITIALIZER(sepBefDecimal),
      INITIALIZER(decimalPt),
      INITIALIZER(grpAftDecimal),
      INITIALIZER(sepAftDecimal),
      INITIALIZER(floatUseAutoPrecision),
      INITIALIZER(autoPrecisionMaxConsecDigits),
      INITIALIZER(floatFixedPtFixedPrecision) {}

std::string FixedPtStringifier::generateOutputBuffer() const {
    std::string output;
    output.reserve(BUFFER_SIZE);
    return output;
}

void FixedPtStringifier::formatNegSign(std::string::const_iterator& srcIt,
                                       std::string& output) const {
    if (*srcIt == '-') {
        output.push_back('-');
        ++srcIt;
    }
}

void FixedPtStringifier::formatBefDecimal(std::string::const_iterator srcIt,
                                          std::string::const_iterator srcEnd,
                                          std::string& output) const {
    auto numDigits{srcEnd - srcIt};
    for (; srcIt != srcEnd; ++srcIt) {
        output.push_back(*srcIt);
        if (numDigits-- % grpBefDecimal == 1) output += sepBefDecimal;
    }

    output.erase(output.size() - sepBefDecimal.size());
}

void FixedPtStringifier::formatAftDecimal(std::string::const_iterator srcIt,
                                          std::string::const_iterator srcEnd,
                                          std::string& output) const {
    uint8_t numDigits{};
    if (srcIt == srcEnd) {
        output.push_back('.');
        output.push_back('0');
        return;
    }
    for (++srcIt; srcIt != srcEnd; ++srcIt) {
        output.push_back(*srcIt);
        if (++numDigits % grpAftDecimal == 0) output += sepAftDecimal;
    }
    if (numDigits % grpAftDecimal == 0)
        output.erase(output.size() - sepAftDecimal.size());
}

void FixedPtStringifier::update(const SettingsImpl& s) {
    ASSIGNER(grpBefDecimal);
    ASSIGNER(sepBefDecimal);
    ASSIGNER(decimalPt);
    ASSIGNER(grpAftDecimal);
    ASSIGNER(sepAftDecimal);
    ASSIGNER(floatUseAutoPrecision);
    ASSIGNER(autoPrecisionMaxConsecDigits);
    ASSIGNER(floatFixedPtFixedPrecision);
}

std::ostringstream FixedPtStringifier::getFixedPrecisionSStream(int p) {
    std::ostringstream sstream;
    sstream << std::fixed << std::setprecision(p);
    return sstream;
}