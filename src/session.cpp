#include "session.h"

#include "except/arityMismatchException.h"
#include "except/dataOutOfLimitException.h"
#include "except/interruptException.h"
#include "except/noOperationException.h"
#include "except/syntaxException.h"
#include "helper/strchop.h"
#include "packages/package.h"
#include "tokens/values/floatToken.h"
#include "tokens/values/integerToken.h"

Session::Session(const Settings& settings, std::istream& istream,
                 std::ostream& ostream, std::ostream& errstream)
    : settings{settings},
      istream{istream},
      ostream{OStreamHandler{settings, ostream, IOMODE_STD}},
      errstream{errstream},
      tokenQueue{},
      tokenBuilder{} {
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

void Session::emptyTokenBuilder() {
    tokenBuilder.str("");
    tokenBuilder.clear();
}

void Session::flushIntegers(ParserLoopMode& loopMode) {
    long long data;

    // attempt to put number as a float
    if (!(tokenBuilder >> data)) {
        tokenBuilder.clear();
        tokenBuilder.str(tokenBuilder.str());
        flushFloats(loopMode);
        return;
    }

    tokenQueue.push_back(std::make_shared<IntegerToken>(data));
    emptyTokenBuilder();
    loopMode = MODE_DEFAULT;
}

void Session::flushFloats(ParserLoopMode& loopMode) {
    long double data;
    if (!(tokenBuilder >> data)) {
        throw DataOutOfLimitException("long double", std::to_string(data),
                                      tokenBuilder.str());
    }
    tokenQueue.push_back(std::make_shared<FloatToken>(data));
    emptyTokenBuilder();
    loopMode = MODE_DEFAULT;
}

void Session::flushSymbols__RPN(ParserLoopMode& loopMode) {
    auto id{tokenBuilder.str()};
    auto it{mapOper.lower_bound(id)};
    auto end{mapOper.upper_bound(id)};

    if (it == end) throw SyntaxException(id);  // no operators found
    tokenQueue.push_back(it->second);
    emptyTokenBuilder();
    loopMode = MODE_DEFAULT;
}

std::string Session::read() {
    std::ostringstream ss;
    std::string nextLine;
    ostream << input_prompt::GET_INPUT_TOKEN;

    while (true) {
        std::getline(istream, nextLine);
        ss << nextLine;

        if (nextLine.back() != '\\') break;

        // continue with next line
        ss.seekp(-1, std::ios_base::cur);
        ss << " ";
        ostream << input_prompt::INPUT_TOKEN_TABBED;
    }

    return ss.str();
}

void Session::tokenize__RPN(const std::string& expr) {
    ParserLoopMode loopMode{MODE_DEFAULT};
    emptyTokenBuilder();

    auto it = expr.cbegin();
    if (*it == ':') {
        if (expr == ":q") throw InterruptException();
        if (expr == ":q!") throw InterruptException(true);
    }

    for (auto end = expr.cend(); it != end; ++it) {
        const char& c{*it};

        if (loopMode == MODE_DEFAULT) {
            if (strchop::isNumeric(c)) loopMode = MODE_INTEGER;

            // for suspected floats
            else if (c == settings.decimalSign) {
                auto next = it + 1;

                if (next != end && strchop::isNumeric(*next)) {  // float
                    tokenBuilder << '.';
                    loopMode = MODE_FLOAT;
                    continue;
                } else  // not float
                    loopMode = MODE_SYMBOL;
            }

            // for minus sign
            else if (settings.exprSyntax == Settings::SYNTAX_RPN && c == '-') {
                tokenBuilder << c;
                auto next{it + 1};

                // minus sign
                if (next == end) {
                    loopMode = MODE_SYMBOL;
                    break;
                }

                // negative number
                if (strchop::isNumeric(*next)) {
                    loopMode = MODE_INTEGER;
                    continue;
                }

                // can't be negative float
                if (*next != settings.decimalSign) loopMode = MODE_SYMBOL;
                continue;
            }

            else if (strchop::isSymbolic(c))
                loopMode = MODE_SYMBOL;
            else if (strchop::isWhitespace(c))
                continue;
        }

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
                        flushIntegers(loopMode);
                        --it;
                    } else if (strchop::isNumeric(*next)) {  // scientific
                        tokenBuilder << 'e';
                        loopMode = MODE_FLOAT_EXP;
                    } else if (*next == '-' || *next == '+') {
                        auto after{next + 1};
                        if (after == end || !strchop::isNumeric(*after)) {
                            flushIntegers(loopMode);
                            --it;
                        } else {
                            tokenBuilder << 'e' << *next;
                            loopMode = MODE_FLOAT_EXP;
                            ++it;
                        }
                    } else {
                        flushIntegers(loopMode);
                        --it;
                    }
                } else if (c != settings.digitSep) {
                    flushIntegers(loopMode);
                    --it;
                }
                break;

            case MODE_FLOAT:
                if (strchop::isNumeric(c))
                    tokenBuilder << c;
                else if (c == 'e' || c == 'E') {  // suspect scientific
                    auto next{it + 1};
                    if (next == end) {  // not scientific
                        flushFloats(loopMode);
                        --it;
                    } else if (strchop::isNumeric(*next)) {  // scientific
                        tokenBuilder << 'e';
                        loopMode = MODE_FLOAT_EXP;
                    } else if (*next == '-' || *next == '+') {
                        auto after{next + 1};
                        if (after == end || !strchop::isNumeric(*after)) {
                            flushFloats(loopMode);
                            --it;
                        } else {
                            tokenBuilder << 'e' << *next;
                            loopMode = MODE_FLOAT_EXP;
                            ++it;
                        }
                    } else {
                        flushFloats(loopMode);
                        --it;
                    }
                } else if (c != settings.digitSep) {
                    flushFloats(loopMode);
                    --it;
                }
                break;

            case MODE_FLOAT_EXP:
                if (strchop::isNumeric(c))
                    tokenBuilder << c;
                else if (c != settings.digitSep) {
                    flushFloats(loopMode);
                    --it;
                }
                break;
            case MODE_SYMBOL:
                if (loopMode == MODE_SYMBOL) {
                    if (strchop::isSymbolic(c))
                        tokenBuilder << c;
                    else {
                        flushSymbols__RPN(loopMode);
                        --it;
                    }
                    break;
                }

            default:
                break;
        }
    }

    switch (loopMode) {
        case MODE_INTEGER:
            flushIntegers(loopMode);
            break;
        case MODE_FLOAT:
        case MODE_FLOAT_EXP:
            flushFloats(loopMode);
            break;
        case MODE_SYMBOL:
            flushSymbols__RPN(loopMode);
        default:
            break;
    }
}

void Session::tokenize__infix(const std::string& expr) {}

ValueStack Session::evaluateTokens() {
    TokenDeque queue;
    ValueStack values;
    if (settings.exprSyntax == Settings::SYNTAX_RPN) {
        queue = std::move(tokenQueue);
    }

    values.reserve(queue.size());

    while (queue.size()) {
        auto token{queue.front()};
        queue.pop_front();

        auto value{std::dynamic_pointer_cast<ValueToken>(token)};
        if (value) {
            values.push_back(value);
            continue;
        }

        auto oper{std::dynamic_pointer_cast<OperatorToken>(token)};
        if (oper) {
            oper->operate(values);
            continue;
        }
    }

    return values;
}

void Session::displayResults(ValueStack& stack) const {
    if (stack.size() == 0) return;
    if (stack.size() == 1) {
        ostream << *stack[0];
        return;
    }

    if (settings.exprSyntax != Settings::SYNTAX_RPN)
        throw SyntaxException{"more arguments than required by operators"};

    ostream << '(' << *stack[0];
    for (auto it = ++(stack.cbegin()), end = stack.cend(); it != end; ++it) {
        ostream << ", " << **it;
    }
    ostream << ")\n";
}

void Session::rep() {
    bool fail{true};

    try {
        auto x{read()};

        if (settings.exprSyntax == Settings::SYNTAX_RPN)
            tokenize__RPN(x);
        else
            tokenize__infix(x);

        auto values = evaluateTokens();
        displayResults(values);
        fail = true;
    } catch (ArityMismatchException& e) {
        errstream << "[Error]<Syntax/ArityMismatch> " << e.what();
    } catch (SyntaxException& e) {
        errstream << "[Error]<Syntax> " << e.what();
    } catch (NoOperationException& e) {
        errstream << "[Error]<No Operation> " << e.what();
    } catch (InterruptException& e) {
        throw;
    } catch (DataOutOfLimitException& e) {
        errstream << "[Error]<DataOutOfLimit> " << e.what();
        emptyTokenBuilder();
    } catch (std::exception& e) {
        errstream << "[Error] " << e.what();
    }

    if (fail) {
        errstream << '\n';
        tokenQueue.clear();
    }
}

void Session::repl() {
    ostream << "Enter :q to leave.\n";
    while (true) try {
            rep();
        } catch (InterruptException& e) {
            if (e.FORCE) break;
            std::string result;
            while (true) {
                ostream << "Are you sure you want to leave? (y/n) ";
                std::getline(istream, result);
                if (result == "y" || result == "n" || result == "Y" ||
                    result == "N")
                    break;
            }
            if (result == "y" || result == "Y") {
                ostream << "To skip confirmation next time, use :q! instead.\n";
                break;
            }
        }
}

#ifdef DEBUG
void Session::printRPNQueue() {
    unsigned long size{tokenQueue.size()};

    ostream << "---------- RPN Queue ----------\n"
            << "No. of elements =  " << size << '\n';

    for (unsigned long i{0}; i < size; i++) {
        auto token{tokenQueue.front()};
        tokenQueue.pop_front();
        tokenQueue.push_back(token);
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