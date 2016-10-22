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
