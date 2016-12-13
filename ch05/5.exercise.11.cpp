// 5.exercise.10.cpp
//
// Write a program that writes out the first so many values of the Fibonacci
// series, that is, the series that starts with 1 1 2 3 5 8 13 21 34. The next
// number of the series is the sum of the two previous ones. Find the largest
// Fibonacci nomber that fits in an int.
//
// Comments:
//  Since we control the int overflow, is easy to determine by test that only
//  the 46 first Fibbonaci numbers can be represented by an int, being the
//  greatest of them 1836311903.

#include "std_lib_facilities.h"

const string ex_bad_input_msg = "You entered something that's not an integer!";
const string ex_not_interested_msg = "That number of values tell me that you're not "
                                     "actually interested on Fibonacci series ...";
const string ex_overflow_msg = "The next Fibonacci value could not be stored on an int.";
                                     
int main()
try
{
    int fib_no = 0;
    cout << "Please insert the number of values of the Fibonacci series that "
         << "yout want to be printed: ";
    cin >> fib_no;
    if (!cin) throw runtime_error(ex_bad_input_msg);
    if (fib_no < 1) throw runtime_error(ex_not_interested_msg);

    int fib0 = 1;
    int fib1 = 1;

    if (fib_no >= 1) cout << "Fib(1)\t" << fib0 << '\n';
    if (fib_no >= 2) cout << "Fib(2)\t" << fib1 << '\n';
    
    for (int i = 3; i <= fib_no; ++i) {
        int tmp = fib0 + fib1;
        // If the add causes the result to be less, there is an overflow
        if (tmp < fib1) throw runtime_error(ex_overflow_msg);
        fib0 = fib1;
        fib1 = tmp;
        cout << "Fib(" << i << ")\t" << fib1 << '\n';
    }

    cout << "\nBye!\n";
}
catch(exception& e)
{
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch(...)
{
    cerr << "Unknown exception!\n";
    return 2;
}
