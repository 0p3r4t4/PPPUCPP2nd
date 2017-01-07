// 6.exercise.08.cpp
//
// Redo the "Bulls and Cows" game from exercise 12 in Chapter 5 to use four
// letters rather than four digits.
//
// Previous statement:
//
//  Implement a little guessing game called (for some obscure reason) "Bulls and
//  Cows". The program has a vector of four different integers in the range 0 to
//  9 (e.g., 1234 but not 1122) and it is the user's task to discover those
//  numbers by repeated guesses. Say the number to be guessed is 1234 andd the
//  user guesses 1359; the response should be "1 bull and 1 cow" because the
//  user got one digit (1) right and in the right position (a bull) and one
//  digit (3) right but in the wrong position (a cow). The guessing continues
//  until the user gets four bulls, that is, has the four digits correct and in
//  the correct order.
//
// Comments:
//  
//  Mainly changes to accomodate to the new requisites, this is, a sequence of
//  four distinct letters rather than a sequence of four distinct numbers.
//
//  Perhaps it would be more interesting to make changes to exercise 13 in
//  Chapter 5 since it's a more advanced version of the program. But that's not
//  what the exercise is telling us.
//
//  Also, the changes are minimal. We can think about replace vectors with
//  strings for guesses and sequence to be guessed. At first I choose to 
//  stick with vectors and it surely works fine, but there are things that
//  become redundant, as parse_input() function (see ch05/5.exercise.12.cpp), 
//  so I made more changes to work with strings instead of vectors (since
//  we have index operator, it feels the same, I guess). In fact, no a great
//  amount of changes, since changing types of guess and to be guessed values,
//  changing the functions arguments types and deleting parse_input() and its
//  calls, suffices. The std::string type has size() member function and []
//  operator just as std::vector, so no changes to code operating on them
//  are needed.

#include "std_lib_facilities.h"

static const string ex_msg_no_four_letter = "Your input is not a four letters sequence.";
static const string ex_msg_repeated_letter = "You've entered repeated letters. "
                                             "This way you're never going to guess it!";
static const string ex_msg_distinct_size = "Something nasty has happened; guess and/or "
                                           "sequence to be guessed do not have a length "
                                           "of 4.";

bool check_input(const string& input)
// Checks input to be a 4-unique-lowcase-letters string.
// Pre-conditions:
//  The length of the string must be exactly 4
//  Each character of the string must be an ASCII (or compatible, as ISO or UTF8)
//      value for chars from 'a' to 'z' (they are consecutive).
//  Each character of the string must be different
try
{
    if (input.length() != 4) throw runtime_error(ex_msg_no_four_letter);

    for (char c : input)
        if (c < 'a' || c > 'z')
            throw runtime_error(ex_msg_no_four_letter);

    for (size_t i = 0; i < input.length() - 1; ++i)
        for (size_t j = i + 1; j < input.length(); ++j)
            if (i != j && input[i] == input[j])
                throw runtime_error(ex_msg_repeated_letter);

    return true;
}
catch (exception& e)
{
    cout << e.what() << '\n';
    return false;
}

int get_bulls(const string& letters, const string& guess)
// Get number of positions in two strings wich have the same value
// Pre-condition:
//  Both strings have the same number of elements
// Post-condition:
//  bulls must be 4 or less
{
    int bulls = 0;

    if (letters.size() != guess.size())
        throw runtime_error(ex_msg_distinct_size);

    for (size_t i = 0; i < letters.size(); ++i)
        if (letters[i] == guess[i]) ++bulls;

    if (bulls > 4)
        throw runtime_error(ex_msg_distinct_size);

    return bulls;
}

int get_cows(const string& letters, const string& guess)
// Get how many letters from guess are present on letters but not in
// the same position.
// Post-condition:
//  cows must be 4 or less (given that elements on guess and letters are unique)
{
    int cows = 0;

    for (size_t i = 0; i < guess.size(); ++i)
        for (size_t j = 0; j < letters.size(); ++j)
            if (i != j && guess[i] == letters[j]) ++cows;

    if (cows > 4)
        throw runtime_error(ex_msg_distinct_size);

    return cows;
}

void print_bulls_and_cows(int bulls, int cows)
// Print number of bulls and cows taking account of singular
// or plural forms.
{
    cout << "You've got ";

    if (bulls == 1) cout << bulls << " bull";
    else cout << bulls << " bulls";

    cout << " and ";

    if (cows == 1) cout << cows << " cow";
    else cout << cows << " cows";
}

int main()
try
{
    // Sequence to guess: gael
    string letters = "gael";
    string guess = "";
    int bulls = 0;
    int cows = 0;

    cout << "Welcome to Bulls and Cows (letters version).\n"
         << "Try to guess the four letters sequence I'm thinking about.\n"
         << "No letter appears more than once and I will give you clues,\n"
         << "with \"bulls\" being correct letters in the right position\n"
         << "and \"cows\" being correct letters in wrong position.\n"
         << "Let's start! Your guess ...\n? ";

    while (bulls != 4) {
        if (cin >> guess) {
            if (check_input(guess)) {
                bulls = get_bulls(letters, guess);
                cows = get_cows(letters, guess);
                if (bulls == 4) {
                    cout << "Congratulations! You guessed right!\n";
                }
                else {
                    print_bulls_and_cows(bulls, cows);
                    cout << "\nGuess again!\n? ";
                }
            }
            else {
                cout << "? ";
            }
        }
        if (cin.eof()) {
            cout << "Bye!\n";
            return 0;
        } 
    }
}
catch (exception& e)
{
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Unknown exception!\n";
    return 2;
}
