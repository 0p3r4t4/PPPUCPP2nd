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
// STATEMENT
//
//  This program converts a temperature from Kelvin to Celsius and vice versa.
//
// COMMENTS
//
//  In summary the chapter tell us to:
//
//      1. Review program presentation to the user.
//      2. Do testing trying to break the program and solve bugs found.
//      3. Clean up the code:
//          a) get rid of magic constants and introduce symbolic names
//          b) divide the code into functions that do just one single logical
//          action
//          c) review code layout to improve code reading
//      4. Evaluate if we can recover from errors
//      5. Evaluate and implement improvements to the program
//
// 1.
//  We will do a loop in main to let the user do more than one conversion
//  inside an execution of the program.
//  There is no need to separate magnitude from unit, so the user's instruction
//  for it is deleted from start message.
// 2. 
//  Some commands I've used for testing the program aside from manual testing:
//
//   for i in {1..25}; do mktemp -u XXXXXXXXXXXXXXXX; done | ./a.out
//  
//  confronts the program with random strings. It will cause mainly exceptions
//  but sometimes it produces a good result or catch a quit command.
//
//    for i in {+,-,a}{0..9}{0..9}{1,b}{K,C,J}; do echo -e $i; done | ./a.out
//
//  confronts the program with well-and-malformed inputs and temperatures
//  below absolute zero.
// 3.a
//  I use a ton of magic constants (given the size of the code), like 'C', 'K'
//  or -273.15 ...
// 3.b
//  The main body will perform a loop of conversions. So convert() will be
//  created to split this loop from the conversion action.
//  Also, it could be that convert() will be a candidate for furthet splitting.
//  I will stop here.
// 3.c
//  I include the statement of the exercise, but since it's an improvement
//  from a previous one, information about the aim is missing. So we
//  include STATEMENT.
//  I use custom exceptions. Return to use error().
// 4.
//  To recover from errors, we can do the try-catch in convert().
// 5.
//  We could add a "quit" command to avoid the abrupt exit with Ctrl+C. For
//  this a new function, user_quits(), is implemented.
//  If we put more than one temperature in a single line prompt is printed
//  after each result. I don't know how to avoid this. Yet.
//  

#include "std_lib_facilities.h"

const char celsius {'C'};
const char kelvin {'K'};
const double absolute_zero {-273.15};
const string prompt {": "};
const char quit {'q'};

double ctok(double c)
// Converts Celsius to Kelvin
{
    if (c < absolute_zero) error("ctok(): Temperature is below absolute zero!");
    // The absolute zero constant is negative, by substracting it we
    // effectively add its absolute value
    return c - absolute_zero;
}

double ktoc(double k)
// Converts Kelvin to Celsius
{
    if (k < 0) error("ktoc(): Temperature is below absolute zero!");
    // The absolute zero constant is negative, by adding it we
    // effectively substract its absolute value
    return k + absolute_zero;
}

bool user_quits()
// Looks ahead the standard input to detect if a quit command has been issued
// by the user. If it's not the case, restore the input state.
{
    char tmp;
    // Search for quit command
    cin >> tmp;
    if (tmp != quit) {
        cin.putback(tmp);
        return false;
    }
    return true;
}

void convert()
try
{
    cout << prompt;

    // Test if the user issues a quit command
    if (user_quits()) {
        // We've received 'quit' command, so we set the EOF flag to
        // cause the exit of the program. Weird.
        cin.setstate(cin.eofbit);
        return; 
    }
        
    double degrees;
    char unit;

    if (cin >> degrees >> unit) {
        switch (unit) {
            case celsius:
                cout << degrees << " ºC is equivalent to " << ctok(degrees) << "K\n";
                break;
            case kelvin:
                cout << degrees << " K is equivalent to " << ktoc(degrees) << " ºC\n";
                break;
            default:
                error("convert(): Given temperature unit isn't a known one.");
        }
    } else {
        // Input is bad formatted, we ignore the rest of the line before
        // throwing the error
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        error("convert(): Bad input format. Ignoring rest of the line ...");
    }
}
catch (exception& e)
{
    cout << "Exception in " << e.what() << '\n';
}

int main()
try 
{
    cout << "Insert a temperature in Celsius or Kelvin to convert.\n"
         << "  Format: <Magnitude><Unit>\n"
         << "          <Unit> being C (for Celsius) or K (for Kelvin).\n"
         << "(Use q to exit the program)\n";
    
    while (!cin.eof()) convert();
    if (cin.eof()) cout << "Bye, bye!\n";

    return 0;
}
catch (...)
{
    cout << "Unknown exception!\n";
    return 1;
}
