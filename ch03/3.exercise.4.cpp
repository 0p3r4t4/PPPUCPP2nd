#include "std_lib_facilities.h"

int main()
{
    cout << "Enter two integer values: ";
    int val1 {0};
    int val2 {0};
    cin >> val1 >> val2;
    if (val1 < val2)
        cout << "The smaller is " << val1 << " and the larger is " << val2 << ".\n";
    else
        cout << "The smaller is " << val2 << " and the larger is " << val1 << ".\n";
    cout << val1 << " + " << val2 << " = " << val1+val2 << '\n';
    cout << val1 << " - " << val2 << " = " << val1-val2 << '\n';
    cout << val1 << " * " << val2 << " = " << val1*val2 << '\n';
    cout << val1 << " / " << val2 << " = " << val1/val2 << '\n';
}
    
