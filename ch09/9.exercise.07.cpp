// 9.exercise.07.cpp
//
//  Create an enumerated type for the Book class called Genre. Have the types
//  be fiction, nonfiction, periodical, biography, and children. Give each book
//  a Genre and make appropiate changes to the Book constructor and member
//  functions.
//
// COMMENTS

#include "std_lib_facilities.h"
#include "9.exercise.07.Chrono.h"
#include "9.exercise.07.Mylib.h"

using Chrono::Date;
using Chrono::Month;
using Mylib::Book;
using Mylib::Genre;

int main()
try
{
    // Test Book class genre member and Genre enum class
    Book book{"04-6502-656-7", "Gödel, Escher, Bach: An Eternal Golden Braid",
              "Douglas Richard Hofstadter", Date{1999, Month::feb, 5},
              Genre::nonfiction};
    cout << book;
    
    book = Book{"07-5640-474-6", "The Name of the Wind", "Patrick Rothfuss",
                Date{2008, Month::apr, 1}, Genre::fiction};
    cout << book;
    
    book = Book{"17-8370-423-3", "The Colour Monster", "Anna Llenas",
              Date{2016, Month::mar, 1}, Genre::children};
    cout << book;

    book = Book{"16-0010-483-5", "Lock and Key, Vol 2: Head Games", 
                "Joe Hill and Gabriel Rodriguez", Date{2009, Month::sep, 29},
                Genre::periodical};
    cout << book;

    book = Book{"03-4552-612-0", "Jim Henson: The Biography", "Brian Jay Jones",
                Date{2016, Month::may, 10}, Genre::biography};
    cout << book;
    
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

