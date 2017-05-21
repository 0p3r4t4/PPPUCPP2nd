// 9.exercise.07.Mylib.h
//
//  Create an enumerated type for the Book class called Genre. Have the types
//  be fiction, nonfiction, periodical, biography, and children. Give each book
//  a Genre and make appropiate changes to the Book constructor and member
//  functions.
//
// COMMENTS

#include "std_lib_facilities.h"
#include "9.exercise.07.Chrono.h"

#ifndef MYLIB_H
#define MYLIB_H

namespace Mylib {

using Chrono::Date;

class Invalid_ISBN { };  // to throw in case ISBN is not valid

enum class Genre {
    fiction, nonfiction, periodical, biography, children
};

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

// helper functions

bool is_isbn(const string& isbn);
void print(ostream& os, const Book& book);
string parse_genre(const Genre& genre);

// Book operators
bool operator==(const Book& a, const Book& b);
bool operator!=(const Book& a, const Book& b);
ostream& operator<<(ostream& os, const Book& book);

} // namespace Mylib

#endif
