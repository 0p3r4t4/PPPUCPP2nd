// 4.exercise.07.cpp
//
//  Modify the "mini calculator" from exercise 5 to accept (just)
//  single digit numbers written as either digits or spelled out
//
//  Comments:
//      Taking detailed care of input could meake the program extremely
//      complicated. So, the main loop is stopped by forcing it (Ctrl+C)
//      as clearing cin somehow gets rid of end of input (Ctrl+D, Ctrl+Z)
//      and I really have been stuck with this exercise too much time
//      to investigate further.
//      And we cheat, just like in exeercise 6, by using cin.clear().
//      I expand the cheat by using cin.ignore() to discard input after a
//      bad read.

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
        // It's an integer number. Read about size_t below.
        if (number<0 || size_t(number) >= names.size())
            cout << "Operand " << number << " is not a single digit number\n";
        else
            result = number;
    else {
        // Clear cin state to be able to re-read
        cin.clear();
        //It's not an integer so we read it as string
        cin >> name;
        // cheat, cheat, cheat. size_t is an integer unsigned type for "sizes",
        // so I use it here as gcc with -Wall warnings about comparing signed
        // and unsigned integer expressions if I define i as int.
        for (size_t i = 0; i < names.size(); ++i) 
            if (names[i] == name) result = i;
        if (result == -1) 
            cout << "The name <" << name
                << "> do not correspond to any single digit number.\n";
    }
    
    return result;
}

int main()
{
    char oper {' '};
    int op_a {0};
    int op_b {0};

    cout << "The Single Digit Calculator ...\n"
        << "Insert two operands (from 0 to 9, on digits or spelled out) "
        << "separated by an operation (+,-,*,/):\n";
    
    while (true) {
        // I'm not actually proud of the structure of this code.
        // I feel it could have been done better. 
        op_a = get_number();
        if (op_a == -1) {
            // Clear error and discard the rest of the input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Try again:\n";
        }
        else {
            cin >> oper;
            op_b = get_number();
            if (op_b == -1) {
                // Clear error and discard the rest of the input
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Try again:\n";
            }
            else {
        
                switch (oper) {
                    case '+':
                        cout << "The sum of " << op_a << " and " << op_b 
                            << " is " << op_a+op_b << '\n';
                        break;;
                    case '-':
                        cout << "The difference of " << op_a << " and " << op_b 
                            << " is " << op_a-op_b << '\n';
                        break;;
                    case '*':
                        cout << "The product of " << op_a << " and " << op_b 
                            << " is " << op_a*op_b << '\n';
                        break;;
                    case '/':
                        if (op_b == 0)
                            cout << "ERROR: Division by zero\n";
                        else
                            cout << "The division of " << op_a << " and " << op_b 
                                << " is " << op_a/op_b << '\n';
                        break;;
                    default:
                        cout << "The operator " << oper << " is not supported!\n";
                        break;;
                }  
            }
        }
    }

    return 0;
}
