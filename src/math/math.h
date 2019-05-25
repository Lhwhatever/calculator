namespace math {

template <typename T>
T gcd(T a, T b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

template <typename T, typename T_ = double>
bool approxEquals(T x, T y, T_ relEpsilon = 1e-8, T_ absEpsilon = 1e-12) {
    T diff = fabs(x - y);
    if (diff <= absEpsilon) return true;
    return diff <= ((fabs(x) < fabs(y) ? fabs(y) : fabs(x)) * relEpsilon);
};

}  // namespace math