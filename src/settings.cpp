#include "settings.h"

#include "except/invalidSettingException.h"
#include "helper/strchop.h"

Settings::Settings(const ExprSyntax syntax, const std::string digitSep,
                   const unsigned int digitSepInterval)
    : exprSyntax{syntax},
      digitSep{digitSep},
      digitSepInterval{digitSepInterval} {
    if (strchop::isWhitespace(*digitSep.cbegin())) {
        throw InvalidSettingException{"digit separator cannot be whitespace"};
    }
}

const Settings Settings::DEFAULT{};