// 3.exercise.03.cpp
//
// Write a program that doesn't do anything, but declares a number of variables
// with legal and ilegal names (such as int double = 0;), so that you can see
// how the compiler reacts.

#include "std_lib_facilities.h"

int main()
{
    int double;
    double delete;
    char _wtf;
    bool 3isfalse;
    // Contrary to statements on section 3.7 (Names) the use of '$' in a name
    // seems to work, at least on MSVC and GNUCC (an extension?). It's true
    // that according to the ISO Standard it's not a valid character.
    string I_want$s {"Hola"};
    cout << I_want$s << '\n';
    int uno y dos;
}
