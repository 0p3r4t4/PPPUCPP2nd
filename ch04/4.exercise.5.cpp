#include "std_lib_facilities.h"

int main()
{
    cout << "The Calculator ...\n";
    cout << "Insert two operands and an operation (+,-,*,/): ";

    double op_a {0};
    double op_b {0};
    char oper {' '};

    while (cin >> op_a >> op_b >> oper) {
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
	    cout << "Insert two operands and an operation (+,-,*,/): ";
    }

    return 0;
}
