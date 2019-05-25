#ifndef CALC__IO__OUTPUT_STREAM_HANDLER_H_
#define CALC__IO__OUTPUT_STREAM_HANDLER_H_

#include <stdio.h>

#include "../settings.h"
#include "../tokens/operators/operatorToken.h"
#include "ioModes.h"

class OStreamHandler {
    const Settings& SETTINGS;
    std::ostream& stream;
    const IOMode IO_MODE;

   public:
    OStreamHandler(const Settings& settings, std::ostream& ostream,
                   IOMode ioMode);

    const Settings& getSettings() const;
    std::ostream& getStream() const;
    IOMode getIOMode() const;
    void flush() const;

    const OStreamHandler& operator<<(const ValueToken&) const;
    const OStreamHandler& operator<<(const std::string&) const;
    const OStreamHandler& operator<<(char) const;
};

#endif