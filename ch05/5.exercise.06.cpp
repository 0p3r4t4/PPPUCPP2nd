// 5.exercise.06.cpp
//
// Write a program so that converts from Celsius to Fahrenheit and from
// Fahrenheit to Celsius (formula in 4.3.3). Use estimation (5.8) to see if
// your results are plausible
//
// Comments:
//  Formula from 4.3.3 coul be expressed as f=9.0/5*dc+32.
//  The inverse formula is easy infered as c=(f-32)*5.0/9.
//
//  I've tried to mimic the documentation style of functions from the end of
//  the chapter; indicating what is supposed to do, and pre and
//  post-conditions. I don't know if any post-condition could be enforced by
//  code, but the pre-condition of greater than absolute zero makes sense to
//  me.
//
//  I know error() function defined in std_lib_facilites.h is the way to go,
//  but I resist to it and prefer some practice with bare exceptions and throw
//  them on my own.
//
//  As for estimation, I think conversion from Celsius to Fahrenheit could be
//  rapidly aproximated by f~=2*dc+30, as 9/5 is 1.8 it feels fine.
//  Conversion from Fahrenheit to Celsius similarly as dc=(f-30)/2, as 5/9 is
//  0.555...

#include "std_lib_facilities.h"

// Constant messages for exceptions thrown
const string ex_abszero_msg = "Indicated temperature below absolute zero!";
const string ex_badunit_msg = "Indicated unit not known (valid values are C, c, F or f)";
const string ex_badinput_msg = "Incorrect input syntax";

double ctof(double c)
// Converts Celsius to Fahrenheit
// pre-condition: Celsius temperature equal oe greater than 273.15 (absolute
//                zero)
{
    if (c < -273.15) throw runtime_error(ex_abszero_msg);
    return c*9.0/5+32;      // Conversion formula
}

double ftoc(double f)
// Converts Fahrenheit to Celsius
// pre-condition: Fahrenheit temperature equal or greater than -459.67
//                (absolute zero)
{
    if (f < -459.67) throw runtime_error(ex_abszero_msg);
    return (f-32.0)*5/9;
}

int main()
try
{
    double degrees = 0;
    char unit = ' ';
    
    cout << "Insert a temperature in Celsius or Fahrenheit to convert.\n"
         << "(Magnitude and unit separated by a space, unit in (C,c,F,f); e.g. 30 C or 90 F)\n"
         << ": ";

    while (cin >> degrees >> unit) {
        switch (unit) {
            case 'c':
            case 'C':
                cout << degrees << " ºC is equivalent to " << ctof(degrees) << " ºF\n";
                break;;
            case 'f':
            case 'F':
                cout << degrees << " ºF is equivalent to " << ftoc(degrees) << " ºC\n";
                break;;
            default:
                throw runtime_error(ex_badunit_msg);
                break;;
        }
        cout << ": ";
    }
    
    // Why have we exit the while loop?
    if (cin.eof()) {
        cout << "\nBye, bye!\n";
    } else {
        throw runtime_error(ex_badinput_msg);
    };

    return 0;
}
catch (exception& e)
{
    cout << "Error: " << e.what() << '\n';
    return 2;
}
catch (...)
{
    cout << "Unknown error.\n";
    return 1;
}
