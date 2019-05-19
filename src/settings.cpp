#include "settings.h"

Settings::Settings(const ExprParsingMode mode) : exprParsingMode{RPN} {}

const Settings Settings::DEFAULT{};