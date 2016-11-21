// 5.exercise.08.cpp
//
// Write a program that reads and stores a series of integers and then computes
// the sum of the first N integers. First ask for N, then read de values into
// a vector, then calculate the sum of the first N values. For example:
//
//  "Please enter the number of values you want to sum:"
//
//      3
//
//  "Please enter some integers (press '|' to stop):"
//
//      12 23 13 24 15 |
//
//  "The sum of the first 3 numbers ( 12 23 13 ) is 48."
//
// Handle all inputs. For example, make sure to give an error message if the
// user asks for a sum of more numbers than there are in the vector.

#include "std_lib_facilities.h"

const string ex_bounds_msg = "You asked to sum more elements than those supplied!";
const string ex_bad_input_msg = "You entered something that's not an integer!";

int sum_of_N(int N, const vector<int>& elements)
// Return the sum of the N first elements of vector elements
// pre-condition:   the vector has to have at least N elements
{
    if (N > int(elements.size())) throw runtime_error(ex_bounds_msg);

    int sum = 0;

    for (int i = 0; i < N; ++i)
        sum += elements[i];

    return sum;
}

int main()
try
{
    vector<int> elements;
    int N = 0;

    cout << "Please enter the number of values you want to sum: ";
    cin >> N;
    if (!cin) throw runtime_error(ex_bad_input_msg);

    cout << "Please enter some integers (press '|' to stop); ";
    for (int element; cin >> element;)
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
            int sum = sum_of_N(N, elements);
            cout << "The sum of the first " << N << " numbers ( ";
            // If sum_of_N hasn't throw, we ca do this:
            for (int i = 0; i < N; ++i)
                cout << elements[i] << ' ';
            cout << ") is " << sum << ".\n";
        }
    }
}
catch (exception& e)
{
    cout << "Error: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cout << "Unexpected error!\n";
    return 2;
}
