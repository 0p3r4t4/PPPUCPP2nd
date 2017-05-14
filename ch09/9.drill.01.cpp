// 9.drill.01.cpp
//
//  This drill simply involves getting the sequence of versions of Date to
//  work. For each version define a Date called today initialized to June 25,
//  1978. Then, define a Date called tomorrow and give it a value by copying
//  today into it and increasing its day by one using add_day(). Finally,
//  output today and tomorrow using a << defined as in §9.8.
//  Your check for a valid date may be very simple. Feel free to ignore leap
//  years. However, don't accept a month that is not in the [1,12] range or
//  day of the month that is not in the [1,31] range. Test each version with at
//  least one invalid date (e.g., 2004, 13, -5).
//
//  The version from §9.4.1
//
// COMMENTS
//
//  I will not do this by separating Date class, Month enumerator or helper
//  functions in their own header file. Just for the shake of simplicity.
//
//  add_day() will be implemented supposing all months have 31 days. It will
//  complicate it to do better until best tools, as enums, are introduced.

#include "std_lib_facilities.h"

struct Date {
    int y;      // year
    int m;      // month in year
    int d;      // day of month
};

void init_day(Date& dd, int y, int m, int d)
// Simply (and incorrect) day initializer with simply (and incorrect) checks.
{
    if (d < 1 || d > 31) error("init_day: Invalid day");
    if (m < 1 || m > 12) error("init_day: Invalid month");

    dd.y = y;       // We don't check valid year yet
    dd.m = m;
    dd.d = d;
}

void add_day(Date& dd, int n)
// Function to add or substract days from a Date.
{
    dd.d += n;
     
    // We must check for overflows, and n can be negative!!
    if (dd.d > 31) { ++dd.m; dd.d -= 31; }     // Day overflow
    if (dd.d < 1)  { --dd.m; dd.d += 31; }     // Day underflow
    // We have modified month, so we must check it
    if (dd.m > 12) { ++dd.y; dd.m -= 12; }     // Month overflow
    if (dd.m < 1)  { --dd.y; dd.m += 12; }     // Month underfow
}

ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.y
              << ',' << d.m
              << ',' << d.d << ')';
}

int main()
try
{
    Date today;
    init_day(today, 1978, 6, 25);

    Date tomorrow{today};
    add_day(tomorrow, 1);

    cout << "Today: " << today << '\n';
    cout << "Tomorrow: " << tomorrow << '\n';

    // Check add_day() overflow (far from perfect) detection 
    Date test;

    init_day(test, 2010, 12, 31);
    add_day(test, 6);   // 2011 January 6th
    cout << "January the 6th 2011? " << test << '\n';
    add_day(test, -6);  // 2010 December 31st again
    cout << "December the 31st 2010? " << test << '\n';

    init_day(test, 2010, 2, 5);
    add_day(test, -7);   // 2010 January 29th 
    cout << "January the 29th 2010? " << test << '\n';
    add_day(test, 7);  // 2010 February 5th again 
    cout << "February the 5th 2010? " << test << '\n';

    // Invalid date
    Date today_e;
    init_day(today_e, 2004, 13, -5);

    return 0;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch(...)
{
    cerr << "Unknown exception!!\n";
    return 2;
}
