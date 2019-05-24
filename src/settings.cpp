#include "settings.h"

Settings::Settings(const ExprSyntax syntax) : exprSyntax{syntax} {}

const Settings Settings::DEFAULT{};