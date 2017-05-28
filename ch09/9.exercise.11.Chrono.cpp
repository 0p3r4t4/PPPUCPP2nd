// 9.exercise.11.Chrono.cpp

#include "std_lib_facilities.h"
#include "9.exercise.11.Chrono.h"

namespace Chrono {

// Day enum class operators

Day operator+(const Day& d, int n)
{
    int r = int(d) + n;
    r %= 7;     // Magic number? I don't think we'll need to chenge 
                // number of days in a week. By now.
    return Day(r);
}

Day& operator+=(Day& d, int n) { d = d + n; return d; }

ostream& operator<<(ostream& os, const Day& d)
{
    switch (d) {
        case Day::sunday:    os << "sunday"; break;
        case Day::monday:    os << "monday"; break;
        case Day::tuesday:   os << "tuesday"; break;
        case Day::wednesday: os << "wednesday"; break;
        case Day::thursday:  os << "thursday"; break;
        case Day::friday:    os << "friday"; break;
        case Day::saturday:  os << "saturday"; break;
        default: error("Day output: invalid day");
    }

    return os;
}

// Month enum class operators

Month operator+(const Month& m, int n)
{
    int r = int(m) + n;
    r %= int(Month::dec);

    if (r == 0) return Month::dec;  // Revert effect of modulo ...
    return Month(r);
}

// Define other operators based on +
Month operator-(const Month& m, int n) { return (m+(-n)); }
Month& operator+=(Month& m, int n) { m = m + n; return m; }
Month& operator++(Month& m) { m = m + 1; return m; }

bool operator<(const Month& m, int n) { return int(m) < n; }
bool operator>(const Month& m, int n) { return int(m) > n; }

// Month helper functions

int month_days(Month m, bool leap)
{
    switch (m) {
        case Month::jan: return 31;
        case Month::feb: 
            if (leap) return 29;
            return 28;
        case Month::mar: return 31;
        case Month::apr: return 30;
        case Month::may: return 31;
        case Month::jun: return 30;
        case Month::jul: return 31;
        case Month::aug: return 31;
        case Month::sep: return 30;
        case Month::oct: return 31;
        case Month::nov: return 30;
        case Month::dec: return 31;
        default:
            error("month_days(): invalid month");
    }
}

// Date member function definitions

Date::Date(int yy, Month mm, int dd)
        :y{yy}, m{mm}, d{dd}
{
    if (!is_date(yy, mm, dd)) throw Invalid{};
}

const Date& default_date()
{
    static Date dd{2001, Month::jan, 1};    // start of 21st century
    return dd;
}

Date::Date():
    y{default_date().year()},
    m{default_date().month()},
    d{default_date().day()}
{
}

void Date::add_day(int n)
{
    if (n < 0) error("Date::add_day(): only positives increments allowed.");

    int n_y{365};
    if (leapyear(y)) ++n_y; 
    // Add year by year decrementing n by year (leap or common) year.
    while (n >= n_y) {
        ++y;
        n -= n_y;
        if (leapyear(y)) n_y = 365; 
        else n_y = 366;
    }

    int n_m{month_days(m, leapyear(y))};
    // Add month by month decrementing n by month days.
    while (n >= n_m) {
        ++m;
        n -= n_m;
        n_m = month_days(m, leapyear(y));
        if (m == Month::jan) ++y;   // year overflow
    }

    d = (d+n) % month_days(m, leapyear(y));  // add days modulo days of month
    if (d == 0) d = month_days(m, leapyear(y)); // modulo is 0 if we reach last
                                                // day of the month
    if (d <= n) ++m;   // Month has overflowed
}

void Date::add_month(int n)
{
    int n_m = n % 12;   // months out of years, to increase
    int n_y = n / 12;   // years to increase

    // Month type takes care of itself on overflows, but we loose track to 
    // modify year if it happens. We must check it before actually operate
    // on m.
    if (Month::dec < (int(m)+n_m)) ++n_y;
    if (Month::jan > (int(m)+n_m)) --n_y;
    m += n_m;   // m is of Month type
    y += n_y;
}

void Date::add_year(int n)
{
    // beware of leap years!
    if (m == Month::feb && d == 29 && !leapyear(y+n)) {
        m = Month::mar;     // use March 1 instead of February 29
        d = 1;
    }
    y += n;
}

// helper functions

bool is_date(int y, Month m, int d)
{
    if (y < epoch_year) return false; // Limit our representation
    if (d <= 0) return false;   // d must be positive
    if (m < Month::jan || m > Month::dec) return false;

    int days_in_month = 31;     // most months have 31 days

    switch (m) {
    case Month::feb:            // the length of February varies
        days_in_month = (leapyear(y)) ? 29 : 28;
        break;
    case Month::apr:
    case Month::jun:
    case Month::sep:
    case Month::nov:
        days_in_month = 30;
        break;
    default:       // Not really needed but avoid compiler warnings
        break;
    }

    return days_in_month >= d;
}

bool leapyear(int y)
{
    return ((y%4 == 0) && !(y%100 == 0)) || (y%400 == 0);
}

bool operator==(const Date& a, const Date& b)
{
    return a.year()  == b.year() 
        && a.month() == b.month()
        && a.day()   == b.day();
}

bool operator!=(const Date& a, const Date& b)
{
    return !(a == b);
}

bool operator<(const Date& a, const Date& b)
{
    if (a.year() != b.year()) return (a.year() < b.year());
    if (a.month() != b.month()) return (a.month() < b.month());
    return (a.day() < b.day());
}

bool operator<=(const Date& a, const Date& b)
{
    return ((a < b) || (a == b));
}

ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.year()
              << ',' << int(d.month())
              << ',' << d.day() << ')';
}

istream& operator>>(istream& is, Date& dd)
{
    int y, m, d;
    char ch1, ch2, ch3, ch4;
    is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
    if (!is) return is;
    if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') { // format error
        is.clear(ios_base::failbit);    // set the fail bit
        return is;
    }

    dd = Date{y, Month(m), d};

    return is;
}

Day day_of_week(const Date& d)
{
    int y{d.year()};
    Day dow{epoch_dow};

    for (int i = epoch_year; i < y; ++i) {
        if (leapyear(i)) dow += 366;
        else dow += 365;
    }

    Month m{d.month()};
    for (Month i = Month::jan; i < m; ++i) {
        dow += month_days(i, leapyear(y));
    }

    dow += (d.day() - 1);

    return dow;
}

Date next_Sunday(const Date& d)
// return next sunday date to d. If d is currently sunday return
// a week in advance
{
    Day dow{day_of_week(d)};    // Day of the week for Date d
    Date r{d};
    r.add_day(7 - int(dow));
    return r;
}

Date next_workday(const Date& d)
{
    Day dow{day_of_week(d)};    // Date of the week for Date d
    Date r{d};

    r.add_day(1);
    if (dow == Day::saturday) r.add_day(1);
    if (dow == Day::friday ) r.add_day(2);

    return r;
}

int week_of_year(const Date& d)
// As exercise 11 statement says, we assume that the first week is that
// with January 1 in it, and that a week starts on sunday.
{
    Date wd{Date(d.year(), Month::jan, 1)}; // First week date
    int week{1};

    wd = next_Sunday(wd);
    while (wd <= d) {   // if date is on sunday, we must reach it
        wd = next_Sunday(wd);
        ++week;
    }

    return week;
}

} // namespace Chrono
