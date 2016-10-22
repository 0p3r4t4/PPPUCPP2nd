#include "std_lib_facilities.h"

const vector<string> names {"zero",
    "one", "two", "three", "four",
    "five", "six", "seven", "eight",
    "nine"};

int get_number()
{
    string name;
    int number;
    int result {-1};

    if (cin >> number)
        if (number<0 || number >= names.size())
            result = -1;
    else {
        cin.clear();
        cin >> name;
        if (name == "|")
            result = -2;
        for (size_t i = 0; i < names.size(); ++i) 
            if (names[i] == name) result = i;
    }
    
    return result;
}

int main()
{
    bool quit {false};

    cout << "The Calculator ...\n";
        << "Insert two operands (from 0 to 9, on digits or spelled out)"
        << "separated by an operation (+,-,*,/): "
        << "(Insert | char tu quit)\n";

    
    while (!quit) {
        int op_a = get_number();
        char oper {' '};
        cin >> oper;
        int op_b = get_number();
        
        switch (get_number()) {
            case -2:
                cout << "Not a decimal cipher name, I guess. Try again.\n";
                break;;
            case -1:
                cout << "One-digit number, Pleeeeeeaseeee....\n";
                break;;
            default:
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
