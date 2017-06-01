// 9.exercise.13.rational.h

#include "std_lib_facilities.h"

#ifndef MATH_H
#define MATH_H

namespace Math {

class Rational {
    public:
        class ZeroQ { };            // q = 0 exception
        Rational(int p, int q);     // p/q constructor
        Rational(int n);            // n/1 (integer) constructor

        double float_point() const;       // conversion to double
        // Accessors
        int p() const { return m_p; };      
        int q() const { return m_q; };

        void simplify();    // reduce to lowest terms
    private:
        int m_p;  // the numerator
        int m_q;  // the denominator

        void normalize();   // normalize signs: reinterpret the rational 
                            // always with possitive denominator
};

// Rational class operators
Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);
bool operator==(const Rational& lhs, const Rational& rhs);  // Equality
ostream& operator<<(ostream& os, const Rational& r);
istream& operator>>(istream& is, Rational& r);

} // namespace Math

#endif
