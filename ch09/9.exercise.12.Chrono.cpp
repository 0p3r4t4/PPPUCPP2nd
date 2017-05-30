// 9.exercise.12.Chrono.cpp

#include "std_lib_facilities.h"
#include "9.exercise.12.Chrono.h"

namespace Chrono {

// Day enum class operators

Day operator+(const Day& d, int n)
{
    int r{int(d)+n};
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
    int r{int(m)+n};
    r %= int(Month::dec);

    if (r == 0) return Month::dec;  // Revert effect of modulo ...
    return Month(r);
}
Month& operator++(Month& m) { m = m + 1; return m; }
/*
// Define other operators based on +
Month operator-(const Month& m, int n) { return (m+(-n)); }
Month& operator+=(Month& m, int n) { m = m + n; return m; }

bool operator<(const Month& m, int n) { return int(m) < n; }
bool operator>(const Month& m, int n) { return int(m) > n; }
*/
// Month helper functions

int month_days(Month m, int y)
{
    switch (m) {
        case Month::apr: case Month::jun:
        case Month::sep: case Month::nov:
            return 30;
        case Month::feb: 
            if (leapyear(y)) return 29;
            return 28;
        default:
            return 31;
    }
}

// Date member function definitions

Date::Date(int yy, Month mm, int dd)
{
    if (!is_date(yy, mm, dd)) throw Invalid{};
    dse = Chrono::days_since_epoch(yy, mm, dd);
}

Date::Date(long int days) : dse{days} 
{
    if (dse < 0) throw Invalid{};
}

Date::Date(): dse{0} { };

/*
const Date& default_date()
{
    static Date dd{2001, Month::jan, 1};    // start of 21st century
    return dd;
}
*/

int Date::day() const
{
    // dse = 0 -> January 1st
    return dse - Chrono::days_since_epoch(year(), month(), 1) + 1;
}

Month Date::month() const
{
    // remaining days from January 1st
    int y{year()};
    long int rd{dse - Chrono::days_since_epoch(year(), Month::jan, 1)};

    Month m{Month::jan};
    while (rd >= Chrono::month_days(m, y)) {
        rd -= Chrono::month_days(m, y);
        ++m;
    }

    return m;
}

int Date::year() const
{
    long int y{dse/365};
    long int rd{dse-(y*365)};
    if ((rd - n_leaps(epoch_year+y)) < 0 ) --y;  // Adjust days be leap years

    return (epoch_year + y);
}

long int Date::days_since_epoch() const
{
    return dse;
}

void Date::add_day(int n)
{
    if (n < 0) error("Date::add_day(): only positives increments allowed.");

    dse += n;
}

void Date::add_month(int n)
{
    if (n < 0) error("Date::add_month(): only positives increments allowed.");

    int y{year()};
    Month m{month()};

    for (int i = 0; i < n; ++i) {
        dse += month_days(m, y);
        ++m;
        if (m == Month::jan) ++y;
    }
}

void Date::add_year(int n)
{
}

// helper functions

bool is_date(int y, Month m, int d)
{
    if (y < epoch_year) return false; // Limit our representation
    if (d <= 0) return false;   // d must be positive
    if (m < Month::jan || m > Month::dec) return false;

    int month_days{31};     // most months have 31 days

    switch (m) {
    case Month::feb:            // the length of February varies
        month_days = (leapyear(y)) ? 29 : 28;
        break;
    case Month::apr:
    case Month::jun:
    case Month::sep:
    case Month::nov:
        month_days = 30;
        break;
    default:       // Not really needed but avoid compiler warnings
        break;
    }

    return month_days >= d;
}

bool leapyear(int y)
{
    return ((y%4 == 0) && !(y%100 == 0)) || (y%400 == 0);
}

int n_leaps(int y)
// return number of leap years from epoch_year to year previous to y
{
    if (y < epoch_year) throw Date::Invalid{};

    int n{0};
    for (int i = epoch_year; i < y; ++i)
        if (leapyear(i)) ++n;
    return n;
}

long int days_since_epoch(int y, Month m, int d)
{
    if (!is_date(y, m, d)) throw Date::Invalid{};
    
    int dse{0};

    dse += (y-epoch_year)*365 + n_leaps(y);
    for (Month i = Month::jan; i < m; ++i)
        dse += month_days(i, y);

    return (dse + d - 1);   // 1970 January 1st is our 0 day
}

bool operator==(const Date& a, const Date& b)
{
    return a.days_since_epoch() == b.days_since_epoch();
}

bool operator!=(const Date& a, const Date& b)
{
    return !(a == b);
}
/*
bool operator<(const Date& a, const Date& b)
{
    return a.days_since_epoch() < b.days_since_epoch();
}
*/
bool operator<=(const Date& a, const Date& b)
{
    return a.days_since_epoch() <= b.days_since_epoch();
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
    return epoch_dow + (d.days_since_epoch() % 7);
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
