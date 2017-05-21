// 9.exercise.08.Mylib.cpp
//
//  Create a Patron class for the library. The class will have a user's name,
//  library card number, and library fees (if owed). Have functions that access
//  this data, as well as a function to set the fee of the user. Have a helper
//  function that returns a Boolean (bool) depending on whether or not the user
//  owns a fee.

#include "std_lib_facilities.h"
#include "9.exercise.08.Chrono.h"
#include "9.exercise.08.Mylib.h"

namespace Mylib {

// Genre operators
ostream& operator<<(ostream& os, Genre g)
{
    switch (g) {
        case Genre::fiction:
            os << "Fiction";
            break;
        case Genre::nonfiction:
            os << "Non fiction";
            break;
        case Genre::periodical:
            os << "Periodical";
            break;
        case Genre::biography:
            os << "Biography";
            break;
        case Genre::children:
            os << "Children";
            break;
        default:
            os << "Unknown genre";
            break;
    }
    return os;
}

// Book member functions
Book::Book(string isbn, string title, string author, Date copyright, Genre genre)
    : id{isbn}, tit{title}, auth{author},
    cright{copyright}, gen{genre}, co{false}
{
    if (!is_isbn(isbn)) throw Invalid_ISBN{};
}

// Book helper functions
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
       << "  Genre: " << book.genre() << '\n'
       << "  ISBN: " << book.isbn() << '\n'
       << "  Copyright date: " << book.copyright() << '\n'
       << "  Checked: ";
    if (book.checked_out()) os << "OUT\n";
    else os << "IN\n";

    return os;
}

// Patron member functions
Patron::Patron(string name, string card_number):
    n{name}, id{card_number}, f{0}
{
}

void Patron::set_fees(double fees)
{
    if (fees < 0) error("Patron::set_fees(): negative fees");
    f = fees;
}

// Patron helper functions
bool owes_fees(const Patron& p)
{
    return (p.fees() != 0);
}

// Patron operators
ostream& operator<<(ostream& os, const Patron& p)
{
    os << "User's name: " << p.name() << '\n'
       << "Card number: " << p.card_number() << '\n'
       << "Fees owed:   " << p.fees() << '\n';

    return os;
}

} // namespace Mylib

