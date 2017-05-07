// 8.exercise.06.cpp
//
// Write versions of the functions from exercise 5, bu with a vector<string>.
//
// COMMENTS
//
//  Remember statement from exercise 5:
//   Write two functions that reverse the order of element in a vector<int>.
//   For example, 1, 3, 5, 6, 9 becomes 9, 7, 5, 3, 1. The first reverse
//   function should produce a new vector with the reverse sequence, leaving
//   the original vector unchanged. The other reverse function should reverse
//   the elements of its vector without using any other vectors (hint: swap).
//
//  We can discard the fibonacci() function, but a print() for strings could be
//  useful for testing.

#include "std_lib_facilities.h"

void print(const string& label, const vector<string>& data)
// Only read arguments, so it safe to pass them by const-reference
{
    cout << label << ": { ";
    for (string i : data)
        cout << i << ' ';
    cout << "}\n";
}

vector<string> reverse_cr(const vector<string>& v)
// Returns a new vector with vector v elements in reverse order
{
    vector<string> r;

    for (size_t i = v.size(); i > 0; --i)
        r.push_back(v[i-1]);

    return r;
}

void reverse_r(vector<string>& v)
// Reverses order of elements of vector v
{
    size_t limit{v.size()/2}; // Only traverse half of the elements.
                              // This way, if we have an odd number of elements
                              // the division ignores the middle one.
    size_t last_idx{v.size()-1};    // Last element index. To avoid recalc.

    for (size_t i = 0; i < limit; ++i)
        swap(v[i], v[last_idx-i]);
}

int main()
try {
    // Test a vector with even element number
    vector<string> e1{"one", "two", "three", "four"};
    print("Original even            ", e1);
    vector<string> e2{reverse_cr(e1)}; // New vector reversed
    print("Reverse even by const-ref", e2);
    reverse_r(e1);                  // Reverse original vector
    print("Reverse even by ref      ", e1);

    // Test a vector with odd element number
    vector<string> o1{"one", "two", "three", "four", "five"};
    print("Original odd             ", o1);
    vector<string> o2{reverse_cr(o1)}; // New vector reversed
    print("Reverse odd by const-ref ", o2);
    reverse_r(o1);                  // Reverse original vector
    print("Reverse odd by ref       ", o1);
    
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
