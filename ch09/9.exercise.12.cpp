// 9.exercise.12.cpp
//
//  Change the representation of a Date to be the number of days since January
//  1, 1970 (known as day 0), represented as a long int, and re-implement the
//  functions from §9.8. Be sure to reject dates outside the range we can
//  represent that way (feel free to reject days before day 0, i.e., no
//  negative days).
//
// COMMMENTS
//
//  Like previous exercise, I'll reference January 1, 1970 as epoch.
//  This is an almost complete rewrite of Chrono namespace and I will take the
//  chance to clean all I can.
//
//  Despite the internal representation we want to preserve the (y,m,d) format
//  to construct the Date and to input/output it. We can add a new constructor
//  with days since epoch as the only argument.

#include "std_lib_facilities.h"
#include "9.exercise.12.Chrono.h"

void test_days_since_epoch(Chrono::Date d)
{
    cout << d.days_since_epoch() << ' ' << d << ' ';
}
    
void test_add_day(Chrono::Date d, int nd, string msg)
{
    d.add_day(nd);
    cout << msg << d << '\n';
}

void test_day_of_week(Chrono::Date d)
{
    cout << d << " is " << Chrono::day_of_week(d) << '\n';
}

void test_next_sunday(Chrono::Date d)
{
    cout << "Next sunday to " << d << " (" << Chrono::day_of_week(d)
         << ") is " << Chrono::next_Sunday(d) << " ("
         << Chrono::day_of_week(Chrono::next_Sunday(d)) << ")\n";
}

void test_next_workday(Chrono::Date d)
{
    cout << "Next workday to " << d << " (" << Chrono::day_of_week(d)
         << ") is " << Chrono::next_workday(d) << " ("
         << Chrono::day_of_week(Chrono::next_workday(d)) << ")\n";
}

void test_week_of_year(Chrono::Date d)
{
    cout << "For date " << d << " week of the year is " 
         << Chrono::week_of_year(d) << '\n';
}

int main()
try
{
    Chrono::Date date;

    test_days_since_epoch(date);
    test_days_since_epoch(Chrono::Date{2017, Chrono::Month::dec, 1});
    test_days_since_epoch(Chrono::Date{2017, Chrono::Month::dec, 31});
    test_days_since_epoch(Chrono::Date{2018, Chrono::Month::jan, 1});
    cout << '\n';

    date = Chrono::Date{2016, Chrono::Month::jan, 1};
    test_add_day(date, 7, "January the 8th 2016? ");
    test_add_day(date, 31, "February the 1st 2016? ");
    test_add_day(date, 60, "March the 1st 2016? ");
    test_add_day(date, 365, "December the 31th 2016? ");
    test_add_day(date, 366, "January the 1st 2017? ");
    test_add_day(date, 397, "February the 1st 2017? ");
    date = Chrono::Date{2016, Chrono::Month::jan, 15};
    test_add_day(date, 80, "April the 4th 2016? ");

    // Test Chrono::day_of_week()
    test_day_of_week(Chrono::Date{1970, Chrono::Month::jan, 1});
    test_day_of_week(Chrono::Date{1978, Chrono::Month::feb, 23});
    test_day_of_week(Chrono::Date{2010, Chrono::Month::mar, 31});
    test_day_of_week(Chrono::Date{2017, Chrono::Month::may, 28});

    // Test Chrono::next_Sunday()
    test_next_sunday(Chrono::Date{2017, Chrono::Month::may, 28});
    test_next_sunday(Chrono::Date{2017, Chrono::Month::may, 24});
    test_next_sunday(Chrono::Date{2017, Chrono::Month::may, 29});

    // Test Chrono::next_workday()
    test_next_workday(Chrono::Date{2017, Chrono::Month::may, 24});
    test_next_workday(Chrono::Date{2017, Chrono::Month::may, 26});
    test_next_workday(Chrono::Date{2017, Chrono::Month::may, 27});
    test_next_workday(Chrono::Date{2017, Chrono::Month::may, 28});

    // Test Chrono::week_of_year()
    test_week_of_year(Chrono::Date{2017, Chrono::Month::jan, 1});
    test_week_of_year(Chrono::Date{2017, Chrono::Month::jan, 9});
    test_week_of_year(Chrono::Date{2017, Chrono::Month::feb, 7});
    test_week_of_year(Chrono::Date{2017, Chrono::Month::mar, 15});
    test_week_of_year(Chrono::Date{2017, Chrono::Month::may, 28});

    return 0;
}
catch (Chrono::Date::Invalid& e)
{
    cerr << "Invalid Date!!\n";
    return 1;
}
catch (exception& e)
{
    cerr << e.what() << '\n';
    return 2;
}
catch (...)
{
    cerr << "Unknown exception!\n";
    return 3;
}
