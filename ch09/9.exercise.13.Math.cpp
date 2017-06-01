// 9.exercise.13.Math.cpp

#include "9.exercise.13.Math.h"

namespace Math {

// Math functions
int gcd(int a, int b) 
// Find greatest common divisor by Euclidean algorithm
// See: https://en.wikipedia.org/wiki/Euclidean_algorithm
{
    a = abs(a);     // we need natural (positive numbers)
    b = abs(b);
    if (b > a) swap(a, b);  // we need a to be the greatest of both

    while (b != 0) {
        int t{b};
        b = a % b;
        a = t;
    }

    return a;
}

// Rational constructors

Rational::Rational(int p, int q) : m_p{p}, m_q{q}
{
    if (q == 0) throw ZeroQ{};
    normalize();    // normalize signs
    reduce();       // to irreducible fraction
}

Rational::Rational(int n) : m_p{n}, m_q{1}
{
    normalize();    // normalize signs
    reduce();       // to irreducible fraction
};

Rational::Rational() : m_p{0}, m_q{1} { };

double Rational::float_point() const
{
    return double(m_p)/m_q;
}

void Rational::normalize()
{
    if (m_q < 0) {  // if denominator is negative do it possitive
        m_q = -m_q;
        m_p = -m_p; // and change the sign of numerator
    }
}

void Rational::reduce()
// Express the rational in its irreducible fraction
{
    int cd{gcd(m_p, m_q)};

    m_p /= cd;
    m_q /= cd;
}

// Rational class operators
Rational operator+(const Rational& lhs, const Rational& rhs)
{
    int p{(lhs.p() * rhs.q()) + (lhs.q() * rhs.p())};
    int q{lhs.q() * rhs.q()};
    
    return Rational{p, q};
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
    int p{(lhs.p() * rhs.q()) - (lhs.q() * rhs.p())};
    int q{lhs.q() * rhs.q()};
    
    return Rational{p, q};
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
    int p{lhs.p() * rhs.p()};
    int q{lhs.q() * rhs.q()};
    
    return Rational{p, q};
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
    if (rhs.p() == 0) throw Rational::ZeroQ{};
    
    int p{lhs.p() * rhs.q()};
    int q{lhs.q() * rhs.p()};
    
    return Rational{p, q};
}

bool operator==(const Rational& lhs, const Rational& rhs)
{
    return ((lhs.p()*rhs.q()) == (lhs.q()*rhs.p()));
}


ostream& operator<<(ostream& os, const Rational& r)
{
    os << r.p() << '/' << r.q();
    return os;
}

istream& operator>>(istream& is, Rational& r)
{
    int p, q;
    char c;
    is >> p >> c >> q;
    if (!is) return is;
    if (c != '/') {                   // format error
        is.clear(ios_base::failbit);  // set the fail bit
        return is;
    }
    r = Rational{p, q};

    return is;
}

} // namespace Math
