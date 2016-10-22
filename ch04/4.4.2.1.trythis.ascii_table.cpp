#include "std_lib_facilities.h"

int main()
{
    char c {'a'};
    cout << "char" << '\t' << "int value" << '\n';

    while (c<='z'){
        cout << c << '\t' << int(c) << '\n';
        ++c;
    }

    return 0;
}
