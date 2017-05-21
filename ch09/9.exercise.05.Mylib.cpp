// 9.exercise.05.Mylib.cpp
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
// is_isbn() helper function is horrible by itself. But as stand alone check is
// the best I can think of right now.
// print() is implemented for convenience to do testing. It could be
// implemented as an overload to << operator, as asked for in exercise 6.

#include "std_lib_facilities.h"
#include "9.exercise.05.Chrono.h"
#include "9.exercise.05.Mylib.h"

namespace Mylib {
    
Book::Book(string isbn, string title, string author, Date copyright)
    : id{isbn}, tit{title}, auth{author}, cright{copyright}, co{false}
{
    if (!is_isbn(isbn)) throw Invalid_ISBN{};
}

bool is_isbn(const string& isbn)
// Checks if isbn has the form n-n-n-x where n is an integer and x is a digit
// or a letter. This is horrendous, but I lack some more advanced tools.
{
    int hyphen{0};  // Number of hyphens found
    bool n{false};  // We are traversing a number

    for (size_t i = 0; i < isbn.size(); ++i) {
        char c{isbn[i]};          // Current char examined

        // With less that 3 hyphens we search for digits or hyphens
        if (hyphen < 3) {
            if (!isdigit(c)) {
                if (c == '-' && n) {   // Hyphen marks end of a number
                    ++hyphen;
                    n = false;
                }    
                else {
                    return false; 
                }
            }
            else {
                // is digit so we're on a number
                n = true;
            }
        }
        else {      // After the third hyphen only a char must be left
            if (i != (isbn.size()-1)) return false;
            // and it must be a digit or a letter
            return (isdigit(c) || isalpha(c));
        }
    }
    // if loop ends without returning, the format is invalid
    return false;
}

void print(ostream& os, const Book& book)
{
    os << book.title() << '\n'
       << "  Author: " << book.author() << '\n'
       << "  ISBN: " << book.isbn() << '\n'
       << "  Copyright date: " << book.copyright() << '\n'
       << "  Checked: ";
    if (book.checked_out()) os << "OUT\n";
    else os << "IN\n";
}

} // namespace Mylib

