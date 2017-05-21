// 9.exercise.08.Mylib.h
//
//  Create a Patron class for the library. The class will have a user's name,
//  library card number, and library fees (if owed). Have functions that access
//  this data, as well as a function to set the fee of the user. Have a helper
//  function that returns a Boolean (bool) depending on whether or not the user
//  owns a fee.
//
// COMMENTS
//
//  A new patron is created with no fees associated.
//  I included a << operator for Patron to do testing.
//  For what is worth, previous exercise parse_genre() is substituted with a
//  Genre << overloaded operator.
//  I also discarded print() Book helper function.

#include "std_lib_facilities.h"
#include "9.exercise.08.Chrono.h"

#ifndef MYLIB_H
#define MYLIB_H

namespace Mylib {

using Chrono::Date;

class Invalid_ISBN { };  // to throw in case ISBN is not valid

enum class Genre {
    fiction, nonfiction, periodical, biography, children
};

// Genre operators
ostream& operator<<(ostream& os, Genre g);

class Book {
public:
    Book(string isbn, string title, string author, Date copyright, Genre genre);

    // modifying function members
    void check_out() { co = true; }
    void check_in() { co = false; }

    // non-modifying function members
    const string& isbn() const { return id; }
    const string& title() const { return tit; }
    const string& author() const { return auth; }
    const Date& copyright() const { return cright; }
    const Genre genre() const { return gen; }
    const bool checked_out() const { return co; }
private:
    string id;
    string tit;
    string auth;
    Date cright;
    Genre gen;
    bool co;
};

// Book helper functions
bool is_isbn(const string& isbn);
void print(ostream& os, const Book& book);

// Book operators
bool operator==(const Book& a, const Book& b);
bool operator!=(const Book& a, const Book& b);
ostream& operator<<(ostream& os, const Book& book);

class Patron {
public:
    Patron(string name, string card_number);

    // modifying function members
    void set_fees(double fees);

    // non-modifying function members
    const string& name() const { return n; }
    const string& card_number() const { return id; }
    const double fees() const { return f; }
private:
    string n;       // User's name
    string id;      // Card number
    double f;          // Fees
};

// Patron helper functions
bool owes_fees(const Patron& p);

// Patron operators
ostream& operator<<(ostream& os, const Patron& p);

} // namespace Mylib

#endif
