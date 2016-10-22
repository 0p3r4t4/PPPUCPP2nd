#include "std_lib_facilities.h"

constexpr double TOLERANCE = 1.0/100;

double min(double a, double b)
{
    if (a<b)
        return a;
    else 
        return b;
}

double max(double a, double b)
{
    if (a>=b)
        return a;
    else 
        return b;
}

bool almost_equal(double a, double b)
{
    if (abs(a-b) < TOLERANCE)
        return true;
    else
        return false;
}

int main()
{
    double a {0}; 
    double b {0}; 

    while (cin >> a >> b){
        if (a==b)
            cout << "the numbers are equal\n";
        else{
            cout << "the smaller value es: " << min(a, b) << '\n';
            cout << "the larger value es: " << max(a, b) << '\n';
            if (almost_equal(a, b))
                cout << "the numbers are almost equal\n";
        }
    }

    return 0;
}
