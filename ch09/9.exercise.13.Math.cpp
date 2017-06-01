// 9.exercise.13.Math.cpp

#include "9.exercise.13.Math.h"

namespace Math {

// Rational constructors

Rational::Rational(int p, int q) : m_p{p}, m_q{q}
{
    if (q == 0) throw ZeroQ{};
    normalize();    // normalize signs
}

Rational::Rational(int n) : m_p{n}, m_q{1}
{
    normalize();    // normalize signs
};

double Rational::float_point() const
{
    return double(m_p)/m_q;
}

void Rational::simplify()
{
    // Not for now. In need if a prime factorization algorithm ...
}

void Rational::normalize()
{
    if (m_q < 0) {  // if denominator is negative do it possitive
        m_q = -m_q;
        m_p = -m_p; // and change the sign of numerator
    }
    // and simplify() if implemented? I think so ...
}

// Rational class operators

bool operator==(const Rational& lhs, const Rational& rhs)
{
    return ((lhs.p()*rhs.q()) == (lhs.q()*rhs.p()));
}


ostream& operator<<(ostream& os, const Rational& r)
{
    os << r.p() << '/' << r.q();
    return os;
}
} // namespace Math
