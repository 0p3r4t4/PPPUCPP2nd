// 10.exercise.01.cpp
//
//  Write a program that produces the sum of all the numbers in a file of
//  whitespace-separated integers.
//
// COMMENTS
//
//  I could have done file reading and sum in the same step, without storaging
//  numbers in a vector, but I decide to separate it. For a simple task as this
//  it seems silly but for more complex ones it seems mandatory.
//  I will also not continue reading if there's a fail. I will consider the
//  file as not well formatted.
//  I will recover check_add() from 8.exercise.05.cpp to avoid integer
//  overflow.

#include "std_lib_facilities.h"

const string if_name{"10.exercise.01.input"};

void read_numbers(vector<int>& v, const string& file)
{
    ifstream ist{file};
    if (!ist) error("Can't open input file ", file);
    ist.exceptions(ist.exceptions()|ios_base::badbit);  // Force on badbit

    for (int n; ist >> n;)
        v.push_back(n);
    
    if (ist.eof()) {    // Some info about the reading
        ist.clear();    // To avoid failbit then
        cout << "File " << file << " completely read. " << v.size()
             << " numbers.\n";
    }
    if (ist.fail()) error("Not well formatted file ", file);
}

int check_add(int lhs, int rhs)
// Adds two integers performing overflow control to avoid undefined behavior.
// (Search for INT32-C on https://www.securecoding.cert.org)
{
    if (((rhs > 0) && (lhs > (numeric_limits<int>::max() - rhs))) ||
        ((rhs < 0) && (lhs < (numeric_limits<int>::min() - rhs))))
        error("check_add(): integer add overflows.");
    else
        return lhs+rhs;
}

int sum(const vector<int>& v)
{
    int sum{0};
    for (int n : v)
        sum = check_add(sum, n);
    return sum;
}

int main()
try {
    vector<int> numbers;

    read_numbers(numbers, if_name);
    cout << "The sum of all the numbers in " << if_name << " is " 
         <<sum(numbers) << '\n';

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
