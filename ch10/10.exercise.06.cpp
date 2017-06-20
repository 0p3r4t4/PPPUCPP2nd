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
    return 0;
}
catch (exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Unknown exception!!\n";
    return 2;
}
