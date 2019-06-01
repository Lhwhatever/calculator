#include "session.h"

#include "except/arityMismatchException.h"
#include "except/dataOutOfLimitException.h"
#include "except/interruptException.h"
#include "except/noOperationException.h"
#include "except/syntaxException.h"
#include "helper/strchop.h"
#include "packages/package.h"
#include "tokens/tokenQueueShunting.h"
#include "tokens/values/floatToken.h"
#include "tokens/values/integerToken.h"

Session::Session(const Settings& settings, std::istream& istream,
                 std::ostream& ostream, std::ostream& errstream)
    : settings{settings},
      istream{istream},
      ostream{OStreamHandler{settings, ostream, IOMODE_STD}},
      errstream{errstream},
      tokenQueue{settings.exprSyntax == Settings::SYNTAX_RPN
                     ? TokenQueue()
                     : ShuntingTokenQueue()},
      tokenizer{settings} {
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

void Session::tokenize(const std::string& expr) {
    if (expr.at(0) == ':')
        processCommands(expr);
    else
        tokenizer.tokenize(expr, funcs, tokenQueue);
}

ValueStack Session::evaluateTokens() {
    ValueStack values;
    values.reserve(tokenQueue.size());

    while (tokenQueue.size()) {
        auto token{tokenQueue.pop()};

        switch (token->CATEGORY) {
            case Token::CAT_FUNC: {
                auto ft{std::static_pointer_cast<FuncToken>(token)};
                auto name{ft->NAME};
                auto arity{ft->ARITY};
                switch (ft->operate(values)) {
                    case FuncToken::ERR_ARITY:
                        auto size{static_cast<unsigned int>(values.size())};
                        values.clear();
                        throw ArityMismatchException(name, arity, size);
                        break;
                }
                break;
            }
            case Token::CAT_VALUE: {
                values.push_back(std::static_pointer_cast<ValueToken>(token));
                break;
            }
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
