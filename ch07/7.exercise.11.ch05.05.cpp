// 7.exercise.11.ch05.05.cpp
//
//  Revisit two programs you wrote for the exercises in Chapter 4 or 5. Clean
//  up that code according to the rules outlined in this chapter. See if you
//  find any bugs in the process.
//
// ORIGINAL STATEMENT
//
//  5.exercise.05.cpp
// 
//   Add to the program so that it can also convert from Kelvin to Celsius.
//
// COMMENTS
//
//  In summary the chapter tell us to:
//
//      - Review pregram presentation to the user.
//      - Do testing trying to break the program and solve bugs found.
//      - Clean up the code:
//          - get rid of symbolic constants
//          - divide the code into functions that do just one single logical
//          action
//          - review code layout to improve code reading
//      - Evaluate if we can recover from errors
//      - Evaluate and implement improvements to the program

#include "std_lib_facilities.h"

class Below_abszero{};
class Bad_input{};

double ctok(double c)
{
    if (c < -273.15) throw Below_abszero();
    return c + 273.15;
}

double ktoc(double k)
{
    if (k < 0) throw Below_abszero();
    return k - 273.15;
}

int main()
try 
{
    double deg = 0;
    char unit = ' ';

    cout << "Insert a temperature in Celsius or Kelvin to convert.\n"
         << "(Magnitude and unit separated by an space; e.g. 30 C or 300 K)\n"
         << ": ";
    
    cin >> deg >> unit; 
    if (cin) {
        switch (unit) {
            case 'C':
                cout << ctok(deg) << "K\n";
                break;
            case 'K':
                cout << ktoc(deg) << " ºC\n";
                break;
            default:
                throw runtime_error("Given temperature unit isn't a known one.");
        }
    } else {
        throw Bad_input();
    }

    return 0;
}
// Exception style a bit mixed, I know. Just testing with those provided
// by C++ and the personalized ones in the same program.
catch (Bad_input)
{
    cerr << "Bad input, sorry!\n";
    return 1;
}
catch (runtime_error& e)
{
    cerr << e.what() << '\n';
    return 2;
}
catch (Below_abszero)
{
    cerr << "You tried to trick me with a temperature below absolute zero ...\n"
        << "Please, don't do that to me.\n";
    return 3;
}
