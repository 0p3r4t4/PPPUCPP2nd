#include "std_lib_facilities.h"

int main()
{
    cout << "Enter an integer number to know if it's even or odd: ";
    int number {0};
    cin >> number;

    if (number % 2 == 0)
        cout << "The value " << number << " is an even number\n";
    else
        cout << "The value " << number << " is an odd number\n";

    return 0;
}
