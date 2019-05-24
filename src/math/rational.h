#include <stdio.h>
#include <iterator>

struct math::Rational;

namespace math {
struct Rational {
   private:
    int n;
    int d;

    void simplify();

   public:
    Rational(int n = 0, int d = 1);
    Rational(int i, int n, int d);

    Rational(Rational&&);
    Rational& operator=(Rational&&);
    Rational& operator=(int);

    operator double() const;

    int floor() const;
    float asFloat() const;
    int getImproperNum() const;
    int getMixedNum() const;
    int getDen() const;
    Rational getUnit() const;

    friend bool operator==(const Rational&, const Rational&);
    friend bool operator==(const Rational&, int);
    friend bool operator==(int, const Rational&);

    friend Rational operator+(const Rational&, const Rational&);
    friend Rational operator+(const Rational&, long);
    friend Rational operator+(long, const Rational&);

    Rational& operator+=(const Rational&);
    Rational& operator+=(long);

    Rational& operator++();
    Rational& operator++(int);

    Rational operator+();

    friend Rational operator-(const Rational&, const Rational&);
    friend Rational operator-(const Rational&, long);
    friend Rational operator-(long, const Rational&);

    Rational& operator-=(const Rational&);
    Rational& operator-=(long);

    Rational& operator--();
    Rational& operator--(int);

    Rational operator-();

    friend Rational operator*(const Rational&, const Rational&);
    friend Rational operator*(const Rational&, long);
    friend Rational operator*(long, const Rational&);

    Rational& operator*=(const Rational&);
    Rational& operator*=(long);

    friend Rational operator/(const Rational&, const Rational&);
    friend Rational operator/(const Rational&, long);
    friend Rational operator/(long, const Rational&);

    Rational& operator/=(const Rational&);
    Rational& operator/=(long);

    int intDiv(long) const;
    int intDiv(const Rational&) const;

    static Rational abs(const Rational&);
    Rational abs() const;
    Rational& absThis();

    static Rational sum(const Rational* arr, unsigned long size);
    static Rational sumProd(const Rational* a, const Rational* b,
                            unsigned long size);
    Rational& cumSum(const Rational* arr, unsigned long size);
};
}  // namespace math