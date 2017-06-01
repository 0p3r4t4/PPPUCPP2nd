// 9.exercise.13.cpp
//
//  Design and implement a rational number class, Rational. A rational number
//  has two parts: a numerator and a denonminator, for example, 5/6
//  (five-sixths, also known as approximately .83333). Look up the definition
//  if you need to. Provide assignment, addition, substraction, multiplication,
//  division and equality operators. Also, provide a conversion to double. Why
//  would people want to use a Rational class?
//
// COMMENTS
//
//  I won't take care of integer overflows this time. I'll keep it simple.
//
//  One reason people may want to use a Rational class is that it let us, I
//  guess, implement a better subset of real numbers than floating point
//  representation.

#include "std_lib_facilities.h"
#include "9.exercise.13.Math.h"

int main()
try
{
    Math::Rational a{25, 12};
    Math::Rational b{-50, -24};
    if (a == b) cout << a << " equals " << b << '\n';
    
    b = Math::Rational{12};
    if (!(a == b)) cout << a << " does not equal " << b << '\n';

    b = Math::Rational{12, -4};
    cout << "12/(-4) after normalization is " << b << '\n';

    b = Math::Rational{-100, 3};
    cout << b << " interpreted as floating point is "
         << b.float_point() << '\n';

    b = Math::Rational{-100, 0};

    return 0;
}
catch(Math::Rational::ZeroQ& e)
{
    cerr << "Math::Rational::ZeroQ exception: denominator couldn't be 0.\n";
    return 1;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 2;
}
catch(...)
{
    cerr << "Unknown exception!!\n";
    return 3;
}
