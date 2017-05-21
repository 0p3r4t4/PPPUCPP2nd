// 9.exercise.07.Mylib.cpp
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

namespace Mylib {
    
Book::Book(string isbn, string title, string author, Date copyright, Genre genre)
    : id{isbn}, tit{title}, auth{author},
    cright{copyright}, gen{genre}, co{false}
{
    if (!is_isbn(isbn)) throw Invalid_ISBN{};
}

// helper functions

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
       << "  Genre: " << parse_genre(book.genre()) << '\n'
       << "  Checked: ";
    if (book.checked_out()) os << "OUT\n";
    else os << "IN\n";
}

string parse_genre(const Genre& genre) {

    switch (genre) {
        case Genre::fiction:
            return "Fiction";
        case Genre::nonfiction:
            return "Non fiction";
        case Genre::periodical:
            return "Periodical";
        case Genre::biography:
            return "Biography";
        case Genre::children:
            return "Children";
        default:
            return "Unknown genre";
    }
}

// Book operators
bool operator==(const Book& a, const Book& b)
{
    return (a.isbn() == b.isbn());
}

bool operator!=(const Book& a, const Book& b)
{
    return !(a == b);
}

ostream& operator<<(ostream& os, const Book& book)
{
    os << book.title() << '\n'
       << "  Author: " << book.author() << '\n'
       << "  Genre: " << parse_genre(book.genre()) << '\n'
       << "  ISBN: " << book.isbn() << '\n';

    return os;
}

} // namespace Mylib

