#include "input.h"
#include "tokens/operatorToken.h"
#include "settings.h"
#include "strchop.h"


Environment::Environment(Settings::ExprParsingMode exprParsingMode,
        std::istream& istream, std::ostream& ostream)
    : exprParsingMode{exprParsingMode}, istream{istream}, ostream{ostream}, tokenQueueRPN() {
    
}

// TODO: Fix this
void Environment::parseExpr(std::string& expr) {
    if(exprParsingMode == Settings::RPN) {
        for(std::string::iterator it = expr.begin(); it != expr.end(); ++it) {
            char c = *it;
            Token* nextToken;

            if(isNumeric(c)) {
                // process digits
                long nextVal = c - '0';
                while(++it != expr.end()) {
                    char c = *it;
                    if(isNumeric(c)) nextVal = nextVal * 10 + (c - '0');
                    else if(c == '_') continue; // treat underscores as digit separators
                    else break;
                }
                nextToken = new ValueToken(nextVal);
            } else if(isWhitespace(c)) {
                // ignore whitespace
            } else if(isAlphabetical(c)){
                // check alphabetical identifiers
            } else if(isSymbolic(c)) {
                // check for symbolic operators
                std::string opId(1, c);
                while(++it != expr.end()) {
                    char c = *it;
                    if(isSymbolic(c)) opId.push_back(c);
                    else break;
                }
                nextToken = OperatorToken::symbolOperators.at(opId);
            }
            tokenQueueRPN.push_back(nextToken);
        }

    }


}

#ifdef DEBUG
void Environment::printRPNQueue() {
    ostream << "RPN Queue: ";
    int i = 0;
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

void Environment::tick() {
    std::string expr;
    ostream << GET_INPUT_TOKEN;
    std::getline(istream, expr);

    parseExpr(expr);

    #ifdef DEBUG
    printRPNQueue();
    #endif
}

Environment::~Environment() {
    while(!tokenQueueRPN.empty()) {
        Token* token {tokenQueueRPN.front()};
        tokenQueueRPN.pop_front();
        if(token->getTokenType() == TokenType::VALUE) {
            delete (ValueToken*) token;
        }
    }
}