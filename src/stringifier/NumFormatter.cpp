#include "calculator/NumFormatter.h"

namespace formatter {

DecimalPart::DecimalPart(int g, const std::string& separator)
    : group{g}, sep{separator} {}

void DecimalPart::push(char digit) {
    s.push_back(digit);
    if (++sinceLastSep == group) {
        s += sep;
        sinceLastSep = 0;
    }
}

void DecimalPart::reset() {
    sinceLastSep = 0;
    s.clear();
}

std::string DecimalPart::get() {
    if (sinceLastSep == 0) s.erase(s.size() - sep.size());
    return s;
}

}  // namespace formatter
