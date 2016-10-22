#include "std_lib_facilities.h"

int main()
{
    cout << "Please write number of miles you want to convert to kilometers: ";
    double miles {0.0};
    cin >> miles;
    cout << miles << " miles are equivalent to " << miles*1.609 << " kilometers.\n";

    return 0;
}
