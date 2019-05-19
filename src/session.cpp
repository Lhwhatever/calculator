#include "session.h"

#include <sstream>

#include "helper/strchop.h"
#include "packages/package.h"
#include "tokens/values/integerToken.h"

namespace {
enum ParserLoopMode {
    MODE_DEFAULT,
    MODE_INTEGER,
    MODE_IDENTIFIER,
    MODE_SYMBOL
};

void emptyStringStream(std::stringstream& ss) {
    ss.str("");
    ss.clear();
}

void flushIntegers(std::stringstream& ss, TokenDeque& deque) {
    long data;
    ss >> data;
    deque.push_back(std::move(std::make_shared<IntegerToken>(data)));
    emptyStringStream(ss);
}

void flushSymbols(std::stringstream& ss, TokenDeque& deque, OperatorMap& map) {
    auto op = map.at(ss.str());
    deque.push_back(op);
    emptyStringStream(ss);
}
}  // namespace

Session::Session(Settings settings, std::istream& istream,
                 std::ostream& ostream)
    : settings{settings}, istream{istream}, ostream{ostream}, tokenQueueRPN{} {
    default_packages::add();

    for (auto it = Package::packages.begin(), end = Package::packages.end();
         it != end; it++) {
        it->second.get().init(settings);
    }  // init

    for (auto it = Package::packages.begin(), end = Package::packages.end();
         it != end; it++) {
        it->second.get().preload(settings);
    }  // preload

    loadPackage("base");  // load base package
}

Session::~Session() {}

void Session::loadPackage(const std::string& name) {
    auto p = Package::packages.at(name).get();
    p.load(settings);
    mapOper.merge(p.mapOper);
}

std::string Session::getInput() {
    std::ostringstream ss;
    bool result;
    ostream << input_prompt::GET_INPUT_TOKEN;

    while (true) {
        std::string nextLine;
        result = std::getline(istream, nextLine) ? true : false;

        if (result)
            ss << nextLine;
        else
            break;

        if (nextLine.back() == '\\') {  // continue on next line
            ss.seekp(-1, std::ios_base::cur);
            ss << " ";
            ostream << input_prompt::INPUT_TOKEN_TABBED;
        } else
            break;
    }
    return ss.str();
}

void Session::parseExpr(const std::string& expr) {
    if (settings.exprParsingMode == Settings::RPN) {
        ParserLoopMode loopMode{MODE_DEFAULT};
        std::stringstream ss;

        for (auto it = expr.cbegin(), end = expr.cend(); it != end; ++it) {
            char c{*it};

            if (!loopMode) {
                if (strchop::isNumeric(c))
                    loopMode = MODE_INTEGER;
                else if (strchop::isSymbolic(c))
                    loopMode = MODE_SYMBOL;
                else if (strchop::isWhitespace(c))
                    continue;
            }

            if (loopMode == MODE_INTEGER) {
                if (strchop::isNumeric(c))
                    ss << c;
                else if (c != '_') {
                    flushIntegers(ss, tokenQueueRPN);
                    loopMode = MODE_DEFAULT;
                    --it;
                }
                continue;
            }

            if (loopMode == MODE_SYMBOL) {
                if (strchop::isSymbolic(c))
                    ss << c;
                else {
                    flushSymbols(ss, tokenQueueRPN, mapOper);
                    loopMode = MODE_DEFAULT;
                    --it;
                }

                continue;
            }
        }

        if (loopMode == MODE_INTEGER)
            flushIntegers(ss, tokenQueueRPN);
        else if (loopMode == MODE_SYMBOL)
            flushSymbols(ss, tokenQueueRPN, mapOper);
    }
}

void Session::rep() {
    parseExpr(getInput());

#ifdef DEBUG
    printRPNQueue();
#endif
}

#ifdef DEBUG
void Session::printRPNQueue() {
    unsigned long size{tokenQueueRPN.size()};

    ostream << "---------- RPN Queue ----------\n"
            << "No. of elements =  " << size << '\n';

    for (unsigned long i{0}; i < size; i++) {
        auto token{tokenQueueRPN.front()};
        tokenQueueRPN.pop_front();
        tokenQueueRPN.push_back(token);
        ostream << i << ".\t";

        auto asValue{std::dynamic_pointer_cast<ValueToken>(token)};
        if (asValue) {
            ostream << "ValueToken(" << asValue->toString() << ")\n";
            continue;
        }

        auto asOp{std::dynamic_pointer_cast<OperatorToken>(token)};
        if (asOp) {
            ostream << "OperatorToken(\"" << asOp->getIdentifier() << "\")\n";
            continue;
        }
    }

    ostream << "---------- End Queue ----------\n";
}
#endif