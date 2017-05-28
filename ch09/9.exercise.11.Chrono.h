// 9.exercise.11.Chrono.h

#include "std_lib_facilities.h"

#ifndef CHRONO_H    // Since this header is included on two .cpp files
#define CHRONO_H    // an include guard must be issued

namespace Chrono {

constexpr int epoch_year{1970};   // Minimal date representation

enum class Day {
    sunday, monday, tuesday, wednesday, thursday, friday, saturday
};

constexpr Day epoch_dow{Day::thursday};  // Day of the week 1970/1/1

// Day enum class operators
Day operator+(const Day& d, int n);
Day& operator+=(Day& d, int n);
ostream& operator<<(ostream& os, const Day& d);

enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

// Month enum class helper functions
//
// returns days in month (common or leap year)
int month_days(Month m, bool leap);

// Month enum class operators
Month operator+(const Month& m, int n);
Month operator-(const Month& m, int n);
Month& operator+=(Month& m, int n);
Month& operator++(Month& m);

bool operator<(const Month& m, int n);
bool operator>(const Month& m, int n);

class Date {
public:
    class Invalid {};               // to throw as exception

    Date(int yy, Month mm, int dd); // check for valid date and initialize
    Date();                         // default constructor
    // the default copy operations are fine

    // nonmodifying operations
    int day() const { return d; }
    Month month() const { return m; }
    int year() const { return y; }

    // modifying operations
    void add_day(int n);
    void add_month(int n);
    void add_year(int n);
private:
    int y;          // year
    Month m;
    int d;          // day
};

bool is_date(int y, Month m, int d);    // true for valid date
bool leapyear(int y);                   // true if y is a leap year

// Date class operators
bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& dd);

Day day_of_week(const Date& d);     // day of week of d
Date next_Sunday(const Date& d);    // next Sunday after d
Date next_workday(const Date& d);   // next workday after d
int week_of_year(const Date& d);    // ordinal week of the year of d

} // namespace Chrono

#endif
