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

bool approxEquals(double x, double y, double relEpsilon = 1e-8,
                  double absEpsilon = 1e-12);

}  // namespace math