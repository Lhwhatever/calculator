#include "rational.h"

#include <sstream>

#include "exceptions/divideByZeroException.h"
#include "math.h"

namespace math {
Rational::Rational(int num, int den) : n{num}, d{den} {
    if (den == 0)
        throw DivideByZeroException{
            "illegal for denominator of rational number to be zero"};

    if (den < 0) num = -num;
    simplify();
}

Rational::Rational(int whole, int num, int den)
    : Rational{num + whole * den, den} {}

Rational::Rational(Rational&& r) {
    n = r.n;
    d = r.d;
    r.n = 0;
    r.d = 1;
}

Rational& Rational::operator=(Rational&& r) {
    if (&r == this) return *this;

    n = r.n;
    d = r.d;
    r.n = 0;
    r.d = 1;
    return *this;
}

Rational& Rational::operator=(int x) {
    n = x;
    d = 1;
    return *this;
}

Rational::operator double() const {
    double x = n;
    return x / d;
}

int Rational::floor() const { return n / d; }

float Rational::asFloat() const {
    float x = n;
    return x / d;
}

std::string Rational::asString() const {
    std::ostringstream ss;
    ss << n << '/' << d;
    return ss.str();
}

Rational::operator std::string() const { return asString(); }

std::ostream& operator<<(std::ostream& stream, const Rational& x) {
    stream << "Rational(" << x.n << ", " << x.d << ')';
    return stream;
}

bool operator==(const Rational& x, const Rational& y) {
    return (x.n == y.n) && (x.d == y.d);
}

bool operator==(const Rational& x, int y) { return (x.d == 1) && (x.n == y); }
bool operator==(int y, const Rational& x) { return (x.d == 1) && (x.n == y); }

int Rational::getImproperNum() const { return n; }
int Rational::getMixedNum() const {
    return (n > 0) ? std::abs(n) % d : -(std::abs(n) % d);
}

int Rational::getDen() const { return d; }

Rational Rational::getUnit() const { return Rational(1, d); }

Rational operator+(const Rational& x, const Rational& y) {
    return (x.d == y.d) ? Rational(x.n + y.n, x.d)
                        : Rational(x.n * y.d + y.n * x.d, x.d * y.d);
}

Rational operator+(const Rational& x, long y) {
    return Rational(x.n + y * x.d, x.d);
}

Rational operator+(long y, const Rational& x) {
    return Rational(x.n + y * x.d, x.d);
}

Rational& Rational::operator+=(const Rational& x) {
    if (d == x.d) {
        n += x.n;
        return *this;
    }

    n = n * x.d + x.n * d;
    d *= x.d;
    simplify();
    return *this;
}

Rational& Rational::operator+=(long x) {
    n += d * x;
    return *this;
}

Rational& Rational::operator++() {
    n += d;
    return *this;
}

Rational& Rational::operator++(int) {
    n += d;
    return *this;
}

Rational Rational::operator+() { return Rational(n, d); }

Rational operator-(const Rational& x, const Rational& y) {
    return (x.d == y.d) ? Rational(x.n - y.n, x.d)
                        : Rational(x.n * y.d - y.n * x.d, x.d * y.d);
}

Rational operator-(const Rational& x, long y) {
    return Rational(x.n - y * x.d, x.d);
}
Rational operator-(long x, const Rational& y) {
    return Rational(x * y.d - y.n, y.d);
}

void Rational::simplify() {
    int f{gcd(std::abs(n), d)};
    n /= f;
    d /= f;
}

Rational& Rational::operator-=(const Rational& x) {
    if (d == x.d) {
        n -= x.n;
        return *this;
    }

    n = n * x.d - x.n * d;
    d *= x.d;
    simplify();
    return *this;
}

Rational& Rational::operator-=(long x) {
    n -= d * x;
    return *this;
}

Rational& Rational::operator--() {
    n -= d;
    return *this;
}

Rational& Rational::operator--(int) {
    n -= d;
    return *this;
}

Rational Rational::operator-() { return Rational(-n, d); }

Rational operator*(const Rational& x, const Rational& y) {
    return Rational(x.n * y.n, x.d * y.d);
};

Rational operator*(const Rational& x, long y) {
    return Rational(x.n * y, x.d);
};
Rational operator*(long y, const Rational& x) {
    return Rational(x.n * y, x.d);
};

Rational& Rational::operator*=(const Rational& x) {
    n *= x.n;
    d *= x.d;
    simplify();
    return *this;
}

Rational& Rational::operator*=(long x) {
    n *= x;
    simplify();
    return *this;
}

Rational operator/(const Rational& x, const Rational& y) {
    return Rational(x.n * y.d, x.d * y.n);
};

Rational operator/(const Rational& x, long y) {
    return Rational(x.n, x.d * y);
};

Rational operator/(long x, const Rational& y) {
    return Rational(x * y.d, y.n);
};

Rational& Rational::operator/=(const Rational& x) {
    n *= x.d;
    d *= x.n;
    simplify();
    return *this;
}

Rational& Rational::operator/=(long x) {
    d *= x;
    simplify();
    return *this;
}

int Rational::intDiv(long x) const { return n / (d * x); }

int Rational::intDiv(const Rational& x) const { return (n * x.d) / (d * x.n); }

Rational Rational::abs(const Rational& x) {
    return Rational(std::abs(x.n), x.d);
}

Rational Rational::abs() const { return Rational(std::abs(n), d); };
Rational& Rational::absThis() {
    if (n < 0) n = -n;
    return *this;
}

Rational Rational::sum(const Rational* ptr, unsigned long size) {
    long n{0}, d{1};
    for (unsigned long i = 0; i < size; ++i) {
        n = n * ptr->d + d * ptr->n;
        d *= ptr->d;
        ++ptr;
    }
    long f{gcd(std::abs(n), d)};
    return Rational(n / f, d / f);
}

Rational Rational::sumProd(const Rational* a, const Rational* b,
                           unsigned long size) {
    long n{0}, d{1};
    for (unsigned long i = 0; i < size; ++i) {
        long xn{a->n * b->d + b->n * a->d}, xd{a->d * b->d};
        n = n * xd + d * xn;
        d *= xd;
        ++a;
        ++b;
    }
    long f{gcd(std::abs(n), d)};
    return Rational(n / f, d / f);
}

Rational& Rational::cumSum(const Rational* ptr, unsigned long size) {
    long num{n}, den{d};
    for (unsigned long i = 0; i < size; ++i) {
        num = num * ptr->d + den * ptr->n;
        den *= ptr->d;
        ++ptr;
    }
    long f{gcd(std::abs(num), den)};
    n = num / f;
    d = den / f;
    return *this;
}
}  // namespace math