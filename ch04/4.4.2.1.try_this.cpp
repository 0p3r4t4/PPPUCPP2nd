// 4.4.2.1.try_this.cpp
//
// The character 'b' is char('a'+1), 'c' is char('a'+2), etc. Use a loop to
// write out a table of characters with their corresponding integer values:
//
//  a   97
//  b   98 
//  ...
//  z   122

#include "std_lib_facilities.h"

int main()
{
    char c {'a'};
    cout << "char" << '\t' << "int value" << '\n';

    while (c <= 'z'){
        cout << c << '\t' << int(c) << '\n';
        ++c;
    }

    return 0;
}
