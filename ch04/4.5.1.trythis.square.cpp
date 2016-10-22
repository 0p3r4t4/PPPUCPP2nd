#include "std_lib_facilities.h"

int square(int x)
{
    int s {0};

    for (int i=0; i<x; ++i)
        s += x;

    return s;
}

int main()
{
    cout << "Number" << '\t' << "Square" << '\n';

    for (int i=0; i<100; ++i)
        cout << i << '\t' << square(i) << '\n';

    return 0;
}
