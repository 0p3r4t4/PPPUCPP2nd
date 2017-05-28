// 9.exercise.11.cpp
//
//  Design and implement a set of useful helper functions for the Date class
//  with functions such as next_workday() (assume that any day that is not a
//  Saturday or a Sunday is a workday) and week_of_year() (assume that week 1
//  is the week with January 1 in it and that the first day of a week is a
//  Sunday).
//
// COMMMENTS
//
//  next_workday() is presented in §9.8 as next_weekday(). I'll replace it.
//  To implement these functions, day_of_week() and next_Sunday() seem
//  convenient.
//
//  To simplify a bit and seeing that the next exercise tell us to change
//  representation to the number of days since January, the first 1970 (the
//  "epoch") and since managing dates previous to that implies negative numbers
//  and added complexity, I'll restrict date to be posterior to the epoch.
//
//  I also define +, += and << operators for Day, a ++ operator for Month, and 
//  a month_days() that returns the days of a month.
//
//  day_of_week() could be implemented more efficiently, of course. But I
//  choose the finger count.
//  next_workday() could be better, also. Read the comment on the body of the
//  function.
//

#include "std_lib_facilities.h"
#include "9.exercise.11.Chrono.h"

int main()
try
{
    // Test Chrono::day_of_week()
    Chrono::Date date{1970, Chrono::Month::jan, 1};
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
