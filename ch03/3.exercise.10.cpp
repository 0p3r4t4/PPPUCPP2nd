#include "std_lib_facilities.h"

int main()
{
    cout << "Write an operation (+ or plus, - or minus, * or mul and / or div)\n"
        "followed by two numbers: ";
    string op {" "};
    double a {0};
    double b {0};
    cin >> op >> a >> b;

    if (op == "+" || op == "plus")
        cout << a << " + " << b << " = " << a+b << '\n';
    else if (op == "-" || op == "minus")
        cout << a << " - " << b << " = " << a-b << '\n';
    else if (op == "*" || op == "mul")
        cout << a << " * " << b << " = " << a*b << '\n';
    else if (op == "/" || op == "div")
        cout << a << " / " << b << " = " << a/b << '\n';
    else
        cout << "Operator " << op << " is not known.\n";

    return 0;
}
