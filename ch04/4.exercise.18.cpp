// 4.exercise.18.cpp
//
// Write a program to solve quadratic equations. A quadratic equation is of the
// form:    ax^2 + bx + c = 0
// If you don't know the quadratic formula for solving such an expression, do
// some research. Remenber, researching how to solve a problem is often
// necessary before a programmer can teach the computer how to solve it. Use
// doubles for the user input for a, b and c. Since there are two solutions to
// a quadratic equation, output both x1 and x2.
//
// Comments:
//  If my elementary school memories are right, x = (-b +- sqrt(b^2 - 4ac))/2a
//  Also that this expression implies that a != 0. If a == 0, then it's not
//  a quadratic equation.
//  We already know the existencde of sqrt() function in C++, and the
//  value returned by this function is the nonnegative square root (man says).
//  So ...

#include "std_lib_facilities.h"

int main()
{
    double a {0}; 
    double b {0}; 
    double c {0}; 

    cout << "Insert the coefficients a, b and c of a quadratic equation (ax^2 + bx + c = 0):\n";
    cin >> a >> b >> c;

    if (a == 0) {
        cout << "If coefficient a equals 0, this is not a quadratic equation.\n";
    } else {
        // if (b*b - 4*a*c) is negative, the solution is imaginary.
        // In that case current float point operation results in a NaN (not
        // a number) that propagates on further expressions.
        double sqrt_term {sqrt(b*b - 4*a*c)};
        double x1 {(-b + sqrt_term) / (2 * a)};
        double x2 {(-b - sqrt_term) / (2 * a)};
        cout << "The solutions for the quadratic equation " << a << "x^2";
        // Some nested if-statement play to format the equation.
        if (b != 0) {
            if (b > 0) cout << " + " << b << "x";
            else cout << " - " << -b << "x";
        }
        if (c != 0) {
            if (c > 0) cout << " + " << c;
            else cout << " - " << -c;
        }
        cout << " = 0, are: x = " << x1 << " and x = " << x2 << '\n';
    }
    return 0;
}
