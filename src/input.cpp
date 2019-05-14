#include "input.h"

#include <vector>
#include <sstream>

#include "tokens/operatorToken.h"
#include "settings.h"
#include "strchop.h"


namespace {
    enum ParserLoopMode {
        MODE_DEFAULT, MODE_INTEGER, MODE_IDENTIFIER, MODE_SYMBOL
    };

}


Environment::Environment(settings::ExprParsingMode exprParsingMode,
        std::istream& istream, std::ostream& ostream)
    : exprParsingMode{exprParsingMode}, istream{istream}, ostream{ostream}, tokenQueueRPN() {
    
}

std::string Environment::getInput() {
    std::string expr;
    bool result;
    ostream << input_prompt::GET_INPUT_TOKEN;

    while(true) {
        std::string nextLine;
        result = std::getline(istream, nextLine) ? true : false;

        if(result) expr += nextLine;
        else break;

        if(nextLine.back() == '\\') { // continue on next line
            expr.pop_back();
            expr.push_back(' ');
            ostream << input_prompt::INPUT_TOKEN_TABBED;
        } else break;
    }
    return expr;
}

void Environment::parseExpr(const std::string& expr) {
    if(exprParsingMode == settings::RPN) {
        ParserLoopMode loopMode{MODE_DEFAULT};
        long dataInteger{0};
        std::string symbol{};

        const auto flushIntegers = [&]() {
            tokenQueueRPN.push_back(new ValueToken{dataInteger});
            dataInteger = 0;
            loopMode = MODE_DEFAULT;
        };

        const auto flushSymbols = [&]() {
            tokenQueueRPN.push_back(OperatorToken::symbolOperators.at(symbol));
            symbol.clear();
            loopMode = MODE_DEFAULT;
        };
        
        for(auto it = expr.cbegin(), end = expr.cend(); it != end; ++it) {
            auto c = *it;
            
            if(!loopMode) {
                if(strchop::isNumeric(c)) loopMode = MODE_INTEGER;
                else if(strchop::isSymbolic(c)) loopMode = MODE_SYMBOL;
                else if(strchop::isWhitespace(c)) continue;
            }

            if(loopMode == MODE_INTEGER) {
                if(strchop::isNumeric(c))
                    dataInteger = dataInteger * 10 + (c - '0');
                else if(c != '_') {
                    flushIntegers();
                    --it;
                }
                
                continue;
            }
            
            if(loopMode == MODE_SYMBOL) {
                if(strchop::isSymbolic(c)) symbol.push_back(c);
                else {
                    flushSymbols();
                    --it;
                }

                continue;
            }
       }

       if(loopMode == MODE_INTEGER) flushIntegers();
       else if(loopMode == MODE_SYMBOL) flushSymbols();
   }


}

#ifdef DEBUG
void Environment::printRPNQueue() {
    ostream << "RPN Queue: ";
    auto i{0};
    int size = tokenQueueRPN.size();
    ostream << size << " elements\n";
    while(i < size) {
        Token* token {tokenQueueRPN.front()};
        tokenQueueRPN.pop_front();
        ostream << i++ << "\t" << *token << "\n";
        tokenQueueRPN.push_back(token);
    }
    ostream << "End of Queue\n";
}
#endif

// INCOMPLETE
void Environment::runRPNQueue() {
    std::vector<ValueToken> valueQueue{tokenQueueRPN.size()};

    while(!tokenQueueRPN.empty()) {
        auto token {tokenQueueRPN.front()};
        tokenQueueRPN.pop_front();

        // for value tokens
        auto valueToken = dynamic_cast<ValueToken*>(token);
        if(valueToken) {
            valueQueue.push_back(*valueToken);
            continue;
        }

        // for operator tokens
        auto operatorToken = dynamic_cast<OperatorToken*>(token);
        if(operatorToken) {
            // syntax error: wrong number of value tokens
            int queueSize = valueQueue.size();

            if(operatorToken->ARITY > queueSize) {
                std::stringstream ss{"Syntax error\n"};
                ss << "\toperator expected " << operatorToken->ARITY
                    << " values but only " << queueSize
                    << " were available.";
                throw ss.str();
            }
        }
    }
}

void Environment::tick() {
    std::string expr{getInput()};
    parseExpr(expr);
    printRPNQueue();
}

Environment::~Environment() {
    while(!tokenQueueRPN.empty()) {
        auto token {tokenQueueRPN.front()};
        tokenQueueRPN.pop_front();

        auto valueToken = dynamic_cast<ValueToken*>(token);
        if(valueToken) delete valueToken;
    }
}