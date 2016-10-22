#include "std_lib_facilities.h"

int main()
{
    cout << "char" << '\t' << "int value" << '\n';

    for (char c='a'; c<='z'; ++c){
        cout << c << '\t' << int(c) << '\n';
    }
    for (char c='A'; c<='Z'; ++c){
        cout << c << '\t' << int(c) << '\n';
    }
    for (char c='0'; c<='9'; ++c){
        cout << c << '\t' << int(c) << '\n';
    }

    return 0;
}
