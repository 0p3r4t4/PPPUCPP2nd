// 8.exercise.04.cpp
//
//  An int can hold integers only up to a maximum number. Find an approximation
//  of that maximum number by using fibonacci().
//
//  COMMENTS
//  
//  As done in previous exercise I don't check for sign on x and y arguments of
//  fibonacci(). This lets me approximate also the minimum number that can be
//  expressed by an int.
//
//  I also checked for overflow (and underflow) and throw an error if it
//  happens. This is caught in main() and causes the end of the program. I have
//  to change that if I want to approximate based on failure. So, in
//  fibonacci() the check_add() call is packed into a try-catch statement that
//  informs about the error and lets the program continue. I suppose that the
//  vector elements generated to that point are still valid on return, but I
//  can be wrong.
//
//  The way to approximate is to begin various Fibonacci sequences with
//  different values each to test distinct growths and decreases of the series.
//  I take the last value of each sequence to track the maximum and minimum.
//  We already know the real limits by using numeric_limits<int>::max() and
//  ::min(), and we can compare the goodness of the approximation.
//
//  The results using begin{-100} and end{100} are:
//      Maximum integer aproximatted: 2140818248 (real limit 2147483647)
//      Minimum integer aproximatted: -2135115361 (real limit -2147483648)
//  The results using begin{-200} and end{200} are:
//      Maximum integer approximate: 2144267801 (real limit 2147483647)
//      Minimum integer approximate: -2140743223 (real limit -2147483648)
//  which I think are pretty good.
//
//  Of course this program prints an amount of error messages. In Linux, you
//  can get rid of them by executing the program as: ./a.out 2> /dev/null

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

int main()
try {
    vector<int> data;
    int max{0};         // Keep track of maximum int obtained
    int min{0};         // Keep track of minimem int obtained
    int begin{-200};    // Value from calculate Fibonacci sequences
    int end{200};       // Value to calculate Fibonacci sequences
    int seq_size{50};   // Elements of Fibonacci sequence. 50 is a good
                        // nomber to provoke overflows

    // Generate Fibonacci sequences
    for (int i = begin; i < end; ++i) {
        fibonacci(i, i+1, data, seq_size);
        int& val = data[data.size()-1];   // Use reference as an alias. §8.5.5
        if (val > max) max = val;
        if (val < min) min = val;
        data.clear();                     // Empty vector for next loop
    }

    cout << "Maximum integer approximate: " << max;
    cout << " (real limit " << numeric_limits<int>::max() << ")\n";
    cout << "Minimum integer approximate: " << min;
    cout << " (real limit " << numeric_limits<int>::min() << ")\n";

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
