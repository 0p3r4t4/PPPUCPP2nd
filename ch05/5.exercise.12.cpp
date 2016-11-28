// 5.exercise.12.cpp
//
// Implement a little guessing game called (for some obscure reason) "Bulls and
// Cows". The program has a vector of four different integers in the range 0 to
// 9 (e.g., 1234 but not 1122) and it is the user's task to discover those
// numbers by repeated guesses. Say the number to be guessed is 1234 andd the
// user guesses 1359; the response should be "1 bull and 1 cow" because the
// user got one digit (1) right and in the right position (a bull) and one
// digit (3) right but in the wrong position (a cow). The guessing continues
// until the user gets four bulls, that is, has the four digits correct and in
// the correct order.
//
// Comments:
//  String input is our best bet. The user input sould start by 0 (no one tell
//  us this isn't possible) and by reading an int we loose that leading 0 and 
//  thus, we cannot determine if the user input has been 0123 (correct) or
//  123 (wrong). Reading char by char, on the other hand, makes it more compicated.

#include "std_lib_facilities.h"

static const string ex_msg_no_four_digit = "Your input is not a four digit number.";
static const string ex_msg_repeated_digits = "You've enetered repeated digits. "
                                             "This way you're never going to guess it.";

bool check_input(const string& input)
// Checks input to be a 4-unique-digit string.
// Pre-conditions:
//  The length of the string must be exactly 4
//  Each character of the string must be an ASCII (or compatible, as ISO or UTF8)
//      value for chars from '0' to '9' (they are consecutive).
//  Each character of the string must be different
try
{
    if (input.length() != 4) throw runtime_error(ex_msg_no_four_digit);

    for (size_t i = 0; i < input.length(); ++i)
        if (input[i] < '0' || input [i] > '9')
            throw runtime_error(ex_msg_no_four_digit);

    for (size_t i = 0; i < input.length(); ++i)
        for (size_t j = i + 1; j < input.length(); ++j)
            if (i != j && input[i] == input[j])
                throw runtime_error(ex_msg_repeated_digits);

    return true;
}
catch (exception& e)
{
    cout << e.what() << '\n';
    return false;
}

int main()
try
{
    bool guessed = false;
    // Number to guess: 3461
    vector<int> digits = {3, 4, 6 , 1};
    string input = "";
    vector<int> guess;

    cout << "Welcome to Bulls and Cows.\n"
         << "Try to guess the four digit sequence I'm thinking about.\n"
         << "No digit appears more than once and I will give you clues,\n"
         << "with \"bulls\" being correct digits in the right position\n"
         << "and \"cows\" being correct digits in wrong position.\n"
         << "Let's start! Your guess ...\n? ";

    while (!guessed) {
        while (cin >> input) {
            if (check_input(input)) {
                //guess = parse_input(input);
                cout << "Correct input!\n";
            }
            else {
                cout << "INCORRECT input!\n";
            }

        }
        if (cin.eof()) {
            cout << "Bye, bye!\n";
            return 0;
        } 
    }
}
catch (exception& e)
{
    cout << "Error: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cout << "Unknown exception!\n";
    return 2;
}
