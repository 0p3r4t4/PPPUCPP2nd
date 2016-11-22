// 5.exercise.09.cpp
//
// Modify the program from exercise 8 to write an error if the result cannot be
// represented as an int
//
// Comments:
//  In Linux I test this program with:
//
//   ( (( N = RANDOM/32 )); echo $N; for i in $(seq $RANDOM); do echo (( RANDOM
//   - 16536 )); done; echo '|' ) | ./a.out
//
//  It can randomly cause throw if:
//      - values to sum is less than 0
//      - asks to sum more values than supplied
//      - sum overflows int type
//
//  You can play with (( RANDOM - 16536 )) and use (( RANDOM*12000 ))
//  to test upper int overflow or (( (RANDOM - 32767) * 12000 )) to test lower
//  overflow.

#include "std_lib_facilities.h"

const string ex_bad_number_msg = "The number of values to sum must be 1 or greater!";
const string ex_bounds_msg = "You asked to sum more elements than those supplied!";
const string ex_bad_input_msg = "You entered something that's not an integer!";
const string ex_sum_overflow_msg = "The sum cannot be represented with an int type!";

int sum_of_N(int N, const vector<int>& elements)
// Return the sum of the N first elements of vector elements
// pre-condition:   the vector has to have at least N elements
{
    if (N > int(elements.size())) throw runtime_error(ex_bounds_msg);

    int sum = 0;

    for (int i = 0; i < N; ++i) {
        // If we add a positive number to the sum and it becomes less than before, or
        // if we add a negative and sum gets greater, an overflow has happened
        if (elements[i] >= 0 && sum + elements[i] < sum) throw runtime_error(ex_sum_overflow_msg);
        if (elements[i] < 0 && sum + elements[i] > sum) throw runtime_error(ex_sum_overflow_msg);
        sum += elements[i];
    }

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
    if (N < 1) throw runtime_error(ex_bad_number_msg);

    cout << "Please enter some integers (press '|' to stop); ";
    int element;
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
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Unexpected error!\n";
    return 2;
}
