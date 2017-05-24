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
//
//  Checking if a book is on the library or if it's available doesn't consider
//  that it can be more than one specimen of the same. Must we force uniqueness
//  of books and patrons? It will be more correct than permit multiple
//  instances or repeated users and not consider it. So add_book() and
//  add_patron() must enforce uniqueness. Private member functions
//  is_patron() and is_book() will come in handy for this and for check_out().
//
//  We need Patron == operator. As we implemented == operator for books based
//  solely on ISBN, the Patron == will be based on comparison between
//  card numbers.
//
//  When checking out we're receving objects to compare with those stored,
//  parsistently, in Library::m_patron and Library::m_book. When we're ready to
//  check out a book, we must call Book::check_out() function on the book,
//  not the one received by Library::check_out() but the persistent one. So I
//  added Library::book() and Library::patron() that return references to the
//  persistent element (from Library::m_book and Library::m_patron,
//  respectively) that equals the argument provided.

#include "std_lib_facilities.h"
#include "9.exercise.09.Chrono.h"

#ifndef MYLIB_H
#define MYLIB_H

namespace Mylib {

class Invalid_ISBN { };  // to throw in case ISBN is not valid
class Invalid_Book { };  // a book does not exist in the library
class Repeated_Book { };  // a book already exists in the library
class Invalid_Patron { }; // patron does not exist in the library
class Repeated_Patron { }; // patron already exists in the library
class Patron_Owes_Fees { }; // patron owes fees (sic)
class Checked_Out_Book { }; // book is already checked out

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
bool operator==(const Patron& a, const Patron& b);
bool operator!=(const Patron& a, const Patron& b);

class Library {
public:
    struct Transaction {
        Book book;
        Patron patron;
        Chrono::Date date;
    };

    void add_book(Book b);
    void add_patron(Patron p);
    void check_out(Book b, Patron p, Chrono::Date d);

    // Reports
    vector<string> with_fees() const; // Return names of users that owe fees
    void print_books(ostream& os) const;
    void print_patrons(ostream& os) const;
    void print_transactions(ostream& os) const;
private:
    bool is_book(const Book& b) const; // tell if a book belongs the library
    bool book_in(const Book& b) const; // tell if a book is checked in
    Book& book(const Book& b); // returns the element of m_book equal to b
    bool is_patron(const Patron& p) const; // tell if a patron already exists
    Patron& patron(const Patron& p); // returns the element of
                                     // m_patron equal to p
    vector<Book> m_book;
    vector<Patron> m_patron;
    vector<Transaction> m_transaction;
};

// Transaction operators
ostream& operator<<(ostream& os, const Library::Transaction& t);

} // namespace Mylib

#endif
