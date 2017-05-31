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
//
//  With Date::add_month() we have to decide. A month is a variable amount of
//  days. If day of the month is between 1 and 28, there is little to argue.
//  But, what if be add a month to March 31st? We have many options, mainly:
//
//      - the "last day" option, so the result will be April 30th.
//      - the "offset" option, remaining days are added so it will be May 1st.
//      - the "administrative" option, which takes a month as 30 days, no less,
//      no more.
//
//  The "administrative" will be te simplest one, and it as valid as imprecise.
//  Between the other two, the "last day" option is what Java and OracleDB do.
//  It says "If date is the last day of the month or if the resulting month has
//  fewer days than the day component of date, then the result is the last day
//  of the resulting month. Otherwise, the result has the same day component as
//  date". I feel more inclined to this one although the arithmetic is weird.
//  For example, add one month and another one result could be different than
//  adding two months:
//
//      2016/1/31 + 1 month -> 2016/2/29 + 1 month -> 2016/3/29
//      2016/1/31 + 2 months -> 2016/3/31
//
//  But for me, it makes sense to respect "last day" of the month concept.
//
//  Using a days since epoch representation simplifies a lot the
//  implementation (except previous trivial accessors year(), month() and
//  day()). Also it makes useless member and helper functions and operator
//  overloads that are needed with the y,m,d representation.
//  I know my current implementation is far from efficient, but I really get
//  tired of date manipulation, so let it be.

#include "std_lib_facilities.h"
#include "9.exercise.12.Chrono.h"

void test_days_since_epoch(Chrono::Date d)
{
    cout << "Chrono::Date::days_since_epoch(): " << d.days_since_epoch() 
         << " days have passed since epoch until " << d << '\n';
}
    
void test_add_day(Chrono::Date d, int nd, string msg)
{
    d.add_day(nd);
    cout << "Chrono::Date::add_day(" << nd << "): " << msg << d << '\n';
}

void test_add_month(Chrono::Date d, int nm, string msg)
{
    d.add_month(nm);
    cout << "Chrono::Date::add_month(" << nm << "): " << msg << d << '\n';
}

void test_add_year(Chrono::Date d, int ny, string msg)
{
    d.add_year(ny);
    cout << "Chrono::Date::add_year(" << ny << "): " << msg << d << '\n';
}

void test_day_of_week(Chrono::Date d)
{
    cout << "Chrono::day_of_week(): " << d << " is " 
         << Chrono::day_of_week(d) << '\n';
}

void test_next_sunday(Chrono::Date d)
{
    cout << "Chrono::next_Sunday(): Next sunday to " << d << " (" 
         << Chrono::day_of_week(d) << ") is " << Chrono::next_Sunday(d) 
         << " (" << Chrono::day_of_week(Chrono::next_Sunday(d)) << ")\n";
}

void test_next_workday(Chrono::Date d)
{
    cout << "Chrono::next_workday(): Next workday to " << d << " (" 
         << Chrono::day_of_week(d) << ") is " << Chrono::next_workday(d) 
         << " (" << Chrono::day_of_week(Chrono::next_workday(d)) << ")\n";
}

void test_week_of_year(Chrono::Date d)
{
    cout << "Chrono::week_of_year(): For date " << d << " week of the year is " 
         << Chrono::week_of_year(d) << '\n';
}

int main()
try
{
    Chrono::Date date;

    cout << '\n';
    test_days_since_epoch(date);
    test_days_since_epoch(Chrono::Date{2017, Chrono::Month::dec, 1});
    test_days_since_epoch(Chrono::Date{2017, Chrono::Month::dec, 31});
    test_days_since_epoch(Chrono::Date{17531});
    test_days_since_epoch(Chrono::Date{2018, Chrono::Month::jan, 1});
    test_days_since_epoch(Chrono::Date{17533});

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

    cout << '\n';
    date = Chrono::Date{2016, Chrono::Month::jan, 1};
    test_add_month(date, 1, "February the 1st 2016? ");
    test_add_month(date, 3, "April the 1st 2016? ");
    test_add_month(date, 6, "July the 1st 2016? ");
    test_add_month(date, 10, "November the 1st 2016? ");
    test_add_month(date, 15, "April the 1st 2017? ");
    date = Chrono::Date{2016, Chrono::Month::jan, 15};
    test_add_month(date, 1, "February the 15th 2016? ");
    test_add_month(date, 3, "April the 15th 2016? ");
    test_add_month(date, 6, "July the 15th 2016? ");
    test_add_month(date, 10, "November the 15th 2016? ");
    test_add_month(date, 15, "April the 15th 2017? ");
    date = Chrono::Date{2016, Chrono::Month::jan, 31};
    test_add_month(date, 1, "February the 29th 2016? ");
    test_add_month(date, 3, "April the 30th 2016? ");
    test_add_month(date, 6, "July the 31th 2016? ");
    test_add_month(date, 10, "November the 30th 2016? ");
    test_add_month(date, 15, "April the 30th 2017? ");
    date = Chrono::Date{2016, Chrono::Month::feb, 29};
    test_add_month(date, 1, "March the 29th 2016? ");
    test_add_month(date, 12, "February the 28th 2017? ");

    cout << '\n';
    date = Chrono::Date{2016, Chrono::Month::jan, 1};
    test_add_year(date, 1, "January the 1st 2017? ");
    test_add_year(date, 4, "January the 1st 2020? ");
    test_add_year(date, 8, "January the 1st 2024? ");
    date = Chrono::Date{2016, Chrono::Month::feb, 29};
    test_add_year(date, 1, "February the 28th 2017? ");
    test_add_year(date, 4, "February the 29th 2020? ");
    date = Chrono::Date{2016, Chrono::Month::mar, 15};
    test_add_year(date, 1, "March the 15th 2017? ");
    test_add_year(date, 4, "March the 15th 2020? ");
    date = Chrono::Date{2015, Chrono::Month::mar, 15};
    test_add_year(date, 1, "March the 15th 2016? ");
    test_add_year(date, 4, "March the 15th 2019? ");
    /*

    cout << '\n';
    test_day_of_week(Chrono::Date{1970, Chrono::Month::jan, 1});
    test_day_of_week(Chrono::Date{1978, Chrono::Month::feb, 23});
    test_day_of_week(Chrono::Date{2010, Chrono::Month::mar, 31});
    test_day_of_week(Chrono::Date{2017, Chrono::Month::may, 28});

    cout << '\n';
    test_next_sunday(Chrono::Date{2017, Chrono::Month::may, 28});
    test_next_sunday(Chrono::Date{2017, Chrono::Month::may, 24});
    test_next_sunday(Chrono::Date{2017, Chrono::Month::may, 29});

    cout << '\n';
    test_next_workday(Chrono::Date{2017, Chrono::Month::may, 24});
    test_next_workday(Chrono::Date{2017, Chrono::Month::may, 26});
    test_next_workday(Chrono::Date{2017, Chrono::Month::may, 27});
    test_next_workday(Chrono::Date{2017, Chrono::Month::may, 28});

    cout << '\n';
    test_week_of_year(Chrono::Date{2017, Chrono::Month::jan, 1});
    test_week_of_year(Chrono::Date{2017, Chrono::Month::jan, 9});
    test_week_of_year(Chrono::Date{2017, Chrono::Month::feb, 7});
    test_week_of_year(Chrono::Date{2017, Chrono::Month::mar, 15});
    test_week_of_year(Chrono::Date{2017, Chrono::Month::may, 28});
    */

    cout << '\n';
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
