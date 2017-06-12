// 10.exercise.01.cpp
//
//  Write a program that produces the sum of all the numbers in a file of
//  whitespace-separated integers.
//
//  TODO:
//      establish exception on badbit
//      review read_elements() for better error handling
//      check overflow in sum()
//      present better results

#include "std_lib_facilities.h"

const string if_name{"10.exercise.01.input"};

void read_numbers(vector<int>& v, const string& file)
{
    ifstream ist{file};
    if (!ist) error("Can't open input file ", file);
    for (int n; ist >> n;)
        v.push_back(n);
}

int sum(const vector<int>& v)
{
    int sum{0};
    for (int n : v)
        sum += n;
    return sum;
}

int main()
try {
    vector<int> numbers;

    read_numbers(numbers, if_name);
    cout << sum(numbers) << '\n';

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
