#include "math.h"

#include <cmath>

namespace math {

bool approxEquals(double x, double y, double relEpsilon, double absEpsilon) {
    double diff = fabs(x - y);
    if (diff <= absEpsilon) return true;
    return diff <= ((fabs(x) < fabs(y) ? fabs(y) : fabs(x)) * relEpsilon);
}

}  // namespace math