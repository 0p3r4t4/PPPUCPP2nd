// 8.exercise.09.cpp
//
//  Write a function that given two vector<double>s price and weight computes a
//  value (an "index") that is the sum of all price[i]*weight[i]. Make sure to
//  have a weight.size()==price.size().

#include "std_lib_facilities.h"

double index(const vector<double>& u, const vector<double>& v)
// Calculates the sum of the product of each element from two vectors
// Sum with i from 0 to u.size()-1 of u[i]*v[i].
// Precondition:
//  u and v must have the same size.
{
    if (u.size() != v.size())
        error("index(): vectors have different sizes.");

    double sum{0};
    size_t limit{u.size()};
    for (size_t i = 0; i < limit; ++i)
        sum += u[i] * v[i];
    return sum;
}

int main()
try {
    vector<double> weight{1, 2, 3};
    
    // Test a simple case
    vector<double> price1{1, 2, 3};
    cout << index(weight, price1) << '\n';

    // Trigger an error
    vector<double> price2{1, 2};
    cout << index(weight, price2) << '\n';

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
