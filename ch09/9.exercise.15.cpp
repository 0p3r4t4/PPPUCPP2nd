// 9.exercise.15.cpp
//
//  Refine the Money class by adding a currency (given as a constructor
//  argument). Accept a floating-point initializer as long as it can be exactly
//  represented as a long int. Don't accept illegal operations. For example,
//  Money*Money doesn't make sense, and USD1.23+DKK5.00 makes sense only if you
//  provide a conversion table defining the conversion factor between U.S.
//  dollars (USD) and Danish kroner (DKK).
//
// COMMENTS
//

#include "std_lib_facilities.h"

constexpr char currency{'$'};   // To be deleted

enum class Currency {
    USD, ARS, DKK, EUR, GBP
};

class Currency_data { 
public:
    class Invalid_currency { };     // Exception
    struct row {
        Currency id;
        string name;
        double ratio;   // to dollars
    };

    Currency_data();       // custom default constructor

    Currency currency(const string& acronym) const;  // get currency by name
    string acronym(Currency currency) const;         // get name by id
    double ratio(Currency currency) const;           // get ratio to US dollars
    double ratio(Currency a, Currency b) const;      // get conversion ratio

    void print();      // Test function
private:
    vector<row> data;
};

Currency_data::Currency_data()
{
    // Currency convert factors as 2017/06/04
    data.push_back(row{Currency::USD, "USD", 1.0});       // US Dollar
    data.push_back(row{Currency::ARS, "ARS", 0.06236});   // Argentine Peso
    data.push_back(row{Currency::DKK, "DKK", 0.15164});   // Danish Krone
    data.push_back(row{Currency::EUR, "EUR", 1.12798});   // Euro
    data.push_back(row{Currency::GBP, "GBP", 1.28841});      // British Pound
}

void Currency_data::print()
{
    for (auto x : data)
        cout << int(x.id) << ' ' << x.name << ' ' << x.ratio << '\n';
}

Currency_data currency_table{};

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

    long int amount() const { return m_amount; };    // accessors
    Currency currency() const { return m_currency; }
    
    long int units() const { return m_amount/100; }; // data retrieve
    long int cents() const { return m_amount%100; };
private:
    long int m_amount;     // amount on money on cents
    Currency m_currency;
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
    currency_table.print();

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
