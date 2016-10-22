#include "std_lib_facilities.h"
#include <locale>

int main()
{
    cout << "Please enter an integer value: ";
    int n;
    cin >> n;
    double dn = n;
    //cout.imbue(locale("es_ES.UTF-8"));
    cout.imbue(locale(""));     // Imbue cout with environment locale
    cout << "n == " << n
        << "\nn+1 == " << n+1
        << "\nthree times n == " << 3*n
        << "\ntwice n == " << n+n
        << "\nn squared == " << n*n
        << "\nhalf of n == " << n/2
        << "\nsquare root of n == " << sqrt(dn)
        << "\nmodulo 10 of n == " << n%10
        << boolalpha << "\nn is greater than 10 == " << (n>10)
        << '\n';
}
