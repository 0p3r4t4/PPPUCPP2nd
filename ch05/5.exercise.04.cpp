// 5.exercise.04.cpp
// 
// Do exercise 3 again, but this time handle the error inside ctok().

#include "std_lib_facilities.h"

class Below_abszero{};
class Bad_input{};

double ctok(double c)
{
    if (c < -273.15) throw Below_abszero();
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
