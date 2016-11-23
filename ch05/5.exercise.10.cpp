// 5.exercise.10.cpp
//
// Modify the program from exercise 8 to use double instead of int. Also, make
// a vector of doubles containing the N-1 differences between adjacent values
// and write out that vector of differences.

#include "std_lib_facilities.h"

const string ex_bad_number_msg = "The number of values to sum must be 1 or greater!";
const string ex_bounds_msg = "You asked to sum more elements than those supplied!";
const string ex_bad_input_msg = "You entered something that's not an integer!";

double sum_of_N(int N, const vector<double>& elements)
// Return the sum of the N first elements of vector elements
// pre-condition:   the vector has to have at least N elements
{
    if (N > int(elements.size())) throw runtime_error(ex_bounds_msg);

    double sum = 0;

    for (int i = 0; i < N; ++i)
        sum += elements[i];

    return sum;
}

vector<double> diffs_of_N(int N, const vector<double>& elements)
// Return a vector containing the N-1 differences between the first
// N adjacent values in elements.
// pre-condition:   the elements vector has to have at least N elements
{
    if (N > int(elements.size())) throw runtime_error(ex_bounds_msg);

    vector<double> diffs;
    diffs.reserve(N-1);

    for (int i = 0; i < N-1; ++i)
        diffs.push_back(elements[i+1] - elements[i]);

    return diffs;
}

int main()
try
{
    cout << "Please enter the number of values you want to sum: ";
    int N = 0;
    cin >> N;
    if (!cin) throw runtime_error(ex_bad_input_msg);
    if (N < 1) throw runtime_error(ex_bad_number_msg);

    cout << "Please enter some real numbers (press '|' to stop); ";
    vector<double> elements;
    double element;
    while (cin >> element)
        elements.push_back(element);

    if (cin.eof()) {
        cout << "Bye, bye!\n";
    }
    else {
        cin.clear();
        char end = ' ';
        cin >> end;
        if (end != '|') {
            throw runtime_error(ex_bad_input_msg);
        }
        else {
            double sum = sum_of_N(N, elements);
            cout << "The sum of the first " << N << " numbers ( ";
            // If sum_of_N hasn't throw, we ca do this:
            for (int i = 0; i < N; ++i)
                cout << elements[i] << ' ';
            cout << ") is " << sum << ".\n";
            vector<double> diffs = diffs_of_N(N, elements);
            cout << "The differences between the first " << N << " numbers are:\n";
            for (int i = 0; i < N-1; ++i)
                cout << diffs[i] << ' ';
            cout << '\n';
        }
    }
}
catch (exception& e)
{
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Unexpected error!\n";
    return 2;
}
