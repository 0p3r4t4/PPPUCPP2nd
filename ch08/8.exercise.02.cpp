// 8.exercise.02.cpp
//
// Write a function print() that prints a vector of ints to cout. Give it two
// arguments: a string for "labeling" the output and a vector.

#include "std_lib_facilities.h"

void print(const string& label, const vector<int>& data)
{
    cout << label << ": { ";
    for (int i : data)
        cout << i << ' ';
    cout << "}\n";
}

int main()
// Test the print function
{
    vector<int> sample;
    string label{"Sample data"};

    // Simple initialization of sample vector
    for (int i = 0; i < 100; ++i) {
        sample.push_back(i);
    }

    // Some calls with current data and also literals
    print(label, sample);
    print("A pair", vector<int> {10, 99});
    print("Empty", vector<int> {});

    return 0;
}
