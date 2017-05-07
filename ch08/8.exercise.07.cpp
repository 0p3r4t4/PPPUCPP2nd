// 8.exercise.07.cpp
//
//  Read five names into a vector<string> name, then prompt the user for the
//  ages of the people named and store the ages in a vector<double> age. Then
//  print out the five (name[i],age[i]) pairs. Sort the names
//  (sort(name.begin(),name.end()) and print out the (name[i],age[i]) pairs.
//  The tricky part here is to get the age vector in the correct order to match
//  the sorted name vector. Hint: Before sorting name, take a copy and use that
//  to make a copy of age in the right order after sorting name.

#include "std_lib_facilities.h"

int main()
try {
    return 0;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch(...)
{
    cerr << "Unknown exception!\n";
    return 2;
}
