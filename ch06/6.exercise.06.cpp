// 6.exercise.06.cpp
//
// Write a program that checks if a sentence is correct according to the
// "English" grammar in 6.4.1. Assume that every sentence is terminated by a
// full stop (.) surrounded by whitespace. For example, "birds fly the fish
// swim . " is a sentence, but "birds fly but the fish swim" (terminating dot
// missing) and "birds fly but the fish swim." (no space before the dot) are
// not. For each sentence entered, the program should simply respond "OK" or
// "not OK". Hint: Don't bother with tokens; just read into a string using >>.
//
// Comments:
//  From the examples in the statement, I guess we must use the extended
//  grammar developed on exercise 5.

#include "std_lib_facilities.h"

int main()
try
{
    return 0;
}
catch (exception& e)
{
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Oops! Unknown exception\n";
    return 2;
}
