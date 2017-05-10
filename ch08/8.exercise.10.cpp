// 8.exercise.10.cpp
//
//  Write a function maxv() that returns the largest element of a vector.

#include "std_lib_facilities.h"

void print(const string& label, const vector<double>& data)
// Only read arguments, so it safe to pass them by const-reference
{
    cout << label << ": { ";
    for (double d : data)
        cout << d << ' ';
    cout << "}\n";
}

double maxv(const vector<double>& v)
{
    double max{v[0]};   // We could not make assumptions about vector values
                        // and so we must initalize the max track to an element
    for (double d : v)
        if (d > max) max = d;

    return max;
}

int main()
try {
    vector<double> test_data{-5, 0, 6.7, -1000, 10.1e5, 10e5};

    print("Test data", test_data);
    cout << "Largest element from data: " << maxv(test_data) << '\n';
    
    return 0;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch(...)
{
    cerr << "Unknown exception!!\n";
    return 2;
}
