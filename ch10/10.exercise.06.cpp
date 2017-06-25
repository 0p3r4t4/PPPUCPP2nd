// 10.exercise.06.cpp
//
//  Define a Roman_int class for holding Roman numerals (as ints) with a << and
//  >>. Provide Roman_int with an as_int() member that returns the int value,
//  so that if r is a Roman_int, we can write cout << "Roman" << r << "equals"
//  << r.as_int() << '\n';.
//
// COMMENTS
//  See details on 10.exercise.06.md

#include "std_lib_facilities.h"
#include "10.exercise.06.roman.h"

int main()
try 
{
    Roman::Roman_int r{45};
    cout << r.value() << '\n';
    r = Roman::Roman_int{"MCMLXXVIII"};
    cout << r << " in Roman is " << r.as_int() << '\n';

    // Provoke errors on constructor
    try {
        r = Roman::Roman_int{"IXIX"};
        cout << r.as_int() << '\n';
    }
    catch (Roman::Not_roman& e) {
        cout << "NOT ROMAN!!\n";
    }
    try {
        r = Roman::Roman_int{"abdba"};
        cout << r.as_int() << '\n';
    }
    catch (Roman::Not_roman& e) {
        cout << "NOT ROMAN!!\n";
    }

    // Test loop, get a Roman numeral, convert to int and convert again to
    // Roman numeral ...
    while (cin >> r) {
        cout << r.as_int() << " -> " << r << '\n';
    }

    return 0;
}
catch (Roman::Not_roman& e)
{
    cerr << "Tried to read something else or create a Roman_int out of bounds [" 
         << Roman::min << ", " << Roman::max << "]\n";
    return 1;
}
catch (exception& e)
{
    cerr << e.what() << '\n';
    return 2;
}
catch (...)
{
    cerr << "Unknown exception!!\n";
    return 3;
}
