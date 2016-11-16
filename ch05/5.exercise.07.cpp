// 5.exercise.07.cpp
//
// Quadratic equations are of the form
//
//      a · x² + b · x + c = 0
//
// To solve these, one uses the quadratic formula:
//
//      x = (-b ± sqrt(b² - 4ac)) / 2a
//
// There is a problem, though: if b² - 4ac is less than zero, then it will
// fail. Write a program that calculate x for a quadratic equation. Create
// a function that prints out the roots of a quadratic equation, given a, b, c.
// When the program detects an equation with no real roots, have it print out
// a message. How do you know that your results are plausible? Can you check
// that they are correct?
//
// Comments:
//  We can view the results from the interpretation of a, b, and c in the 
//  function f(x)=a·x²+b·x+c, as plotted.
//  The most important coefficient is b:
//      - when is zero, the solutions are symmetrical: x1 = -x2.
//      - when greater than zero the solutions tend to the negative.
//        A positive root will be less than the absolute of the negative
//        solutions. And usually the two roots will be negative.
//      - when less than zero the solutions tend to the positive.
//  This way we can estimate if the solutions make sense or not.
//
//  We can check if they are correct if they comply with the equation. The
//  problem to this is the floating point precision, and that zero is
//  not always zero but a very very small number.
//  We get to the same problem as stated in Fragment 21 of 5.drill.cpp, and to
//  re-read
//  https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
//
#include "std_lib_facilities.h"

const string ex_no_quadratic_msg = "You have not specified a quadratic equation (a = 0)";
const string ex_no_real_roots_msg = "The quadratic equation has no real roots";
const string ex_wrong_result_msg = "The solutions do not comply the equation";
const string ex_bad_input_msg = "I don't understand your input, sorry!";

void quadratic_roots(double a, double b, double c)
// Prints, if they exist, the real roots of quadratic equation a·x² + b·x + c = 0
// pre-conditions:
//          a could not be zero
//          b² must be greater or equal to 4ac
// post-conditions
//          obtained roots must comply with original quadratic equation
{
    if (a == 0) throw runtime_error(ex_no_quadratic_msg);
    if (b*b < 4*a*c) throw runtime_error(ex_no_real_roots_msg);

    double sqrt_term = sqrt(b*b - 4*a*c);
    double x1 = (-b + sqrt_term) / (2*a);
    double x2 = (-b - sqrt_term) / (2*a);

    // Some complications to write the equation with the correct signs
    cout << "Solutions to quadratic equation " << a << "·x²";
    if (b != 0) {
        if (b > 0) cout << " + " << b << "·x";
        else cout << " - " << -b << "·x";
    }
    if (c != 0) {
        if (c > 0) cout << " + " << c;
        else cout << " - " << -c;
    }
    cout << " = 0, are: x = " << x1 << " and x = " << x2 << '\n';

    // Does the results comply with the equation?
    double s1 = a*x1*x1 + b*x1 + c;
    double s2 = a*x2*x2 + b*x2 + c;

    cout << s1 << ' ' << s2 << '\n';
    
    if (s1 != 0.0 || s2 != 0.0) throw runtime_error(ex_wrong_result_msg);
}

int main()
try
{
    double a = 0;
    double b = 0;
    double c = 0;

    cout << "Insert the coefficients a, b and c of a quadratic equation (a·x² + b·x + c = 0)\n> ";
    while (cin >> a >> b >> c) {
        quadratic_roots(a, b, c);
        cout << "> ";
    }
    if (cin.eof())
        cout << "Bye, bye!\n";
    else
        throw runtime_error(ex_bad_input_msg);

    return 0;
}
catch (exception& e)
{
    cout << "Error: " << e.what() << '\n';
    return 2;
}
catch (...)
{
    cout << "Unknown expception!\n";
    return 1;
}
