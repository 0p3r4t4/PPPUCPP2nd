// 5.exercise.03.cpp
// 
// Absolute zero is the lowest temperature that can be reached; it's -273.15
// ºC, or 0K. The above program, even when corrected, will produce erroneous
// results when given a temperature below this. Place a check in the main
// program that will produce an error if a temperature is given below -273.15
// ºC.
//
// Commments:
//  Basically this silution is the same as 5.exercise.02.cpp since I already
//  considered the below absolute zero input as an error.

#include "std_lib_facilities.h"

class Below_abszero{};
class Bad_input{};

double ctok(double c)
{
    return c + 273.15;
}

int main()
try 
{
    double c = 0;
    cout << "Insert a temperature in Celsius to know the Kelvin equivalent: ";
    cin >> c;
    if (cin) {
        double k = ctok(c);
        if (k < 0)
            throw Below_abszero();
        else
            cout << k << "K\n";
    } else {
        throw Bad_input();
    }

    return 0;
}
catch (Below_abszero)
{
    cerr << "You tried to trick me with a temperature below absolute zero ...\n"
        << "Please, don't do that to me.\n";
}
catch (Bad_input)
{
    cerr << "Bad input, sorry!\n";
}
