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
      allowInfix{false},
      beginToken{settings.exprSyntax == Settings::SYNTAX_INFIX
                     ? beginToken__infix
                     : beginToken__RPN},
      flushSymbols{settings.exprSyntax == Settings::SYNTAX_INFIX
                       ? flushSymbols__infix
                       : flushSymbols__RPN} {
    std::cout << Package::basePackage.NAME;
    Package::add(Package::basePackage);

    for (auto it = Package::packages.begin(), end = Package::packages.end();
         it != end; it++)
        it->second.get().init(settings);
    // init

    for (auto it = Package::packages.begin(), end = Package::packages.end();
         it != end; it++)
        it->second.get().preload(settings);
    // preload

    loadPackage("base");  // load base package
}

Session::~Session() {}

void Session::loadPackage(const std::string& name) {
    auto p = Package::packages.at(name).get();
    p.load(settings);
    funcs.merge(p.functions);
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

    tokenQueue.push(std::make_shared<IntegerToken>(data));
    emptyTokenBuilder();
    loopMode = MODE_DEFAULT;
    allowInfix = true;
}

void Session::flushFloats(ParserLoopMode& loopMode) {
    long double data;
    if (!(tokenBuilder >> data)) {
        throw DataOutOfLimitException("long double", std::to_string(data),
                                      tokenBuilder.str());
    }
    tokenQueue.push(std::make_shared<FloatToken>(data));
    emptyTokenBuilder();
    loopMode = MODE_DEFAULT;
    allowInfix = true;
}

void Session::flushSymbols__RPN(Session& s, ParserLoopMode& loopMode) {
    auto id{s.tokenBuilder.str()};
    auto it{s.funcs.opRPN.find(id)};

    // no operators found
    if (it == s.funcs.opRPN.end()) throw SyntaxException(id);

    s.tokenQueue.push(it->second);
    s.emptyTokenBuilder();
    loopMode = MODE_DEFAULT;
    s.allowInfix = false;
}

void Session::flushSymbols__infix(Session& s, ParserLoopMode& loopMode) {
    auto id{s.tokenBuilder.str()};

    // check either prefix map or infix map
    auto& map1{s.allowInfix ? s.funcs.opInfix : s.funcs.opPrefix};
    auto it1{map1.find(id)};
    if (it1 == map1.end()) {
        // not in this map; check postfix map
        auto it2{s.funcs.opPostfix.find(id)};
        if (it2 == s.funcs.opPostfix.end())
            throw SyntaxException("no operator with symbol " + id +
                                  " was found");
        s.tokenQueue.push(it2->second);
    } else
        s.tokenQueue.push(it1->second);

    s.emptyTokenBuilder();
    loopMode = MODE_DEFAULT;
    s.allowInfix = false;
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

void Session::processCommands(const std::string& expr) {
    if (expr == ":q") throw InterruptException();
    if (expr == ":q!") throw InterruptException(true);
}

bool Session::beginToken__infix(Session& s, ParserLoopMode& loopMode,
                                const char& c, std::string::const_iterator& it,
                                std::string::const_iterator& end) {
    if (strchop::isNumeric(c)) loopMode = MODE_INTEGER;

    // for suspected floats
    else if (c == s.settings.decimalSign) {
        auto next = it + 1;

        if (next != end && strchop::isNumeric(*next)) {  // float
            s.tokenBuilder << '.';
            loopMode = MODE_FLOAT;
            return true;
        } else  // not float
            loopMode = MODE_SYMBOL;
    }

    else if (strchop::isSymbolic(c))
        loopMode = MODE_SYMBOL;
    else if (strchop::isWhitespace(c))
        return true;

    return false;
}

bool Session::beginToken__RPN(Session& s, ParserLoopMode& loopMode,
                              const char& c, std::string::const_iterator& it,
                              std::string::const_iterator& end) {
    if (s.settings.exprSyntax == Settings::SYNTAX_RPN && c == '-') {
        s.tokenBuilder << c;
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
        if (*next != s.settings.decimalSign) loopMode = MODE_SYMBOL;
        return true;
    }
    return beginToken__infix(s, loopMode, c, it, end);
}

void Session::tokenize(const std::string& expr) {
    ParserLoopMode loopMode{MODE_DEFAULT};
    emptyTokenBuilder();

    auto it = expr.cbegin();
    if (*it == ':') processCommands(expr);

    for (auto end = expr.cend(); it != end; ++it) {
        const char& c{*it};
        if (loopMode == MODE_DEFAULT && beginToken(*this, loopMode, c, it, end))
            continue;

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
                        flushSymbols(*this, loopMode);
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
            flushSymbols(*this, loopMode);
        default:
            break;
    }

    allowInfix = false;
    tokenQueue.flush();
}

ValueStack Session::evaluateTokens() {
    ValueStack values;
    values.reserve(tokenQueue.size());

    while (tokenQueue.size()) {
        auto token{tokenQueue.pop()};

        switch (token->CATEGORY) {
            case Token::CAT_FUNC:
                std::static_pointer_cast<FuncToken>(token)->operate(values);
                break;

            case Token::CAT_VALUE:
                values.push_back(std::static_pointer_cast<ValueToken>(token));
                break;
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
        tokenize(read());

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
