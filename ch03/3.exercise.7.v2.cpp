#include "std_lib_facilities.h"

template <typename T>
inline void xchg(T& a, T& b)
{
    T tmp;

    tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    cout << "Enter three strings: ";
    string val1 {" "};
    string val2 {" "};
    string val3 {" "};
    cin >> val1 >> val2 >> val3;

    // A step by step bubble sort
    if (val1 > val2)
        xchg(val1, val2);
    if (val2 > val3)
        xchg(val2, val3);
    if (val1 > val2)
        xchg(val1, val2);

    cout << val1 << ", " << val2 << ", " << val3 << '\n';
}
    
