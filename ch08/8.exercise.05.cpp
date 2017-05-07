// 8.exercise.05.cpp
//
//  Write two functions that reverse the order of element in a vector<int>.
//  For example, 1, 3, 5, 6, 9 becomes 9, 7, 5, 3, 1. The first reverse
//  function should produce a new vector with the reverse sequence, leaving the
//  original vector unchanged. The other reverse function should reverse the
//  elements of its vector without using any other vectors (hint: swap).
//
// COMMENTS
//
//  The fibonacci() and print() functions comes in handy to test the proposed
//  functions on this exercise.
//
//  The first function will be named reverse_cr() as parameter will be passed
//  by const-reference. The other one will be reverse_r() as parameter will be
//  passed by reference.
//
//  We must check for odd and even elements sequences.
//

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

    // Add a try-catch block to catch overflow and let the program continue
    try {
        for (int i = 2; i < n; ++i)
            v.push_back(check_add(v[i-2],v[i-1]));
    }
    catch(exception& e){
       cerr << e.what() << '\n';
    }
}

void swap(int& a, int& b)
// Swaps values of two int variables
{
    int temp{a};
    a = b;
    b = temp;
}

vector<int> reverse_cr(const vector<int>& v)
// Returns a new vector with vector v elements in reverse order
{
}

void reverse_r(vector<int>& v)
// Reverses order of elements of vector v
{
}

int main()
try {
    vector<int> data;
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
