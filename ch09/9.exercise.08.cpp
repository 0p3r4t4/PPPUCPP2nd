// 9.exercise.08.cpp
//
//  Create a Patron class for the library. The class will have a user's name,
//  library card number, and library fees (if owed). Have functions that access
//  this data, as well as a function to set the fee of the user. Have a helper
//  function that returns a Boolean (bool) depending on whether or not the user
//  owns a fee.
//
// COMMENTS

#include "std_lib_facilities.h"
#include "9.exercise.08.Chrono.h"
#include "9.exercise.08.Mylib.h"

using Chrono::Date;
using Chrono::Month;
using Mylib::Book;
using Mylib::Genre;
using Mylib::Patron;

int main()
try
{
    // Test new Genre << operator through Book << operator
    Book book{"04-6502-656-7", "Gödel, Escher, Bach: An Eternal Golden Braid",
              "Douglas Richard Hofstadter", Date{1999, Month::feb, 5},
              Genre::nonfiction};
    cout << book;
    
    // Test Patron type
    Patron patron{"John Doe", "000001"};
    cout << patron;

    // Test owes_fees() helper 
    if (owes_fees(patron)) cout << "The patron has fees!\n";
    else cout << "No fees owed.\n";

    // Test Patron::set_fees()
    patron.set_fees(100);
    cout << "With fees ...\n" << patron;
    if (owes_fees(patron)) cout << "The patron has fees!\n";
    else cout << "No fees owed.\n";

    // Provoke error on Patron::set_fees()
    try {
        patron.set_fees(-100);
    }
    catch(exception& e) {
        cerr << e.what() << '\n';
    }
    
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

