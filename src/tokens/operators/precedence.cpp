#include "precedence.h"
#include "calculator/Precedence.h"

Precedence::Precedence(short level, Precedence::Associativity assoc)
    : assoc{assoc}, level{level} {};

Precedence::operator short() const { return level; }
short Precedence::getLevel() const { return level; }
void Precedence::setLevel(short newLevel) { level = newLevel; }

bool operator==(Precedence& a, Precedence& b) {
    return a.level == b.level && a.assoc == b.assoc;
}

bool operator!=(Precedence& a, Precedence& b) {
    return a.level != b.level || a.assoc != b.assoc;
}

bool operator>(Precedence& a, Precedence& b) {
    return a.level > b.level || a.assoc > b.assoc;
}

bool operator<(Precedence& a, Precedence& b) {
    return a.level < b.level || a.assoc < b.assoc;
}

bool operator>=(Precedence& a, Precedence& b) {
    return a.level > b.level || (a.level == b.level && a.assoc >= b.assoc);
}

bool operator<=(Precedence& a, Precedence& b) {
    return a.level < b.level || (a.level == b.level && a.assoc <= b.assoc);
}

namespace refactor {
Precedence::Precedence(int nominal, Precedence::Associativity a)
    : precd{nominal}, assoc{a} {}

Precedence Precedence::l2r(int precd) {
    return {precd, Precedence::Associativity::L2R};
}

Precedence Precedence::r2l(int precd) {
    return {precd, Precedence::Associativity::R2L};
}

bool Precedence::isL2R() const noexcept {
    return assoc == Precedence::Associativity::L2R;
}

bool Precedence::isR2L() const noexcept {
    return assoc == Precedence::Associativity::R2L;
}

std::ostream& operator<<(std::ostream& stream, Precedence p) {
    stream << "Precedence(" << p.precd
           << (p.isL2R() ? ".5, left2right)" : ", right2left)");
    return stream;
}

bool operator==(Precedence a, Precedence b) {
    return a.precd == b.precd && a.assoc == b.assoc;
}

bool operator!=(Precedence a, Precedence b) {
    return a.precd != b.precd || a.assoc != b.assoc;
}

bool operator>(Precedence a, Precedence b) {
    return a.precd > b.precd || (a.precd == b.precd && a.assoc > b.assoc);
}

bool operator<(Precedence a, Precedence b) {
    return a.precd < b.precd || (a.precd == b.precd && a.assoc < b.assoc);
}

bool operator>=(Precedence a, Precedence b) {
    return a.precd > b.precd || (a.precd == b.precd && a.assoc >= b.assoc);
}

bool operator<=(Precedence a, Precedence b) {
    return a.precd < b.precd || (a.precd == b.precd && a.assoc <= b.assoc);
}

}  // namespace refactor