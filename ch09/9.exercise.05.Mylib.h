// 9.exercise.05.Mylib.h
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
// I think that a default constructor for Book is nonsense. We could invent a
// book but it's not very logical. So only a explicit all-date constructor is
// defined. Also, on book creation, I think it couldn't be checked out, so
// initial value for Book::co will be false.

#include "std_lib_facilities.h"
#include "9.exercise.05.Chrono.h"

#ifndef MYLIB_H
#define MYLIB_H

namespace Mylib {

using Chrono::Date;

class Invalid_ISBN { };  // to throw in case ISBN is not valid

class Book {
public:
    Book(string isbn, string title, string author, Date copyright);

    // modifying function members
    void check_out() { co = true; }
    void check_in() { co = false; }

    // non-modifying function members
    const string& isbn() const { return id; }
    const string& title() const { return tit; }
    const string& author() const { return auth; }
    const Date& copyright() const { return cright; }
    const bool checked_out() const { return co; }
private:
    string id;
    string tit;
    string auth;
    Date cright;
    bool co;
};

// helper functions

bool is_isbn(const string& isbn);
void print(ostream& os, const Book& book);

} // namespace Mylib

#endif
