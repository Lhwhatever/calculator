#include "session.h"

#include "except/interruptException.h"
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
      tokenizer{settings, errCode} {
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
                if (std::static_pointer_cast<FuncToken>(token)->operate(
                        values, errCode))
                    return values;
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
        ostream << *stack[0] << '\n';
        return;
    }

    /*if (settings.exprSyntax != Settings::SYNTAX_RPN)
        throw SyntaxException{"more arguments than required by operators"};*/

    ostream << '(' << *stack[0];
    for (auto it = ++(stack.cbegin()), end = stack.cend(); it != end; ++it) {
        ostream << ", " << **it;
    }
    ostream << ")\n";
}

void Session::rep() {
    try {
        tokenize(read());

        auto values{evaluateTokens()};
        if (errCode) {
            errstream << errCode << '\n';
            tokenQueue.clear();
            errCode.clear();
            return;
        }

        displayResults(values);
    } catch (InterruptException&) {
        throw;
    } catch (std::exception& e) {
        errstream << "[Error] " << e.what() << '\n';
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
