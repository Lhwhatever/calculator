#include "tokenizer.h"
#include "../helper/strchop.h"
#include "../tokens/values/floatToken.h"
#include "../tokens/values/integerToken.h"

Tokenizer::Tokenizer(const Settings& s, ErrorCode& e)
    : settings{s},
      errCode{e},
      beginToken{s.exprSyntax == Settings::SYNTAX_RPN
                     ? &Tokenizer::beginToken__RPN
                     : &Tokenizer::beginToken__infix},
      flushSymbols{s.exprSyntax == Settings::SYNTAX_RPN
                       ? &Tokenizer::flushSymbols__RPN
                       : &Tokenizer::flushSymbols__infix} {}

void Tokenizer::emptyTokenBuilder() {
    tokenBuilder.str("");
    tokenBuilder.clear();
    loopMode = MODE_DEFAULT;
}

void Tokenizer::flushIntegers(TokenQueue& output) {
    long long data;

    // attempt to put number as a float
    if (!(tokenBuilder >> data)) {
        tokenBuilder.clear();
        tokenBuilder.str(tokenBuilder.str());
        flushFloats(output);
        if (errCode) return;
    }

    output.push(std::make_shared<IntegerToken>(data));
    emptyTokenBuilder();
    allowInfixNext = true;
}

void Tokenizer::flushFloats(TokenQueue& output) {
    long double data;
    if (!(tokenBuilder >> data)) {
        errCode = DataOutOfLimitError("long double", tokenBuilder.str(),
                                      std::to_string(data));
        return;
    }
    output.push(std::make_shared<FloatToken>(data));
    emptyTokenBuilder();
    allowInfixNext = true;
}

void Tokenizer::flushAll(const FuncSet& funcs, TokenQueue& output) {
    switch (loopMode) {
        case MODE_INTEGER:
            flushIntegers(output);
            break;
        case MODE_FLOAT:
        case MODE_FLOAT_EXP:
            flushFloats(output);
            break;
        case MODE_SYMBOL:
            (this->*flushSymbols)(funcs, output);
            break;
        default:
            break;
    }
}

void Tokenizer::tick(const FuncSet& funcs, TokenQueue& output) {
    const char& c{*it};
    if (loopMode == MODE_DEFAULT && (this->*beginToken)()) return;

    switch (loopMode) {
        case MODE_INTEGER:
            if (strchop::isNumeric(c))
                tokenBuilder << c;
            else if (c == settings.decimalSign) {  // float
                tokenBuilder << '.';
                loopMode = MODE_FLOAT;
            } else if (c == 'e' || c == 'E') {  // suspect scientific
                auto next{it + 1};
                if (next == end) {  // not scientific
                    flushIntegers(output);
                    if (errCode) return;
                    --it;
                } else if (strchop::isNumeric(*next)) {  // scientific
                    tokenBuilder << 'e';
                    loopMode = MODE_FLOAT_EXP;
                } else if (*next == '-' || *next == '+') {
                    auto after{next + 1};
                    if (after == end || !strchop::isNumeric(*after)) {
                        flushIntegers(output);
                        if (errCode) return;
                        --it;
                    } else {
                        tokenBuilder << 'e' << *next;
                        loopMode = MODE_FLOAT_EXP;
                        ++it;
                    }
                } else {
                    flushIntegers(output);
                    if (errCode) return;
                    --it;
                }
            } else if (c != settings.digitSep) {
                flushIntegers(output);
                if (errCode) return;
                --it;
            }
            break;

        case MODE_FLOAT:
            if (strchop::isNumeric(c))
                tokenBuilder << c;
            else if (c == 'e' || c == 'E') {  // suspect scientific
                auto next{it + 1};
                if (next == end) {  // not scientific
                    flushFloats(output);
                    if (errCode) return;
                    --it;
                } else if (strchop::isNumeric(*next)) {  // scientific
                    tokenBuilder << 'e';
                    loopMode = MODE_FLOAT_EXP;
                } else if (*next == '-' || *next == '+') {
                    auto after{next + 1};
                    if (after == end || !strchop::isNumeric(*after)) {
                        flushFloats(output);
                        if (errCode) return;
                        --it;
                    } else {
                        tokenBuilder << 'e' << *next;
                        loopMode = MODE_FLOAT_EXP;
                        ++it;
                    }
                } else {
                    flushFloats(output);
                    if (errCode) return;
                    --it;
                }
            } else if (c != settings.digitSep) {
                flushFloats(output);
                if (errCode) return;
                --it;
            }
            break;

        case MODE_FLOAT_EXP:
            if (strchop::isNumeric(c))
                tokenBuilder << c;
            else if (c != settings.digitSep) {
                flushFloats(output);
                if (errCode) return;
                --it;
            }
            break;
        case MODE_SYMBOL:
            if (loopMode == MODE_SYMBOL) {
                if (strchop::isSymbolic(c))
                    tokenBuilder << c;
                else {
                    (this->*flushSymbols)(funcs, output);
                    if (errCode) return;
                    --it;
                }
                break;
            }

        default:
            break;
    }
}

void Tokenizer::tokenize(const std::string& input, const FuncSet& funcs,
                         TokenQueue& output) {
    loopMode = MODE_DEFAULT;
    emptyTokenBuilder();
    allowInfixNext = false;

    for (it = input.cbegin(), end = input.cend(); it < end; ++it) {
        tick(funcs, output);
        if (errCode) return;
    }

    flushAll(funcs, output);
    output.flush();
}