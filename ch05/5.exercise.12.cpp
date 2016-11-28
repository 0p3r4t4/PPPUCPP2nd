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

#include "std_lib_facilities.h"

vector<int> _guess()
// read a number from 
{
}

int main()
try
{
    bool guessed = false;
    // Number to guess: 3461
    vector<int> digits = {3, 4, 6 , 1};
    int guess = 0;

    cout << "Welcome to Bulls and Cows.\n"
         << "Try to guess the four digit sequence I'm thinking about.\n"
         << "No digit appears more than once and I will give you clues,\n"
         << "with \"bulls\" being correct digits in the right position\n"
         << "and \"cows\" being correct digits in wrong position.\n"
         << "Let's start! Your guess ...\n? ";

    while (!guessed) {
        while (cin >> guess) {
            // smallest and biggest combination of 4 distinct digits on [0, 9]
            if (guess >= 123 && guess <= 9876) {
            }
            else { 
                cout "Not a four digit number! Please try again.\n? ";
            }
        }
        if (cin.eof()) {
            cout << "Bye, bye!\n";
            return 0;
        } else {
            cout "Not a four digit number! Please try again.\n? ";
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
