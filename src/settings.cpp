#include "settings.h"

#include "except/invalidSettingException.h"
#include "helper/strchop.h"

Settings::Settings(ExprSyntax syntax, char digitSep, int digitSepInterval,
                   char decimalSign)
    : exprSyntax{syntax},
      digitSep{digitSep},
      digitSepInterval{digitSepInterval},
      decimalSign{decimalSign} {
    if (!digitSep &&
        (strchop::isAlphanumeric(digitSep) || strchop::isWhitespace(digitSep) ||
         !strchop::isPrintable(digitSep) || digitSep == '+' || digitSep == '-'))
        throw InvalidSettingException{
            "digit separator cannot be alphanumeric, whitespace or "
            "non-printable (unless it is \\0)"};

    if (strchop::isAlphanumeric(decimalSign) ||
        strchop::isWhitespace(decimalSign) ||
        !strchop::isPrintable(decimalSign) || decimalSign == '+' ||
        decimalSign == '-')
        throw InvalidSettingException{
            "digit separator cannot be alphanumeric, whitespace or "
            "non-printable"};

    if (digitSep == decimalSign)
        throw InvalidSettingException{
            "digit separator cannot be same as decimal sign"};

    if (digitSepInterval < 0)
        throw InvalidSettingException{
            "digit separator interval cannot be negative"};
}

const Settings Settings::DEFAULT;