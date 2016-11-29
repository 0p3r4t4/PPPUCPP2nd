// 5.exercise.13.cpp
//
// The program is a bit tedious because the answer is hard-coded into the
// program. Make a version where the user can play repeatedly (without stopping
// and restarting the program) and each game has a new set of four digits. You
// can get four random digits by calling the random number generator
// randint(10) from std_lib_facilities.h four times. You will note that if you
// run that program repeatedly, it will pick the same sequence of four digits
// each time you start the program. To avoid that, ask the user to enter
// a number (any number) and call seed_rand(n), also from std_lib_facilities.h,
// where n is the number the user entered before calling randint(10). Such n is
// called a seed, and different seeds give different sequences of random
// numbers.
//
// Comments:
//  I don't really like to ask the user for a number to seed the random
//  generator. I suppose it is another point to check if the the user introduces
//  a number or not, but I prefer to make it transparent to the user. It seems
//  that a very common way to seed the random generator is to use the
//  time(nullptr) function to get the number of seconds since the Epoch.

#include "std_lib_facilities.h"

static const string ex_msg_no_four_digit = "Your input is not a four digit number.";
static const string ex_msg_repeated_digits = "You've entered repeated digits. "
                                             "This way you're never going to guess it!";
static const string ex_msg_distinct_size = "Something nasty has happened; guess and/or "
                                           "number to be guessed do not have a length "
                                           "of 4.";

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

    for (size_t i = 0; i < input.length() - 1; ++i)
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

vector<int> parse_input(const string& input)
// Converts a 4-unique-digit string to a vector of ints with 4 elements
// Pre-condition:
//  input has to have been checked by check_input()
{
    vector<int> parse;

    for (char d : input)
        parse.push_back(d - '0');

    return parse;
}

int get_bulls(const vector<int>& digits, const vector<int>& guess)
// Get number of positions in two vectors wich have the same value
// Pre-condition:
//  Both vectors have the same number of elements
// Post-condition:
//  bulls must be 4 or less
{
    int bulls = 0;

    if (digits.size() != guess.size())
        throw runtime_error(ex_msg_distinct_size);

    for (size_t i = 0; i < digits.size(); ++i)
        if (digits[i] == guess[i]) ++bulls;

    if (bulls > 4)
        throw runtime_error(ex_msg_distinct_size);

    return bulls;
}

int get_cows(const vector<int>& digits, const vector<int>& guess)
// Get how many numbers from guess are present on digits but not in
// the same position.
// Post-condition:
//  cows must be 4 or less (given that elements on guess and digits are unique)
{
    int cows = 0;

    for (size_t i = 0; i < guess.size(); ++i)
        for (size_t j = 0; j < digits.size(); ++j)
            if (i != j && guess[i] == digits[j]) ++cows;

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
    // Number to guess: 3461
    vector<int> digits = {3, 4, 6, 0};
    string input = "";
    vector<int> guess;
    int bulls = 0;
    int cows = 0;

    cout << "Welcome to Bulls and Cows.\n"
         << "Try to guess the four digit sequence I'm thinking about.\n"
         << "No digit appears more than once and I will give you clues,\n"
         << "with \"bulls\" being correct digits in the right position\n"
         << "and \"cows\" being correct digits in wrong position.\n"
         << "Let's start! Your guess ...\n? ";

    while (cin >> input) {
        if (bulls == 4) {
            if (check_input(input)) {
                guess = parse_input(input);
                bulls = get_bulls(digits, guess);
                cows = get_cows(digits, guess);
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
    cout << "Error: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cout << "Unknown exception!\n";
    return 2;
}
