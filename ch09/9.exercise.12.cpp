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

int main()
try
{
    Chrono::Date date;
    // Check new add_day()
    date = Chrono::Date{2016, Chrono::Month::jan, 1};
    date.add_day(7);
    cout << "January the 8th 2016? " << date << '\n';
    date = Chrono::Date{2016, Chrono::Month::jan, 1};
    date.add_day(31);
    cout << "February the 1st 2016? " << date << '\n';
    date = Chrono::Date{2016, Chrono::Month::jan, 1};
    date.add_day(60);
    cout << "March the 1st 2016? " << date << '\n';
    date = Chrono::Date{2016, Chrono::Month::jan, 1};
    date.add_day(365);
    cout << "December the 31th 2016? " << date << '\n';
    date = Chrono::Date{2016, Chrono::Month::jan, 1};
    date.add_day(366);
    cout << "January the 1st 2017? " << date << '\n';
    date = Chrono::Date{2016, Chrono::Month::jan, 1};
    date.add_day(397);
    cout << "February the 1st 2017? " << date << '\n';
    date = Chrono::Date{2016, Chrono::Month::jan, 15};
    date.add_day(80);
    cout << "April the 4th 2016? " << date << '\n';

    // Test Chrono::day_of_week()
    date = Chrono::Date{1970, Chrono::Month::jan, 1};
    cout << date << " is " << Chrono::day_of_week(date) << '\n';
    date = Chrono::Date{1978, Chrono::Month::feb, 23};
    cout << date << " is " << Chrono::day_of_week(date) << '\n';
    date = Chrono::Date{2010, Chrono::Month::mar, 31};
    cout << date << " is " << Chrono::day_of_week(date) << '\n';
    date = Chrono::Date{2017, Chrono::Month::may, 28};
    cout << date << " is " << Chrono::day_of_week(date) << '\n';

    // Test Chrono::next_Sunday()
    date = Chrono::Date{2017, Chrono::Month::may, 28};
    cout << "Next sunday to " << date << " (" << Chrono::day_of_week(date)
         << ") is " << Chrono::next_Sunday(date) << " ("
         << Chrono::day_of_week(Chrono::next_Sunday(date)) << ")\n";
    date = Chrono::Date{2017, Chrono::Month::may, 24};
    cout << "Next sunday to " << date << " (" << Chrono::day_of_week(date)
         << ") is " << Chrono::next_Sunday(date) << " ("
         << Chrono::day_of_week(Chrono::next_Sunday(date)) << ")\n";
    date = Chrono::Date{2017, Chrono::Month::may, 29};
    cout << "Next sunday to " << date << " (" << Chrono::day_of_week(date)
         << ") is " << Chrono::next_Sunday(date) << " ("
         << Chrono::day_of_week(Chrono::next_Sunday(date)) << ")\n";

    // Test Chrono::next_workday()
    date = Chrono::Date{2017, Chrono::Month::may, 24};
    cout << "Next workday to " << date << " (" << Chrono::day_of_week(date)
         << ") is " << Chrono::next_workday(date) << " ("
         << Chrono::day_of_week(Chrono::next_workday(date)) << ")\n";
    date = Chrono::Date{2017, Chrono::Month::may, 26};
    cout << "Next workday to " << date << " (" << Chrono::day_of_week(date)
         << ") is " << Chrono::next_workday(date) << " ("
         << Chrono::day_of_week(Chrono::next_workday(date)) << ")\n";
    date = Chrono::Date{2017, Chrono::Month::may, 27};
    cout << "Next workday to " << date << " (" << Chrono::day_of_week(date)
         << ") is " << Chrono::next_workday(date) << " ("
         << Chrono::day_of_week(Chrono::next_workday(date)) << ")\n";
    date = Chrono::Date{2017, Chrono::Month::may, 28};
    cout << "Next workday to " << date << " (" << Chrono::day_of_week(date)
         << ") is " << Chrono::next_workday(date) << " ("
         << Chrono::day_of_week(Chrono::next_workday(date)) << ")\n";

    // Test Chrono::week_of_year()
    date = Chrono::Date{2017, Chrono::Month::jan, 1};
    cout << "For date " << date << " week of the year is " 
         << Chrono::week_of_year(date) << '\n';
    date = Chrono::Date{2017, Chrono::Month::jan, 9};
    cout << "For date " << date << " week of the year is " 
         << Chrono::week_of_year(date) << '\n';
    date = Chrono::Date{2017, Chrono::Month::feb, 7};
    cout << "For date " << date << " week of the year is " 
         << Chrono::week_of_year(date) << '\n';
    date = Chrono::Date{2017, Chrono::Month::mar, 15};
    cout << "For date " << date << " week of the year is " 
         << Chrono::week_of_year(date) << '\n';
    date = Chrono::Date{2017, Chrono::Month::may, 28};
    cout << "For date " << date << " week of the year is " 
         << Chrono::week_of_year(date) << '\n';

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
