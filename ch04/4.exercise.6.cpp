// 4.exercise.6.cpp
//
// Make a vector holding ten string values "zero", "one", ... "nine".
// Use that in a program that converts a digit to its corresonding
// spelled-out value; e.g. the input 7 gives the output seven. Hava
// the same program, using the same input loop, convert spelled-out
// numbers into their digit form; e.g. the input seven gives the
// output 7.
//
// Comments:
//  As stated by Bjarne Stroustrup in his "Selected Exercise Solutions"
//  cin.clear() is needed to solve this problem without making the
//  program too complicated. Since iostreams and their functions are
//  exposed later on the book, we are cheating a bit.
//
#include "std_lib_facilities.h"

const vector<string> names {"zero", "one", "two",
    "three", "four", "five", "six", 
    "seven", "eight", "nine"};

int get_number(string name)
{
    int result {-1};
    for (size_t i = 0; i < names.size(); ++i) 
        if (names[i] == name) result = i;

    return result;
}

int main()
{
    int number {0};
    string name {""};
    bool quit {false};

    cout << "Insert a one-digit number to get its name.\n"
        << "Insert a cipher name to get the number.\n"
        << "(Insert | char tu quit)\n";
    
    while (!quit) {
        if (cin >> number) {
            if (number<0 || number>10)
                cout << "One-digit number, Pleeeeeeaseeee....\n";
            else
                cout << names[number] << '\n';
        }
        else {
            // The cheat. clear() return us to the begining of the input
            cin.clear();
            cin >> name;
            if ( name == "|" )
                quit = true;
            else {
                int n = get_number(name);
                if (n == -1)
                    cout << "Not a decimal cipher name, I guess. Try again.\n";
                else
                    cout << get_number(name) << '\n';
            }
        }
    }

    return 0;
}
