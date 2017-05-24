// 9.exercise.10.cpp
//
//  Implement leapyear() from §9.8.
//
// COMMMENTS
//
//  This is easy as we can get the algorithm from the Wikipedia
//  (https://en.wikipedia.org/wiki/Leap_year):
//
//      Every year that is exactly divisible by four is a leap year, except for
//      years that are exactly divisible by 100, but these centurial years are
//      leap years if they are exactly divisible by 400.
//
//  and so:
//
//      if (year is not divisible by 4) then (it is a common year)
//      else if (year is not divisible by 100) then (it is a leap year)
//      else if (year is not divisible by 400) then (it is a common year)
//      else (it is a leap year)
//  
//  See implementation in 9.exercise.10.Chrono.cpp

#include "std_lib_facilities.h"
#include "9.exercise.10.Chrono.h"

int main()
{
    constexpr int inc{5};   // These are good values for viewing the results
    constexpr int cols{4};
    int col{0};

    // So test for some years
    for (int i = 1700; i < 2200; i+=inc) {
        cout << i << ": ";
        if (Chrono::leapyear(i)) cout << "LEAP year    ";
        else cout << "Common year  ";
        ++col;
        if (col == cols) {
            cout << '\n';
            col = 0;
        }
    }
    cout << '\n';
    
    return 0;
}
