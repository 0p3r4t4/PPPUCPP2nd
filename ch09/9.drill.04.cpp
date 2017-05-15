// 9.drill.04.cpp
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
//  The version from §9.7.1 (There are changes between §9.4.3 and this that
//  must be observed):
//      - §9.4.4 Use of member initializer list in the constructor
//      - §9.4.6 Reporting errors
//
// COMMENTS
//
//  I will not do this by separating Date class, Month enumerator or helper
//  functions in their own header file. Just for the shake of simplicity.
//  This time I will create a namespace for Date and related stuff.
//
//  I will consider the Year class as an example and will not implement it
//  since it does not live up to the final version of Date.
//
//  I can't stop getting myself in trouble. As I've implemented add_day() and
//  with the introduction of Month enum class, all the operators needed to
//  manage the Month type are missing and must be overloaded. This work has to
//  be done at some point, but is sad that I will do it with such a miserable 
//  add_day() current implementation.
//
//  Date::add_day() will be implemented supposing all months have 31 days. It
//  will complicate it to do better until best tools are introduced and more
//  elaborated code is written.
//
//  In operator<< definition we declare to receive a const-by-reference Date.
//  And we call Date member functions. As stated in §9.7.4 we must make
//  explicit that those member functions do no modify the object, so we must
//  declare them as const memeber functions.

#include "std_lib_facilities.h"

namespace Chrono {

enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

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

bool operator<(const Month& m, int n) { return int(m) < n; }
bool operator>(const Month& m, int n) { return int(m) > n; }

class Date {
public:
    class Invalid {};
    Date(int yy, Month mm, int dd);
    void add_day(int n);              // increase the Date by n days
    Month month() const { return m; }
    int day() const { return d; }
    int year() const { return y; }
private:
    int y;          // year
    Month m;
    int d;          // day
    bool is_valid();
};

Date::Date(int yy, Month mm, int dd)
        :y{yy}, m{mm}, d{dd}
{
    if (!is_valid()) throw Invalid{};
}

bool Date::is_valid()
// Checks if the current state of Date object iss a valid one
{
    if (d < 1 || d > 31) return false;
    if (m < Month::jan || m > Month::dec) return false;
    return true;
}

void Date::add_day(int n)
// Function to add or substract days from a Date.
{
    // We take (31*12) as days in a year supposing every month has 31 days
    int n_d = n % 31;          // days out of months, to increase
    int n_m = (n / 31) % 12;   // months out of years, to increase
    int n_y = n / (31*12);     // years to increase

    d += n_d;
    // We must check for overflows, and n and derivatives can be negative!!
    if (d > 31) { ++n_m; d -= 31; }     // Day overflow
    if (d < 1)  { --n_m; d += 31; }     // Day underflow
 
    // Month type takes care of itself on overflows, but we loose track to 
    // modify year if it happens. We must check it before actually operate
    // on m.
    if (Month::dec < (int(m)+n_m)) ++n_y;
    if (Month::jan > (int(m)+n_m)) --n_y;
    m += n_m;   // m is of Month type
    y += n_y;
}

ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.year()
              << ',' << int(d.month())
              << ',' << d.day() << ')';
}

}; // namespace Chrono

int main()
try
{
    using Chrono::Date;
    using Chrono::Month;

    Date today{1978, Month::jun, 25};

    Date tomorrow{today};
    tomorrow.add_day(1);

    cout << "Today: " << today << '\n';
    cout << "Tomorrow: " << tomorrow << '\n';

    // Check add_day() overflow (far from perfect) detection 
    Date test{2010, Month::dec, 31};

    test.add_day(6);   // 2011 January 6th
    cout << "January the 6th 2011? " << test << '\n';
    test.add_day(-6);  // 2010 December 31st again
    cout << "December the 31st 2010? " << test << '\n';

    test = Date{2010, Month::feb, 5};
    test.add_day(-7);   // 2010 January 29th 
    cout << "January the 29th 2010? " << test << '\n';
    test.add_day(7);    // 2010 February 5th again 
    cout << "February the 5th 2010? " << test << '\n';
    test.add_day(3650);  // A year after ...
    cout << "Somewhere circa February 2020? " << test << '\n';
    test.add_day(-3650); // A year before ...
    cout << "Somewhere circa February 2010? " << test << '\n';

    // Invalid date
    Date today_e{2004, Month::dec, -5};

    return 0;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch(Chrono::Date::Invalid)
{
    cerr << "Invalid date!\n";
    return 2;
}
catch(...)
{
    cerr << "Unknown exception!!\n";
    return 3;
}
