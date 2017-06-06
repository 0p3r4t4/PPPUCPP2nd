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
//  So, how to manage data referred to currencies and exchange rates? What I
//  want to prioritize is ease of maintenance so the needed data extends the
//  fewer places the best. And I really don't know how to conciliate this with
//  good practices and with we have learned from the book so far.
//
//  My approach is to encapsulate the data inside a class, Currency_data, that
//  admits no further changes; every function member is const and private data
//  member is const and static. We have read about static, but no so in depth.
//  I just go through compiler errors and warnigns to get there.
//
//  The way to use this class is to create a global object. Not very elegant
//  but has been done earlier on the calculator. We need that object primarily
//  for operator overloads on Money and there is no pass-by way to carry that
//  object into the operator functions.
//
//  You can argue me as much as you want and you'll have part of reason.
//  Another way to do this, given the constness and staticness of
//  Currency_data, is to create a member of that type in Money. The data will
//  not be duplicated and it's storage efficient. But it feels more convoluted
//  to me; Money class has no need for this data, only the helper functions do,
//  so I don't see why Money would have to host a Currency_data member.  Other
//  way is to hardcode the currency data on as many functions as we need.  But
//  this goes against ease of maintenance, and we will face lengthy
//  switch-case-statements before we add a bunch of currencies to the program.
//  
//  I will take currency rates to USD and calculate the rest if needed. Of
//  course currency conversion is not so easy, and it won't be precise.  Rates
//  are not the same if you are buying or selling. Rates also differ (there is
//  no exact arithmetic relationship) if you are trading EUR to USD or USD to
//  EUR. So I'll simplify based on rates from currencies to USD. We could
//  expand Currency_data to treat these differences if we want to.
//
//  When I add the constructor Money(double, Currency) without removing the
//  constructor Money(long int, Currency) and try to create an object with
//  something like Money{0, Currency::USD}, compiler complains about an
//  ambiguous call. The thing is that 0 is an int, and between the two
//  candidates, it must be converted or promoted, so no one is better than the
//  other.  The solution is to suffix the integer literal to mark int as a long
//  int, so Money{0L, Currency::USD} will disambiguate. C++ is turning
//  difficult by moments.
//  We could argue if we need the former constructor with long int now that we
//  have a constructor with double that will simplify the >> operator overload
//  on Money.
//
//  Exercise tell us to implement a floating-point initializer "as long as it
//  can be exactly represented as a long int". Luckily I tested 4.56 on input,
//  and discover that it isn't representable by double type (is represented as
//  4.5599999999999994). I will not handle this because of the exercise
//  statement, but to solve it some iround() or round() must be employed and
//  operator>>(Money) reviewed.
//
//  Now, with currency exchange rates being doubles and applied on all
//  arithmetic operators for Money, rounding is needed almost everywhere.

#include "std_lib_facilities.h"

namespace Financial {

// wide scope helper funcion
long int iround(double n) 
{
    return (n < 0.0) ? (n - 0.5) : (n + 0.5);
}

// Currency enum class
enum class Currency {
   USD, ARS, DKK, EUR, GBP
};

// Currency_data class
class Currency_data { 
public:
    class Invalid_currency { };  // Exception
    struct row {
        Currency id;
        string name;             // i.e. "GBP"
        string long_name;        // i.e. "British Pounds"
        double ratio;            // to US Dollars
    };

    Currency currency(const string& name) const;      // get currency by name
    const string& name(Currency currency) const;      // get name by id
    const string& long_name(Currency currency) const; // get long name by id
    double ratio(Currency currency) const;            // get ratio to US dollars
    double ratio(Currency a, Currency b) const;       // get conversion ratio
    
    void info() const;  // print information about currencies suportted

private:
    static const vector<row> data;
};

// Definition of static const Currency_data::data must be outside the class
const vector<Currency_data::row> Currency_data::data {
    row{Currency::USD, "USD", "US Dollar",      1.0},
    row{Currency::ARS, "ARS", "Argentine Peso", 0.06236},
    row{Currency::DKK, "DKK", "Danish Krone",   0.15164},
    row{Currency::EUR, "EUR", "Euro",           1.12798},
    row{Currency::GBP, "GBP", "British Pound",  1.28841}
};

// Global currency data provider
const Currency_data currency_data{};

// Currency operators (need currency_data)
ostream& operator<<(ostream& os, const Currency currency)
{
    os << currency_data.name(currency);
    return os;
}

istream& operator>>(istream& is, Currency& currency)
{
    char c;
    string name;
    // assume currency name has always three chars
    // beware the magic number!
    for (int i = 0; i < 3; ++i) {
        is >> c;
        if (!is) return is;  // in case of EOF
        name += c;
    }

    try {
        currency = currency_data.currency(name);  // may throw
    }
    catch(Currency_data::Invalid_currency& e) {
        is.clear(ios_base::failbit);
    }

    return is;
}

// Currency_data function members
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

const string& Currency_data::long_name(Currency currency) const
{
    for (const row& r : data)
        if (r.id == currency) return r.long_name;

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

void Currency_data::info() const
{
    for (const row& r: data)
        cout << r.name << " (" << r.long_name << ")\n";
}

// Money class
class Money {
public:
    class Division_by_zero { }; // custom exception
    class Invalid_amount { };   // basically float point constructor does not
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
: m_amount{(long int)(amount*100)}, m_currency{currency}
{
    if (double(m_amount) != (amount*100)) throw Invalid_amount{};
}

Money::Money() : m_amount{0}, m_currency{Currency::USD} { };

// Money operators
Money operator-(const Money& rhs)
{
    return Money{-rhs.amount(), rhs.currency()};
}

Money operator+(const Money& lhs, const Money& rhs)
{
    // avoid unreadable one-liner
    double ratio{currency_data.ratio(rhs.currency(), lhs.currency())};
    return Money{iround(lhs.amount()+(rhs.amount()*ratio)), lhs.currency()};
}

Money operator-(const Money& lhs, const Money& rhs)
{
    double ratio{currency_data.ratio(rhs.currency(), lhs.currency())};
    return Money{iround(lhs.amount()-(rhs.amount()*ratio)), lhs.currency()};
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

    double ratio{currency_data.ratio(rhs.currency(), lhs.currency())};
    return (double(lhs.amount())/(rhs.amount()*ratio));
}

bool operator==(const Money& lhs, const Money& rhs)
{
    double ratio{currency_data.ratio(rhs.currency(), lhs.currency())};
    return (lhs.amount() == iround(rhs.amount()*ratio));
}

bool operator!=(const Money& lhs, const Money& rhs)
{
    double ratio{currency_data.ratio(rhs.currency(), lhs.currency())};
    return (lhs.amount() != iround(rhs.amount()*ratio));
}

ostream& operator<<(ostream& os, const Money& money)
{
    os << money.currency() << money.units() << '.';
    if (abs(money.cents()) < 10) os << '0';  // we could need a leading 0
    os << abs(money.cents());

    return os;
}

istream& operator>>(istream& is, Money& money)
{
    double amount{0};
    Currency currency{Currency::USD};

    is >> currency;
    if (!is) return is;
    is >> amount;
    if (!is) return is;

    try {
        money = Money{amount, currency};  // may throw
    }
    catch(Money::Invalid_amount& e) {
        is.clear(ios_base::failbit);
    }

    return is;
}

}; // namespace Financial

using namespace Financial;

int main()
try{
    // Currency_data::ratio() test
    cout << "USD -> USD - " << currency_data.ratio(Currency::USD, Currency::USD) << '\n';
    cout << "USD -> EUR - " << currency_data.ratio(Currency::USD, Currency::EUR) << '\n';
    cout << "USD -> DKK - " << currency_data.ratio(Currency::USD, Currency::DKK) << '\n';
    cout << "USD -> GBP - " << currency_data.ratio(Currency::USD, Currency::GBP) << '\n';
    cout << "USD -> ARS - " << currency_data.ratio(Currency::USD, Currency::ARS) << '\n';
    cout << "EUR -> GBP - " << currency_data.ratio(Currency::EUR, Currency::GBP) << '\n';
    cout << "GBP -> EUR - " << currency_data.ratio(Currency::GBP, Currency::EUR) << '\n';
    cout << "EUR -> ARS - " << currency_data.ratio(Currency::EUR, Currency::ARS) << '\n';

    cout << '\n';

    // Test operators for distinct currencies
    Money usd{1000.00, Currency::USD};
    Money eur{1000.00, Currency::EUR};
    Money gbp{1000.00, Currency::GBP};
    Money ars{1000.00, Currency::ARS};
    Money dkk{1000.00, Currency::DKK};
    Money dkk_usd{
        iround(usd.amount()*currency_data.ratio(Currency::USD, Currency::DKK)),
        Currency::DKK
    };
    cout <<"-" << eur << " = " << -eur << '\n';
    cout << eur << " + " << gbp << " = " << eur+gbp << '\n';
    cout << usd << " - " << gbp << " = " << usd-gbp << '\n';
    cout << dkk << " * " << 25 << " = " << dkk*25 << '\n';
    cout << 25 << " * " << ars << " = " << 25*ars << '\n';
    cout << ars << " / " << 10 << " = " << ars/10 << '\n';
    cout << usd << " / " << dkk << " = " << usd/dkk << '\n';
    if (usd == dkk_usd) cout << usd << " == " << dkk_usd << '\n';
    if (usd != gbp) cout << usd << " != " << gbp << '\n'; 

    cout << '\n';

    // Test Money*double, double*Money, Money/Money, Money/double, Money-Money
    // and <<
    Money budget{1000000,0,Currency::USD};
    Money wage{9908,35,Currency::DKK};
    long int months{18};
    long int workers{ iround(budget/(wage*months)) };
    Money surplus{budget-(workers*wage*months)};    // No currency: copy constructor?
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
    cout << "Write some quantities. Examples: EUR23.04 or GBP-10.\n"
         << "Quit with Ctrl+D. Supported currenies are:\n\n";
    currency_data.info();
    cout << "\n> ";
    Money input{12.01,Currency::USD};
    while (cin) {
        cin >> input;
        if (cin.eof()) break;
        if (cin.fail()) {
            cout << "Bad input format\n> ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            double ratio = currency_data.ratio(input.currency(), Currency::EUR);
            cout << '\t' << input << "  ("
                 << Money{iround(input.amount()*ratio), Currency::EUR}
                 << ")\n> ";
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
