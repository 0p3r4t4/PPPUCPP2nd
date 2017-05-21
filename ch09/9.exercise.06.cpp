// 9.exercise.06.cpp
//
// Add operators for the Book class. Have the == operator check whether the
// ISBN numbers are the same for two books. Have != also compare the ISBN
// numbers. Have a << print out the title, author, and ISBN on separate lines.
//
// COMMENTS
//
//  I assume that for comparision only ISBN matters.

#include "std_lib_facilities.h"
#include "9.exercise.06.Chrono.h"
#include "9.exercise.06.Mylib.h"

using Chrono::Date;
using Chrono::Month;
using Mylib::Book;

int main()
try
{
    // Test Book class new operators
    Book book{"04-6502-656-7", "Gödel, Escher, Bach: An Eternal Golden Braid",
              "Douglas Richard Hofstadter", Date{1999, Month::feb, 5}};
    cout << book;
    
    Book b1{"16-8050-127-5",
                "Practical Vim: Edit at the Speed of Thought, 2nd Edition",
                "Drew Neil", Date{2015, Month::nov, 7}};
    Book b2{"16-8050-127-5",
                "Practical Vim: Edit at the Speed of Thought",
                "Drew Neil", Date{2015, Month::nov, 7}};

    if (b1 == b2) cout << '\n' << b1 
                       << "\n-- is THE SAME book as --\n\n"
                       << b2 << '\n';
    cout << "----------------------\n";
    if (book != b2) cout << '\n' << book 
                         << "\n-- is NOT THE SAME book as --\n\n" 
                         << b2 << '\n';

    return 0;
}
catch(Chrono::Date::Invalid& e)
{
    cerr << "Invalid date!\n";
    return 1;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 2;
}
catch(...)
{
    cerr << "Unknown exception!\n";
    return 3;
}

