#include "calculator/FixedPointStringifier.h"

#include <iomanip>

#define INITIALIZER(X) \
    X { s.X }

#define ASSIGNER(X) X = s.X

FixedPointStringifier::FixedPointStringifier(const SettingsImpl& s)
    : INITIALIZER(grpBefDecimal),
      INITIALIZER(sepBefDecimal),
      INITIALIZER(grpAftDecimal),
      INITIALIZER(sepAftDecimal),
      INITIALIZER(decimalPt),
      INITIALIZER(floatPrecisionMode),
      INITIALIZER(autoPrecisionMaxConsecDigits) {}

std::string FixedPointStringifier::generateOutputBuffer() const {
    std::string output;
    output.reserve(BUFFER_SIZE);
    return output;
}

void FixedPointStringifier::formatNegSign(std::string::const_iterator& srcIt,
                                          std::string& output) const {
    if (*srcIt == '-') {
        output.push_back('-');
        ++srcIt;
    }
}

void FixedPointStringifier::formatBefDecimal(std::string::const_iterator srcIt,
                                             std::string::const_iterator srcEnd,
                                             std::string& output) const {
    auto numDigits{srcEnd - srcIt};
    for (; srcIt != srcEnd; ++srcIt) {
        output.push_back(*srcIt);
        if (numDigits-- % grpBefDecimal == 1) output += sepBefDecimal;
    }

    output.erase(output.size() - sepBefDecimal.size());
}

void FixedPointStringifier::formatAftDecimal(std::string::const_iterator srcIt,
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

void FixedPointStringifier::update(const SettingsImpl& s) {
    ASSIGNER(grpBefDecimal);
    ASSIGNER(sepBefDecimal);
    ASSIGNER(grpAftDecimal);
    ASSIGNER(sepAftDecimal);
    ASSIGNER(decimalPt);
    ASSIGNER(floatPrecisionMode);
    ASSIGNER(autoPrecisionMaxConsecDigits);
}

std::ostringstream FixedPointStringifier::getFixedPrecisionSStream(
    int p) const {
    std::ostringstream sstream;
    sstream << std::fixed << std::setprecision(p);
    return sstream;
}