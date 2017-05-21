// 9.exercise.05.cpp
//
// This exercise and the next few require you to design and implement a Book
// class, such as you can imagine as part of software for a library. Class Book
// should have members for the ISBN, title, author, and copyright date. Also
// store data on whether or not the book is checked out. Create functions for
// returning those data values. Create functions for checking a book in and
// out. Do simple validation of data entered into a Book; for example, accept
// ISBN only of the form n-n-n-x where n is an integer and x is a digit or a
// letter. Store an ISBN as a string.
//
// COMMENTS
//
//  I will implement Book class in its own namespace (Mylib, poor named) and
//  the namespace in its own header a code files.
//
//  Since we need a Date I will borrow it from §9.8 and additions from 
//  9.drill.05.cpp and take the Chrono namespace to its own files.
//  The functionality from Date is barely used here, so I will not check it
//  thoroughly and trust previous work and book corectness. 
//
//  Chrono header is included several times so I have to introduce include
//  guards with #ifndef/#define macros. This is not yet introduced, but needed.
//
//  I put using declarations only for main user defined types. Helper functions
//  and exception classes are invoked fully qualified. Is this bad style?
//  Perhaps.

#include "std_lib_facilities.h"
#include "9.exercise.05.Chrono.h"
#include "9.exercise.05.Mylib.h"

using Chrono::Date;
using Chrono::Month;
using Mylib::Book;

int main()
try
{
    // Test Mylib::is_isbn() function
    string s{};
    string isbn{};

    isbn = "2342-2342-2344-A";
    s = Mylib::is_isbn(isbn) ? "" : "not ";
    cout << isbn << " is " << s << "a valid ISBN\n";
    isbn = "04-6502-656-7";
    s = Mylib::is_isbn(isbn) ? "" : "not ";
    cout << isbn << " is " << s << "a valid ISBN\n";
    isbn = "aoiefoawinefna";
    s = Mylib::is_isbn(isbn) ? "" : "not ";
    cout << isbn << " is " << s << "a valid ISBN\n";
    isbn = "2342-2342-2344-AAA";
    s = Mylib::is_isbn(isbn) ? "" : "not ";
    cout << isbn << " is " << s << "a valid ISBN\n";
    isbn = "2342-2342--A";
    s = Mylib::is_isbn(isbn) ? "" : "not ";
    cout << isbn << " is " << s << "a valid ISBN\n";
    isbn = "-2345/234-23-23-2";
    s = Mylib::is_isbn(isbn) ? "" : "not ";
    cout << isbn << " is " << s << "a valid ISBN\n";
    cout << '\n';

    // Test Book class
    Book book{"04-6502-656-7", "Gödel, Escher, Bach: An Eternal Golden Braid",
              "Douglas Richard Hofstadter", Date{1999, Month::feb, 5}};
    Mylib::print(cout, book);
    book = Book{"07-5640-474-6", "The Name of the Wind", "Patrick Rothfuss",
                Date{2008, Month::apr, 1}};
    book.check_out();
    Mylib::print(cout, book);
    book = Book{"16-8050-127-5",
                "Practical Vim: Edit at the Speed of Thought, 2nd Edition",
                "Drew Neil", Date{2015, Month::nov, 7}};
    book.check_out();
    book.check_in();
    Mylib::print(cout, book);
    try {
        book = Book{"???", "Necronomicon", "Abdul Alhazred",
                    Date{768, Month::jan, 1}};
    }
    catch(Mylib::Invalid_ISBN& e) {
        cerr << "Invalid ISBN!\n";
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

