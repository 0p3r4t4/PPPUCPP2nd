// 5.exercise.07.cpp
//
// Quadratic equations are of the form
//
//      a·x² + b·x + c = 0
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
//
//  Firstly, I want the user to enter coefficients and resolve quadratic
//  equations while he wants. From this point of view, if the coefficients
//  result on a violation of pre and post-conditions, I don't consider it an
//  error but an unsolvable equation. The program do not terminate and the user
//  can continue, after being conveniently informed.
//  So I throw exceptions for this conditions but caught them on the function,
//  not in the main body. I'm not sure if it's right or not, but the work is
//  done.
//
//  How do you know that your results are plausible?
//
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
//  Can you check that they are correct?
//
//  Short answer, yes. But it's not so easy.
//  We can check if they are correct if they comply with the equation. The
//  problem to this is the floating point precision, and that we don't always
//  get a zero but a very very small number.
//  We get to the same problem as stated in Fragment 21 of 5.drill.cpp, and to
//  re-read and freshly read:
//
//      - https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
//      - "What Every Computer Scientist Should Know About Floating-Point
//      Arithmetic", David Goldberg, 1991 (broadly available on internet)
//      - "Numerical Analysis - Fifth Edition", Richard L. Burden and J.
//      Douglas Faires, 1993 (An old book from my college days)
//
//  Summarizing, what we do with floating-point arithetic is approximate an
//  infinite set of numbers (Reals) with a finite set of binary numbers. So
//  a floating-point number do not represent a real number but a range of them.
//  So we face rounding errors, cancellation effects and so on.
//  I will not bore you but I learn that, to obtain better results on
//  floating-point arithmetic, we must think about arrangement of operations.
//
//  On the two referenced text, a quadratic equation case is exposed, and that
//  bring me to quadratic_roots_2() function and to compare the "simple"
//  solution with a rearrangement of the formula denpending on the coefficients
//  and their mutual relationships. This rearrangement consists on rationalize
//  the denominator of the formula. Feel free to search about it, but is
//  clearly explained on David Goldberg's text.
//  Despite of this, results from both functions do not differ by large
//  working with double type (you need to print at least 15 decimals to view
//  differences, sometimes).
//
//  What is more interesting is that polynomials should always be evaluated on
//  its nested forms, so:
//      a*x*x + b*x + c
//  is evaluated as:
//      (a*x + b)*x +c
//  thus minimizing the operations and the possible errors accumulated by them.
//  And it's true that the nested form bring us more precise results. In our
//  case, the results are 0 more often and consistently nearer to 0 than
//  with the original form.
//
//  But they're not always zero, and we are somehow at the start again. So we
//  consider a number (epsilon) to resolve if the error is assumeable. Somehow
//  arbitrarily I choose 1e-12 as this number.
//
//  Enough.

#include "std_lib_facilities.h"

const string ex_no_quadratic_msg = "You have not specified a quadratic equation (a = 0)";
const string ex_no_real_roots_msg = "The quadratic equation has no real roots";
const string ex_wrong_result_msg = "The solutions do not comply the equation";
const string ex_bad_input_msg = "I don't understand your input, sorry!";

constexpr double epsilon = 1e-12;   // Numbers below this are considered zero
constexpr double scale = 10;        // multiplier to determine when a number is
                                    // much greater than other, i.e,
                                    // b > scale*a => b >> a.

void quadratic_roots(double a, double b, double c)
// Prints, if they exist, the real roots of quadratic equation a·x² + b·x + c = 0
// pre-conditions:
//          a could not be zero
//          b² must be greater or equal to 4ac
// post-conditions
//          obtained roots must comply with original quadratic equation
try
{
    if (a == 0) throw runtime_error(ex_no_quadratic_msg);
    if (b*b < 4*a*c) throw runtime_error(ex_no_real_roots_msg);

    double sqrt_term = sqrt(b*b - 4*a*c);
    double x1 = (-b + sqrt_term) / (2*a);
    double x2 = (-b - sqrt_term) / (2*a);

    // Do the results comply with the equation? We evaluate the polynomial
    double p1 = a*x1*x1 + b*x1 + c;
    double p2 = a*x2*x2 + b*x2 + c;

    cout << "\tquadratic_roots()\t" << fixed << x1 << '\t' << x2 << defaultfloat << "\t(" << p1 << ", " << p2 << ")\n";
    
    // Post-condition
    if (p1 > epsilon || p2 > epsilon) throw runtime_error(ex_wrong_result_msg);
}
catch (exception& e)
{
    cout << "\tquadratic_roots() Exception: " << e.what() << '\n';
}

void quadratic_roots_2(double a, double b, double c)
// Prints, if they exist, the real roots of quadratic equation a·x² + b·x + c = 0
// pre-conditions:
//          a could not be zero
//          b² must be greater or equal to 4ac
// post-conditions
//          obtained roots must comply with original quadratic equation
try
{
    if (a == 0) throw runtime_error(ex_no_quadratic_msg);
    if (b*b < 4*a*c) throw runtime_error(ex_no_real_roots_msg);

    double sqrt_term = sqrt(b*b - 4*a*c);
    double x1 = 0;
    double x2 = 0;

    // Get roots depending on magnitude of coefficients to minimize
    // cancellation effects on floating-point arithmetic. See head of the 
    // file comments. We consider to be much greater an order of magnitude.
    if ( b*b > scale*a*c ) {
        if (b >= 0) {
            x1 = (2*c) / (-b - sqrt_term);
            x2 = (-b - sqrt_term) / (2*a);
        }
        else {
            x1 = (-b + sqrt_term) / (2*a);
            x2 = (2*c) / (-b + sqrt_term);
        }
    }
    else {
        x1 = (-b + sqrt_term) / (2*a);
        x2 = (-b - sqrt_term) / (2*a);
    }

    // Do the results comply with the equation? We evaluate the polynomial
    // We use the nested form of the polynomial to minimize operations
    // and thus, the accumulated rounding error
    double p1 = (a*x1+b)*x1+c;
    double p2 = (a*x2+b)*x2+c;

    cout << "\tquadratic_roots_2()\t" << fixed << x1 << '\t' << x2 << defaultfloat << "\t(" << p1 << ", " << p2 << ")\n";

    // Post-condition 
    if (p1 > epsilon || p2 > epsilon) throw runtime_error(ex_wrong_result_msg);
}
catch (exception &e)
{
    cout << "\tquadratic_roots2() Exception: " << e.what() << '\n';
}

int main()
try
{
    double a = 0;
    double b = 0;
    double c = 0;

    cout << "Insert the coefficients a, b and c of a quadratic equation (a·x² + b·x + c = 0)\n> ";
    while (cin >> a >> b >> c) {
        // Some complications to write the equation with the correct signs
        cout << "Roots of quadratic equation " << a << "x²";
        if (b != 0) {
            if (b > 0) cout << " + " << b << "x";
            else cout << " - " << -b << "x";
        }
        if (c != 0) {
            if (c > 0) cout << " + " << c;
            else cout << " - " << -c;
        }
        cout << " = 0, and their evaluations (p1, p2) are: \n\n";
        cout << "\tFunction\t\tx1\t\tx2\t\t(p1, p2)\n";
        cout << "\t=============================================================================\n";
        quadratic_roots(a, b, c);
        quadratic_roots_2(a, b, c);
        cout << "\n> ";
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
