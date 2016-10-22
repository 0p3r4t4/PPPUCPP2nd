#include "std_lib_facilities.h"

int main()
{
    cout << "Spell out a number, please: ";
    std::string text {" "};
    cin >> text;

    if (text == "zero")
        cout << 0 << '\n';
    else if (text == "one")
        cout << 1 << '\n';
    else if (text == "two")
        cout << 2 << '\n';
    else if (text == "three")
        cout << 3 << '\n';
    else if (text == "four")
        cout << 4 << '\n';
    else 
        cout << "not a number I know, sorry.\n";

    return 0;
}
