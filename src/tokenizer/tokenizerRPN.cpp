#include "../except/syntaxException.h"
#include "../helper/strchop.h"
#include "tokenizer.h"

bool Tokenizer::beginToken__RPN() {
    if (*it == '-') {
        tokenBuilder << *it;
        auto next{it + 1};

        // minus sign
        if (next == end) {
            loopMode = MODE_SYMBOL;
            return true;
        }

        // negative number
        if (strchop::isNumeric(*next)) {
            loopMode = MODE_INTEGER;
            return true;
        }

        // can't be negative float
        if (*next != settings.decimalSign) loopMode = MODE_SYMBOL;
        return true;
    }

    return beginToken__infix();
}

void Tokenizer::flushSymbols__RPN(const FuncSet& funcs, TokenQueue& output) {
    auto id{tokenBuilder.str()};
    auto it{funcs.opRPN.find(id)};

    // no operators found
    if (it == funcs.opRPN.end()) throw SyntaxException(id);

    output.push(it->second);
    emptyTokenBuilder();
    allowInfixNext = false;
}
