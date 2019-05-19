#include "binaryOperatorToken.h"

BinaryOperatorToken::BinaryOperatorToken(const int relPred,
                                         const std::string& idLaTeX,
                                         const std::string& idPlain)
    : OperatorToken{2, relPred, idLaTeX, idPlain} {}