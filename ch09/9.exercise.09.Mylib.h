// 9.exercise.09.Mylib.h
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
//
//  I wasn't happy with the "naming convention" used in the previous exercises.
//  I guess that private data members of Date make sense being y, m and d.
//  Their meainig is clear in that case. But translating that to Mylib classes
//  feel poorer. The problem is that data members could not be named as
//  member functions to retrieve their values. Searching on the web, there is
//  no consense, but some ideas. I don't really like the get/set syntax. I also
//  think that postfix the data members with _ is error prone. I don't like it
//  either, but I think is a better option to prefix data members with m_, so
//  until I found or think about a better approximation I will stick with this.
//
//  Library::print_*() are implemented for testing.
//  Library::check_out() is done under the assumption that te book is
//  identified by ISBN and de patron is by card number.
//
//  Checking if a book is on the library or if it's available doesn't consider
//  that it can be more than one specimen of the same. Must we force uniqueness
//  of books and patrons? It will be more correct than permit multiple
//  instances or repeated users and not consider it. So add_book() and
//  add_patron() must enforce uniqueness. Private member functions
//  is_patron() and is_book() will come in handy for this and for check_out().

#include "std_lib_facilities.h"
#include "9.exercise.09.Chrono.h"

#ifndef MYLIB_H
#define MYLIB_H

namespace Mylib {

class Invalid_ISBN { };  // to throw in case ISBN is not valid
class Repeated_ISBN { };  // to throw in case ISBN is repeated
class Invalid_Card_Number { }; // to throw in case invalid card number
class Repeated_Card_Number { }; // to throw in case card number is repeated
class Book_Checked_Out { }; // to throw in case a book is already checked out

enum class Genre {
    fiction, nonfiction, periodical, biography, children
};

// Genre operators
ostream& operator<<(ostream& os, Genre g);

class Book {
public:
    Book(string isbn, string title, string author, Chrono::Date copyright,
         Genre genre);

    // modifying function members
    void check_out() { m_checked_out = true; }
    void check_in() { m_checked_out = false; }

    // non-modifying function members
    const string& isbn() const { return m_isbn; }
    const string& title() const { return m_title; }
    const string& author() const { return m_author; }
    const Chrono::Date& copyright() const { return m_copyright; }
    const Genre genre() const { return m_genre; }
    const bool checked_out() const { return m_checked_out; }
private:
    string m_isbn;
    string m_title;
    string m_author;
    Chrono::Date m_copyright;
    Genre m_genre;
    bool m_checked_out;
};

// Book helper functions
bool is_isbn(const string& isbn);
void print(ostream& os, const Book& b);

// Book operators
bool operator==(const Book& a, const Book& b);
bool operator!=(const Book& a, const Book& b);
ostream& operator<<(ostream& os, const Book& b);

class Patron {
public:
    Patron(string name, string card_number);

    // modifying function members
    void set_fees(double fees);

    // non-modifying function members
    const string& name() const { return m_name; }
    const string& card_number() const { return m_card_number; }
    const double fees() const { return m_fees; }
private:
    string m_name;
    string m_card_number;
    double m_fees;
};

// Patron helper functions
bool owes_fees(const Patron& p);

// Patron operators
ostream& operator<<(ostream& os, const Patron& p);

struct Transaction {
    Book book;
    Patron patron;
    Chrono::Date date;
};

// Transaction operators
ostream& operator<<(ostream& os, const Transaction& t);

class Library {
public:
    void add_book(Book b);
    void add_patron(Patron p);
    void check_out(string& card_number, string& isbn, Chrono::Date& date);

    // Reports
    vector<string> users_with_fees() const; // Return names of users
                                            // that owes fees
    void print_books(ostream& os) const;
    void print_patrons(ostream& os) const;
    void print_transactions(ostream& os) const;
private:
    bool is_book(const string& isbn); // tell if a book is already on the library
    bool book_in(const string& isbn); // tell if a book is checked in
    bool is_patron(const string& card_number); // tell if a patron already exists
    vector<Book> m_book;
    vector<Patron> m_patron;
    vector<Transaction> m_transaction;
};

} // namespace Mylib

#endif
