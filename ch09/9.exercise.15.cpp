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
//  So, how to manage data referred to currencies and exchange ratios? What I
//  want to prioritize is ease of maintenance, so the needed data extends the
//  fewer places the best. And I really don't know how to conciliate this with
//  good practices and with we have learned from the book so far.
//
//  My approach is to encapsulate the data inside a class, Currency_data, that
//  admits no further changes; every function member is const and private data
//  member is const and static. We have read about static, but no so in depth.
//  I just go through compiler error and warnigns to get there.
//
//  The way to use this class is to create a global object. Not very elegant,
//  but has been done earlier on the calculator. We need that object primarily
//  for operator overloads on Money and there is no pass-by way to carry that
//  object into the operator functions.
//
//  You can argue me as much as you want and you'll have part of reason.
//  Another way to do this, given the constness and staticness of
//  Currency_data, is to create a member of that type in Money. The data will
//  not be duplicated and it's efficient. But it feels more convoluted to me;
//  Money class has no need for this data, only the helper functions do, so I
//  don't see why Money would have to host a Currency_data member.
//  Other way is to hardcode the currency data on as many functions as we need.
//  But this goes against ease of maintenance, and we will face lengthy
//  switch-case-statements before we add a bunch of currencies to the program.
//
//  
//  I will take currency rates to USD and calculate the rest if needed. Of
//  course currency conversion it's not so easy, and it will not be precise.
//  Rates are not the same if you are buying or selling. Rates also differ
//  (there no exact arithmetic relationship) if you are trading EUR to USD or
//  USD to EUR. So I'll simplify based on rates from currencies to USD. We
//  could expand Currency_data to treat these differences if we want to.

#include "std_lib_facilities.h"

namespace Financial {

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

    Currency currency(const string& name) const;     // get currency by name
    const string& name(Currency currency) const;     // get name by id
    double ratio(Currency currency) const;           // get ratio to US dollars
    double ratio(Currency a, Currency b) const;      // get conversion ratio

    void print() const;      // Test function
private:
    static const vector<row> data;
};

// Definition of Currency_data::data outside the class
const vector<Currency_data::row> Currency_data::data {
    row{Currency::USD, "USD", 1.0},       // US Dollar
    row{Currency::ARS, "ARS", 0.06236},   // Argentine Peso
    row{Currency::DKK, "DKK", 0.15164},   // Danish Krone
    row{Currency::EUR, "EUR", 1.12798},   // Euro
    row{Currency::GBP, "GBP", 1.28841}    // British Pound
};

// Global currency data provider
const Currency_data currency_data{};

// Currency_data function members
void Currency_data::print() const
{
    for (auto x : data)
        cout << int(x.id) << ' ' << x.name << ' ' << x.ratio << '\n';
}

Currency Currency_data::currency(const string& name) const
{
    for (const row& r : data)
        if (r.name == name) return r.id;

    throw Invalid_currency{};
}

const string& Currency_data::name(Currency currency) const
{
    for (const row& r : data)
        if (r.id == currency) return r.name;

    throw Invalid_currency{};
}

double Currency_data::ratio(Currency currency) const
{
    for (const row& r : data)
        if (r.id == currency) return r.ratio;

    throw Invalid_currency{};
}

double Currency_data::ratio(Currency a, Currency b) const
{
    if (a == b) return 1.0;     // same currency

    double ratio_a{currency_data.ratio(a)};
    double ratio_b{currency_data.ratio(b)};

    return (ratio_a/ratio_b);   // Since USD has a ratio 1.0, this formula
                                // works fine for all cases.
}

// Global helper funcion
long int iround(double n) 
{
    return (n < 0.0) ? (n - 0.5) : (n + 0.5);
}

class Money {
public:
    class Division_by_zero { }; // custom exception
    class Invalid_amount { };   // Basically float point constructor does not
                                // preserve amount argument

    // constructor on units and cents
    Money(long int units, long int cents, Currency currency);
    // constructor on number of cents
    Money(long int amount, Currency currency);    
    // constructor on floating point
    Money(double amount, Currency currency);
    // default constructor, amount 0, currency Currency::USD
    Money();                  

    long int amount() const { return m_amount; };    // accessors
    Currency currency() const { return m_currency; }
    
    long int units() const { return m_amount/100; }; // data retrieve
    long int cents() const { return m_amount%100; };
private:
    long int m_amount;     // amount on money on cents
    Currency m_currency;
};

// Money constructors
Money::Money(long int units, long int cents, Currency currency)
: m_amount{units*100+cents}, m_currency{currency} { };

Money::Money(long int amount, Currency currency)
: m_amount{amount}, m_currency{currency} { };

Money::Money(double amount, Currency currency)
: m_amount{int(amount*100)}, m_currency{currency}
{
    if (double(m_amount) != (amount*100)) throw Invalid_amount{};
}

Money::Money() : m_amount{0}, m_currency{Currency::USD} { };

// Money operators
Money operator-(const Money& rhs)
{
    return Money{-rhs.amount()};
}

Money operator+(const Money& lhs, const Money& rhs)
{
    return Money{lhs.amount()+rhs.amount(), lhs.currency()};
}

Money operator-(const Money& lhs, const Money& rhs)
{
    return Money{lhs.amount()-rhs.amount(), lhs.currency()};
}

Money operator*(const Money& lhs, double rhs)
{
    return Money{iround(lhs.amount()*rhs), lhs.currency()};
}

Money operator*(double lhs, const Money& rhs)
{
    return Money{iround(lhs*rhs.amount()), rhs.currency()};
}

Money operator/(const Money& lhs, double rhs)
{
    if (rhs == 0) throw Money::Division_by_zero{};

    return Money{ iround(lhs.amount()/rhs), lhs.currency()};
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
    money = Money{(units*100)+cents, Currency::USD};

    return is;
}

}; // namespace Financial

using namespace Financial;

int main()
try{

    currency_data.print(); // Silly test. REMOVE IT. Or not.

    // Currency_data::ratio() test
    cout << "USD -> USD - " << currency_data.ratio(Currency::USD, Currency::USD) << '\n';
    cout << "USD -> EUR - " << currency_data.ratio(Currency::USD, Currency::EUR) << '\n';
    cout << "USD -> DKK - " << currency_data.ratio(Currency::USD, Currency::DKK) << '\n';
    cout << "USD -> GBP - " << currency_data.ratio(Currency::USD, Currency::GBP) << '\n';
    cout << "USD -> ARS - " << currency_data.ratio(Currency::USD, Currency::ARS) << '\n';
    cout << "EUR -> GBP - " << currency_data.ratio(Currency::EUR, Currency::GBP) << '\n';
    cout << "GBP -> EUR - " << currency_data.ratio(Currency::GBP, Currency::EUR) << '\n';
    cout << "EUR -> ARS - " << currency_data.ratio(Currency::EUR, Currency::ARS) << '\n';

    // Test Money*double, double*Money, Money/Money, Money/double, Money-Money
    // and <<
    Money budget{1000000,0,Currency::USD};
    Money wage{1500,0,Currency::USD};
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
    Money product{134,0,Currency::USD};
    double vat = 0.21;
    Money total{product+(product*vat)};
    cout << "You have bought and paid by transference " << product
         << " for a product. But you forgot the VAT (" << vat*100
         << "%).\n" << "With VAT applied the product costs " << total
         << " so you debt " << product-total << '\n';

    cout << '\n';

    // Test and justify Money/Money
    Money after_tax{41,82,Currency::USD};
    Money before_tax{34,56,Currency::USD};
    double tax{(after_tax/before_tax)-1};
    cout << "A product with a final price of " << after_tax << " and a price"
         << " before taxes of " << before_tax << "\nhas been applied a "
         << tax*100 << "% of taxes (" << after_tax-before_tax << ")\n";

    cout << '\n';

    // Test >> and << operators;
    cout << "Write some quantities (examples: $123.04 or $-10.10, two digits"
         << " for cents are mandatory. Quit with Ctrl+D).\n> ";
    Money input{0,Currency::USD};
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
catch(Money::Invalid_amount& e)
{
    cerr << "Money class: invalid amount\n";
    return 2;
}
catch(Currency_data::Invalid_currency& e)
{
    cerr << "Currancy_data class: invalid currency\n";
    return 3;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 4;
}
catch(...)
{
    cerr << "Unknown exception!!\n";
    return 5;
}
