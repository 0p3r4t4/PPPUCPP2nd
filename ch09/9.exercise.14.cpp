// 9.exercise.14.cpp
//
//  Design and implement a Money class for calculations involving dollars and
//  cents where arithmetric has to be accurate to the last cent using the 4/5
//  rounding rule (.5 of a cent rounds up; anything less than .5 rounds down).
//  Represent a monetary amount as a number of cents in a long int, but input
//  and output as dollars and cents, e.g., $123.45. Do not worry about amounts
//  that don't fit into a long int.
//
// COMMENTS
//
//  What operations will be implemented? Addition and substraction for sure.
//  As for multiplication and division, we must think about what type of
//  operands make sense:
//      (Money * Money)                         does not make sense to me
//      (Money * double) and (double * Money)   are perfectly legit
//      (Money / double)                        makes sense
//      (Money / Money)                         could make sense to distribute
//                                              or find ratios between amounts
//
//  As for the 4/5 rounding rule goes, only the multiplication and division
//  operators are affected (as far as only a currency is involved).
//
//  Do we want to manage negative amounts of money? It is interesting to manage
//  debts, so yes.

#include "std_lib_facilities.h"

constexpr char currency{'$'};

long int iround(double n) 
{
    return (n < 0.0) ? (n - 0.5) : (n + 0.5);
}

class Money {
public:
    class Division_by_zero { }; // custom exception

    Money(long int units, long int cents);  // constructor on units and cents
    Money(long int amount);     // constructor on number of cents
    Money();                    // default constructor, amount 0

    long int amount() const { return m_amount; };    // accessor
    
    long int units() const { return m_amount/100; }; // data retrieve
    long int cents() const { return m_amount%100; };
private:
    long int m_amount;     // amount on money on cents
};

Money::Money(long int units, long int cents) : m_amount{units*100+cents} { };
Money::Money(long int amount) : m_amount{amount} { };
Money::Money() : m_amount{0} { };

Money operator-(const Money& rhs)
{
    return Money{-rhs.amount()};
}

Money operator+(const Money& lhs, const Money& rhs)
{
    return Money{lhs.amount()+rhs.amount()};
}

Money operator-(const Money& lhs, const Money& rhs)
{
    return Money{lhs.amount()-rhs.amount()};
}

Money operator*(const Money& lhs, double rhs)
{
    return Money{ iround(lhs.amount()*rhs) };
}

Money operator*(double lhs, const Money& rhs)
{
    return Money{ iround(lhs*rhs.amount()) };
}

Money operator/(const Money& lhs, double rhs)
{
    if (rhs == 0) throw Money::Division_by_zero{};

    return Money{ iround(lhs.amount()/rhs) };
}

double operator/(const Money& lhs, const Money& rhs)
{
    if (rhs.amount() == 0) throw Money::Division_by_zero{};

    return (double(lhs.amount())/rhs.amount());
}

bool operator==(const Money& lhs, const Money& rhs)
{
    return (lhs.amount() == rhs.amount());
}

bool operator!=(const Money& lhs, const Money& rhs)
{
    return (lhs.amount() != rhs.amount());
}

ostream& operator<<(ostream& os, const Money& money)
{
    os << currency << money.units() << '.';
    if (abs(money.cents()) < 10) os << '0'; // we could need a leading 0
    os << abs(money.cents());

    return os;
}

istream& operator>>(istream& is, Money& money)
{
    long int units{0};
    char cur, dot;
    char d, u;

    is >> cur >> units >> dot >> d >> u;
    if (!is) return is;
    if (cur != currency || dot != '.' || !isdigit(d) || !isdigit(u)) {
        is.clear(ios_base::failbit);
        return is;
    }
    // if we read an integer after the dot we could find out that
    // 00000015 results to be 15. A solution will be to put back the
    // dot and read a double. This has its own set of new problems, so
    // I will read two chars and compose the cents. Pure brute force.
    int cents{(d-'0')*10+(u-'0')};

    if (units < 0) cents = -cents;  // only units have sign, but cents matter
    money = Money{(units*100)+cents};

    return is;
}

int main()
try{

    // Test Money*double, double*Money, Money/Money, Money/double, Money-Money
    // and <<
    Money budget{1000000,0};
    Money wage{1500,0};
    long int months{18};
    long int workers{ iround(budget/(wage*months)) };
    Money surplus{budget-(workers*wage*months)};
    cout << "The project's budget ascends to " << budget
         << " and it will be developed during " << months << " months.\n"
         << "Each developer get " << wage << " per month. "
         << "So we can hire " << workers << " developers.\n"
         << "The spare budget will be " << surplus << ".\n";

    cout << '\n';

    // Test Money*double, Money+Money and <<
    Money product{134,0};
    double vat = 0.21;
    Money total{product+(product*vat)};
    cout << "You have bought and paid by transference " << product
         << " for a product. But you forgot the VAT (" << vat*100
         << "%).\n" << "With VAT applied the product costs " << total
         << " so you debt " << product-total << '\n';

    cout << '\n';

    // Test and justify Money/Money
    Money after_tax{41,82};
    Money before_tax{34,56};
    double tax{(after_tax/before_tax)-1};
    cout << "A product with a final price of " << after_tax << " and a price"
         << " before taxes of " << before_tax << "\nhas been applied a "
         << tax*100 << "% of taxes (" << after_tax-before_tax << ")\n";

    cout << '\n';

    // Test >> and << operators;
    cout << "Write some quantities (examples: $123.04 or $-10.10, two digits"
         << " for cents are mandatory. Quit with Ctrl+D).\n> ";
    Money input{0};
    while (cin) {
        cin >> input;
        if (cin.eof()) break;
        if (cin.fail()) {
            cout << "Bad input format\n> ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cout << '\t' << input << "\n> ";
        }
    }

    cout << "\nBye!\n";

    // Forced errors (division by zero)
    //cout << Money{}/0;
    //cout << Money{}/Money{};
    return 0;
}
catch(Money::Division_by_zero& e)
{
    cerr << "Money class: division by zero\n";
    return 1;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 2;
}
catch(...)
{
    cerr << "Unknown exception!!\n";
    return 3;
}
