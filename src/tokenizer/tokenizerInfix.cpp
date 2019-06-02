#include "../helper/strchop.h"
#include "tokenizer.h"

bool Tokenizer::beginToken__infix() {
    if (strchop::isNumeric(*it)) {
        loopMode = MODE_INTEGER;
        return false;
    }

    // for suspected floats
    if (*it == settings.decimalSign) {
        auto next = it + 1;

        if (next != end && strchop::isNumeric(*next)) {  // float
            tokenBuilder << '.';
            loopMode = MODE_FLOAT;
            return true;
        }

        // not float
        loopMode = MODE_SYMBOL;
        return false;
    }

    if (strchop::isSymbolic(*it)) {
        loopMode = MODE_SYMBOL;
        return false;
    }

    if (strchop::isWhitespace(*it)) return true;

    return false;
}

void Tokenizer::flushSymbols__infix(const FuncSet& funcs, TokenQueue& output) {
    auto id{tokenBuilder.str()};

    // check either prefix map or infix map
    auto& map1{allowInfixNext ? funcs.opInfix : funcs.opPrefix};
    auto it1{map1.find(id)};
    if (it1 == map1.end()) {
        // not in this map; check postfix map
        auto it2{funcs.opPostfix.find(id)};
        if (it2 == funcs.opPostfix.end()) {
            errCode = UnknownOperatorError(id);
            return;
        }
        output.push(it2->second);
    } else
        output.push(it1->second);

    emptyTokenBuilder();
    allowInfixNext = false;
}