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
std::ostream& operator<<(std::ostream& stream, Precedence p) {
    stream << "Precedence(" << (p.val >> 1u)
           << (p.isL2R() ? ".5, left2right)" : ", right2left)");
    return stream;
}

}  // namespace refactor