// 8.exercise.03.cpp
//
//  Create a vector of Fibonacci numbers and print them using the function from
//  exercise 2. To create the vector, write a function, fibonacci(x,y,v,n),
//  where integers x and y are ints, v is an empty vector<int> and n is the
//  number of elements to put into v; v[0] will be x and v[1] will be y. A
//  Fibonacci number is one that is part of a sequence where each elements is
//  the sum of the two previous ones. For example, starting with 1 an 2, we get
//  1, 2, 3, 5, 8, 13, 21, ... Your finbonacci() function should make such a
//  sequence starting with its x and y arguments.
//
//  COMMENTS
//
//  As discovered previously on exercise 10 from chapter 6, interger overflow
//  lends to undefined behavior. I'll implement a checked add function to
//  control it. I won't take as a precondition that x and y parameters on
//  fibonacci() are positive since I want to let them free to be negative
//  numbers. So the former function must take it into account.

#include "std_lib_facilities.h"

void print(const string& label, const vector<int>& data)
// Only read arguments, so it safe to pass them by const-reference
{
    cout << label << ": { ";
    for (int i : data)
        cout << i << ' ';
    cout << "}\n";
}

int check_add(int a, int b)
// Adds two integers performing overflow control to avoid undefined behavior.
// (Search for INT32-C on https://www.securecoding.cert.org)
{
    if (((b > 0) && (a > (numeric_limits<int>::max() - b))) ||
        ((b < 0) && (a < (numeric_limits<int>::min() - b))))
            error("check_add(): integer add overflows.");
    else
        return a+b;
}

void fibonacci(int x, int y, vector<int>& v, int n)
// Generates a Fibonacci sequence of n values into v, starting with values x
// and y (integers passed by value, and we are modifying v, so it is passed by
// reference).
// Preconditions:
//  Vector must be empty
//  To simplify, n must be equal or greater than two.
{
    if (v.size() != 0)
        error("fibonacci(): Non empty vector passed as argument.");
    if (n < 2)
        error("fibonacci(): n must be al least 2.");

    v.push_back(x);
    v.push_back(y);

    for (int i = 2; i < n; ++i)
        v.push_back(check_add(v[i-2],v[i-1]));
}

int main()
// Test the fibonacci function
try {
    vector<int> data;

    fibonacci(1, 2, data, 10);
    print("Fib(10)", data);

    // Some tests
    data.clear();
    fibonacci(-2,-2, data, 10);
    print("Test with negatives", data);

    data.clear();
    fibonacci(1, 2, data, 20);
    print("Test", data);

    data.clear();
    fibonacci(-5, 4, data, 20);
    print("Test with two signs", data);

    data.clear();       
    fibonacci(1, 2, data, 50);      // Causes integer overflow
    print("Test Fib(50)", data);

    return 0;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch(...)
{
    cerr << "Unknwon exception!!\n";
    return 2;
}
