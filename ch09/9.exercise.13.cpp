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
//  I will try to implement a Rational::reduce() to represent the rational
//  number in its irreductible form. For this I will use the Euclidean
//  algorithm to find the greatest common divisor (GCD), in detriment of prime
//  factorizaton method. References:
//      - https://en.wikipedia.org/wiki/Rational_number
//      - https://en.wikipedia.org/wiki/Irreducible_fraction
//      - https://en.wikipedia.org/wiki/Euclidean_algorithm
//
//  I won't take care of integer overflows this time. I'll keep it simple. An
//  advantage of having Rational::reduce() is that as we operate on
//  rationals their terms do not grow indefinitely. So we keep terms the
//  smallest we can and do not easily reach the point where overflows,
//  otherwise, will happen for sure after a moderate number of operations.
//  
//  Rational numbers are a set of mathematical study itself, so it will
//  interest mathematicians and more people out there. Also, well implemented,
//  I guess they don't exhibit the cumulative error on calculations that float
//  point numbers suffer.

#include "std_lib_facilities.h"
#include "9.exercise.13.Math.h"

int main()
try
{
    // Test normalize/reduce/equality
    Math::Rational a{25, 12};
    Math::Rational b{-50, -24};
    if (a == b) cout << a << " equals " << b << '\n';
    b = Math::Rational{12};
    if (!(a == b)) cout << a << " does not equal " << b << '\n';

    // Test normalize/reduce
    b = Math::Rational{12, -4};
    cout << "12/(-4) after normalization is " << b << '\n';
    b = Math::Rational{120, 90};
    cout << "120/90 normalized and reduced is " << b << '\n';
    b = Math::Rational{90, -120};
    cout << "90/120 normalized and reduced is " << b << '\n';
    b = Math::Rational{1071, 462};
    cout << "1071/462 normalized and reduced is (should be 51/22) " << b << '\n';
    b = Math::Rational{-105, 252};
    cout << "-105/252 normalized and reduced is (should be -5/12) " << b << '\n';
    
    // Test floating point conversion
    b = Math::Rational{-100, 3};
    cout << b << " interpreted as floating point is "
         << b.float_point() << '\n';

    // Test addition
    a = Math::Rational{3, 4};
    b = Math::Rational{2, 4};
    cout << a << " + " << b << " = " << a+b << '\n';
    Math::Rational c;
    Math::Rational d;
    c = Math::Rational{-123, 42};
    d = Math::Rational{245, 81};
    cout << c << " + " << d << " = " << c+d << '\n';

    // Test substraction/multiplication/division
    cout << a << " - " << b << " = " << a-b << '\n';
    cout << a << " * " << b << " = " << a*b << '\n';
    cout << a << " / " << b << " = " << a/b << '\n';
    cout << c << " - " << d << " = " << c-d << '\n';
    cout << c << " * " << d << " = " << c*d << '\n';
    cout << c << " / " << d << " = " << c/d << '\n';

    // Test >> operator
    cout << "Type some fractions:\n";
    while (cin >> a) cout << '\t' << a << '\n';
    cout << "Format error or Ctrl+D pressed\n";

    // Forced errors
    //b = Math::Rational{-100, 0};
    //b = Math::Rational{1}/Math::Rational{};

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
