// 6.exericise.09.cpp
//
// Write a program that reads digits and composes them into integers. For
// example, 123 is read as the characters 1, 2 and 3. The program should output
// 123 is 1 hundred and 2 tens and 3 ones. The number should be output as an
// int value. Handle numbers with one, two, three, or four digits. Hint: to get
// the integer value 5 from the character '5' substract '0', that is,
// '5'-'0'==5.
//
// Comments:
//
//  This is the kind of exercise that makes me feel unconfortable; there is
//  a simpler way of doing it. Why not read an integer and decompose it
//  instead? The output will be the same without the user noticing it.
//  Whatever, the requisites are clear so let's go for it.
//
//  We must read the input as a string. It's very much like I do in
//  5.exercise.12.cpp, so let's borrow some functions from it (check_input()
//  and parse_input()) and do some slight modifications to accomodate.
//
//  We must compose the integer and somehow retain the original digit by digit
//  data to do the verbose output. For the output we will do a trick with 
//  a predefined vector of strings named powers; see print_output() for
//  details.

#include "std_lib_facilities.h"

static const string ex_msg_greater_than =
        "Your input is greater than I can manage.";
static const string ex_msg_not_only_digits =
        "Your input is not an integer number.";

static const vector<string> powers = {"thousand", "hundred", "ten", "one"};

bool check_input(const string& input)
// Checks input to be equal or less digits than we're able to manage .
// Pre-conditions:
//  The length of the string must be less or equal to powers.size()
//  Each character of the string must be an ASCII (or compatible, as ISO or UTF8)
//      value for chars from '0' to '9' (they are consecutive).
try
{
    if (input.length() > powers.size()) throw runtime_error(ex_msg_greater_than);

    for (char c : input)
        if (c < '0' || c > '9')
            throw runtime_error(ex_msg_not_only_digits);

    return true;
}
catch (exception& e)
{
    cout << e.what() << '\n';
    return false;
}

vector<int> parse_input(const string& input)
// Converts a digits string to a vector of ints 
// Pre-condition:
//  input has to have been checked by check_input()
{
    vector<int> parse;

    for (char d : input) {
        // Ignore leading 0's
        if (parse.size() != 0 || d != '0')
            parse.push_back(d - '0');
    }
    // Manage the case where user has introduced 0 as a number
    // We can do it in the former for if we change it to
    // a classical form to inspect the current index to input.
    if (parse.size() == 0)
        parse.push_back(0);

    return parse;
}

int compose_integer(const vector<int>& digits)
// Compose an integer number out of its digits
// I could do this on parse_input, but let's enforce the principle of
// a function doing just one thing.
{
    int result = 0;

    for (int d: digits)
        result = result*10 + d;

    return result;
}

void print_output(int result, const vector<int>& digits)
// Print composed integer result and do verbose output based on digits and
// powers.
{
    cout << result << " is ";
    // index to start the walk on powers vector, so number of digits
    // tell us if we have thousands or not, hundreds or not, and so on.
    size_t idx = powers.size() - digits.size();
    for (int d : digits) {
        // We manage plurals with the ternary operator
        cout << d << ' ' << powers[idx] << ( d == 1 ? " " : "s " );
        ++idx;
        if (idx < powers.size())
            cout << "and ";
    }
    cout << '\n';
}

int main()
try{
    string input = "";
    vector<int> digits;
    int composed = 0;

    cout << "Integer number composer.\n"
         << "Introduce an integer number of " << powers.size() << " or less digits.\n"
         << "Terminate the program with Ctrl+D (or Ctrl+Z).\n";

    while (cin >> input) {
        if (check_input(input)) {
            digits = parse_input(input);
            composed = compose_integer(digits);
            print_output(composed, digits);
        }
    }
    if (cin.eof()) {
        cout << "Bye!\n";
    }

    return 0;
}
catch(exception& e)
{
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch(...)
{
    cerr << "Oops! Unknown exception!\n";
    return 2;
}
