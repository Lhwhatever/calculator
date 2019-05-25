#include "oStreamHandler.h"
#include "../tokens/values/integerToken.h"

OStreamHandler::OStreamHandler(const Settings& settings, std::ostream& ostream,
                               IOMode ioMode)
    : SETTINGS{settings}, stream{ostream}, IO_MODE{ioMode} {}

const Settings& OStreamHandler::getSettings() const { return SETTINGS; }
std::ostream& OStreamHandler::getStream() const { return stream; }
IOMode OStreamHandler::getIOMode() const { return IO_MODE; }
void OStreamHandler::flush() const { stream.flush(); }

const OStreamHandler& OStreamHandler::operator<<(
    const ValueToken& token) const {
    const ValueToken::NumType numType{token.getNumType()};

    auto integerToken{dynamic_cast<const IntegerToken*>(&token)};
    if (integerToken) {
        std::string str{integerToken->toString()};

        if (SETTINGS.digitSep != "" && SETTINGS.digitSepInterval != 0) {
            for (int i = str.size() - SETTINGS.digitSepInterval,
                     end = integerToken->getValue() < 0 ? 1 : 0;
                 i > end; i -= SETTINGS.digitSepInterval)
                str.insert(i, SETTINGS.digitSep);
        }

        stream << str;
        return *this;
    }

    return *this;
}

const OStreamHandler& OStreamHandler::operator<<(
    const std::string& string) const {
    stream << string;
    return *this;
}

const OStreamHandler& OStreamHandler::operator<<(char c) const {
    stream << c;
    return *this;
}