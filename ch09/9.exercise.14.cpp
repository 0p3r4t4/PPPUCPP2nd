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
//      (Money * Money)                     does not make sense to me
//      (Money * int) and (int * Money)     are perfectly legit
//      (Money / int)                       makes sense
//      (Money / Money)                     could make sense to distribute
//
//  As for the 4/5 rounding rule goes, only the division operator is affected
//  (as far as only a currency is involved).
//
//  Do we want to manage negative amounts of money? It is interesting to manage
//  debts, so yes.

#include "std_lib_facilities.h"

constexpr char currency{'$'};

class Money {
public:
    Money(long int amount);     // constructor on number of cents
    Money();                    // default constructor, amount 0

    long int amount() const { return m_amount; };    // accessor
private:
    long int m_amount;     // amount on money on cents
};

Money::Money(long int amount) : m_amount{amount} { };
Money::Money() : m_amount{0} { };

Money operator-(const Money& m)
{
    return(Money{-m.amount()});
}

Money operator+(const Money& lhs, const Money& rhs)
{
    return(Money{lhs.amount()+rhs.amount()});
}

Money operator-(const Money& lhs, const Money& rhs)
{
    return(Money{lhs.amount()-rhs.amount()});
}

Money operator*(const Money& lhs, long int rhs)
{
    return(Money{lhs.amount()*rhs});
}

Money operator*(long int lhs, const Money& rhs)
{
    return(Money{lhs*rhs.amount()});
}

Money operator/(const Money& lhs, long int rhs)
{
    return(Money{lhs.amount()/rhs});
    // TODO: Rounding
}

long int operator/(const Money& lhs, const Money& rhs)
// Times of money distribution
{
    return(lhs.amount()/rhs.amount());
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
    os << currency << money.amount()/100 << '.';

    long int cents{money.amount()%100};
    if (cents < 10) os << '0'; // we could need a leading 0
    os << cents;

    return os;
}

istream& operator>>(istream& is, Money& money)
{
    long int units, cents;
    char cur, dot;

    is >> cur >> units >> dot >> cents;
    if (!is) return is;
    if (units != currency || dot != '.') {
        is.clear(ios_base::failbit);
        return is;
    }

    money = Money{};
}

int main()
try{

    // Test Money*int, int*Money, Money/Money, Money/int, Money-Money and <<
    Money budget{1000000*100};
    Money wage{1500*100};
    long int months{18};
    long int workers{budget/(wage*months)};
    Money surplus{budget-(workers*wage*months)};
    cout << "The project's budget ascends to " << budget
         << " and it will be developed during " << months << " months.\n"
         << "Each developer get " << wage << " per month. "
         << "So we can hire " << workers << " developers.\n"
         << "The spare budget will be " << surplus << ".\n";

    return 0;
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
