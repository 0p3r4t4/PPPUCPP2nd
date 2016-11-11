// 5.exercise.02.cpp
// 
// The following program takes in a temperature value in Celsius and converts
// it to Kelvin. This code has many errors in it. Find the errors, list them,
// and correct the code.
//

// double ctok(double c)       // converts Celsius to Kelvin
// {
//     int k = c + 273.15;
//     return int
// }
// 
// int main()
// {
//     double c = 0;           // declare input variable
//     cin >> d;               // retrieve temperature to input variable
//     double k = ctok("c");   // convert temperature
//     Cout << k << '\n';      // print temperature
// }

// Where do we begin??
// 1. We need to include std_lib_facilities.h, of course.

#include "std_lib_facilities.h"

// 2. In ctok() a floating point arithmetic expression is assigned to an int 
//    variable performing a narrowing conversion
// 3. In ctok() return a type is tried, instead the variable. Also, no ; at the
//    end of the statement.

double ctok(double c)
{
    return c + 273.15;
}

// 4. In main() is tried to read from the input to a variable not declares (d)
// 5. In main(), "c", a sting, not a double variable, is used as an argument
//    in the call to ctok()
// 6. Cout is not right written
// 7. There is no clue to the user of what this program does
// 8. There is no checking of input
// 9. There is no checking of physical laws (absolute zero, at least; Plank
//    temperature is so high ...)

class Below_abszero{};
class Bad_input{};

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
            cout << k << " K\n";
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
