// 10.exercise.06.cpp
//
//  Define a Roman_int class for holding Roman numerals (as ints) with a << and
//  >>. Provide Roman_int with an as_int() member that returns the int value,
//  so that if r is a Roman_int, we can write cout << "Roman" << r << "equals"
//  << r.as_int() << '\n';.

#include "std_lib_facilities.h"
#include "10.exercise.06.roman.h"

int main()
try 
{
    Roman::Roman_int r{45};
    cout << r.value() << '\n';
    r = Roman::Roman_int{"MCMLXXVIII"};
    cout << r.value() << " in Roman is " << r.as_int() << '\n';
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
    /*
    while (cin) {
        string s;
        cin >> s;
        cout << Roman::Roman_int{s}.as_int() << '\n';
    }
    */
    while (cin >> r) {
        cout << r.as_int() << " -> " << r.value() << '\n';
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
