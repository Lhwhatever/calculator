#include "package.h"

#include <string.h>
#include <stdexcept>
#include <utility>

std::map<const std::string, PackageR> Package::packages{};

Package::Package(std::string name, Callback onInit, Callback onPreload,
                 Callback onLoad)
    : NAME{name},
      latexMap{},
      plainMap{},
      onInit{onInit},
      onPreload{onPreload},
      onLoad{onLoad} {
    packages.insert_or_assign(NAME, std::ref(*this));
}

byte Package::addOperator(const OperatorToken& op) {
    auto opR{std::ref(op)};
    auto idPlain{op.getPlainIdentifier()};
    byte out{'\0'};
    if (idPlain.compare("")) {
        auto [a, b] = plainMap.insert_or_assign(idPlain, opR);
        a;
        if (b) out |= 0b01;
    }

    auto [a, b] = latexMap.insert_or_assign(op.getLaTeXIdentifier(), opR);
    a;
    if (b) out |= 0b10;

    return out;
    // Return value: 0b01 if no operator was overwritten in plainMap
    //               0b10 if no operator was overwritten in latexMap
}
