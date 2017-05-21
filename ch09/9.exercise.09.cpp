// 9.exercise.09.cpp
//
//  Create a Library class. Include vectors of Books and Patrons. Include a
//  struct called Transaction. Have it include a Book, a Patron, and a Date
//  from the chapter. Make a vector of Transactions. Create functions to add
//  books to the library, add patrons to the library, and check out books.
//  Whenever a user checks out a book, have the library make sure that both the
//  user and the book are in the library. If they aren't, report an error. Then
//  check to make sure that the user owes no fees. If the user does report an
//  error. If not, create a Transaction, and place it in the vector of
//  Transactions. Also write a function that will return a vector that contains
//  the names of all Patrons who owe fees.
//
// COMMENTS

#include "std_lib_facilities.h"
#include "9.exercise.09.Chrono.h"
#include "9.exercise.09.Mylib.h"

using Mylib::Book;
using Mylib::Genre;
using Mylib::Patron;
using Mylib::Transaction;
using Mylib::Library;

void add_book(Library& l, Book b)
{
    try {
        l.add_book(b);
    }
    catch(Mylib::Repeated_ISBN& e) {
        cerr << "Repeated ISBN " << b.isbn() << " for \""
             << b.title() <<"\"!!!\n";
    }
}

void init_books(Library& l)
{
    add_book(l, Book{"04-6502-656-7",
                    "Gödel, Escher, Bach: An Eternal Golden Braid",
                    "Douglas Richard Hofstadter", 
                    Chrono::Date{1999, Chrono::Month::feb, 5},
                    Genre::nonfiction});
    
    add_book(l, Book{"07-5640-474-6",
                    "The Name of the Wind",
                    "Patrick Rothfuss",
                    Chrono::Date{2008, Chrono::Month::apr, 1},
                    Genre::fiction});
    
    add_book(l, Book{"17-8370-423-3",
                    "The Colour Monster",
                    "Anna Llenas",
                    Chrono::Date{2016, Chrono::Month::mar, 1},
                    Genre::children});

    add_book(l, Book{"16-0010-483-5",
                    "Lock and Key, Vol 2: Head Games", 
                    "Joe Hill and Gabriel Rodriguez",
                    Chrono::Date{2009, Chrono::Month::sep, 29},
                    Genre::periodical});

    add_book(l, Book{"03-4552-612-0",
                    "Jim Henson: The Biography",
                    "Brian Jay Jones",
                    Chrono::Date{2016, Chrono::Month::may, 10},
                    Genre::biography});
    // Error, repeated ISBN
    add_book(l, Book{"03-4552-612-0",
                    "Jim Henson: The Biography",
                    "Brian Jay Jones",
                    Chrono::Date{2016, Chrono::Month::may, 10},
                    Genre::biography});
}

void add_patron(Library& l, Patron p)
{
    try {
        l.add_patron(p);
    }
    catch(Mylib::Repeated_Card_Number& e) {
        cerr << "Repeated Card Number " << p.card_number() << " for patron "
             << p.name() << "!!!\n";
    }
}

void init_patrons(Library& l)
{
    add_patron(l, Patron{"John Doe", "0000001"});
    add_patron(l, Patron{"Peter Pan", "000032"});
    add_patron(l, Patron{"Bobby Fisher", "000053"});
    add_patron(l, Patron{"Max Rockatansky", "000104"});
    add_patron(l, Patron{"Ivan Drago", "000156"});
    // Error, repeated card number
    add_patron(l, Patron{"Bobby Fisher", "000053"});
}

int main()
try
{
    Library mylib;

    init_books(mylib);
    init_patrons(mylib);
    
    cout << "\nLIBRARY BOOKS ===\n\n";
    mylib.print_books(cout);
    cout << "\nLIBRARY PATRONS ===\n\n";
    mylib.print_patrons(cout);

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

