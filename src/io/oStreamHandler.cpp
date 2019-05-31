#include "oStreamHandler.h"
#include "../tokens/values/floatToken.h"
#include "../tokens/values/integerToken.h"

OStreamHandler::OStreamHandler(const Settings& settings, std::ostream& ostream,
                               IOMode ioMode)
    : SETTINGS(settings), stream{ostream}, sciStream{}, IO_MODE{ioMode} {}

const Settings& OStreamHandler::getSettings() const { return SETTINGS; }
std::ostream& OStreamHandler::getStream() const { return stream; }
IOMode OStreamHandler::getIOMode() const { return IO_MODE; }
void OStreamHandler::flush() const { stream.flush(); }

const OStreamHandler& OStreamHandler::operator<<(
    const ValueToken& token) const {
    const ValueToken::NumType& numType{token.getNumType()};

    if (numType == IntegerToken::TYPE_INTEGER) {
        auto integerToken{static_cast<const IntegerToken*>(&token)};
        std::string str{integerToken->toString()};

        if (SETTINGS.digitSep && SETTINGS.digitSepInterval)
            for (int size = str.size(), i = size - SETTINGS.digitSepInterval,
                     end = integerToken->getValue() < 0 ? 1 : 0;
                 i > end; i -= SETTINGS.digitSepInterval)
                str.insert(i, 1, SETTINGS.digitSep);

        stream << str;
        return *this;
    }

    if (numType == FloatToken::TYPE_FLOAT) {
        auto floatToken{static_cast<const FloatToken*>(&token)};
        std::string str{floatToken->toString()};

        if (SETTINGS.digitSep && SETTINGS.digitSepInterval) {
            int pos = str.find('.');
            for (int i = pos + SETTINGS.digitSepInterval + 1, size = str.size();
                 i < size; i += SETTINGS.digitSepInterval + 1) {
                str.insert(i, 1, SETTINGS.digitSep);
                ++size;
            }

            for (int j = pos - SETTINGS.digitSepInterval,
                     end = floatToken->isNeg();
                 j > end; j -= SETTINGS.digitSepInterval)
                str.insert(j, 1, SETTINGS.digitSep);
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