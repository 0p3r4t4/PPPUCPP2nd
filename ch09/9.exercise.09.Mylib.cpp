// 9.exercise.09.Mylib.cpp
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

#include "std_lib_facilities.h"
#include "9.exercise.09.Chrono.h"
#include "9.exercise.09.Mylib.h"

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
Book::Book(string isbn, string title, string author, Chrono::Date copyright,
    Genre genre) : m_isbn{isbn}, m_title{title}, m_author{author},
    m_copyright{copyright}, m_genre{genre}, m_checked_out{false}
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

ostream& operator<<(ostream& os, const Book& b)
{
    os << b.title() << '\n'
       << "  Author: " << b.author() << '\n'
       << "  Genre: " << b.genre() << '\n'
       << "  ISBN: " << b.isbn() << '\n'
       << "  Copyright date: " << b.copyright() << '\n'
       << "  Checked: ";
    if (b.checked_out()) os << "OUT\n";
    else os << "IN\n";

    return os;
}

// Patron member functions
Patron::Patron(string name, string card_number):
    m_name{name}, m_card_number{card_number}, m_fees{0}
{
}

void Patron::set_fees(double fees)
{
    if (fees < 0) error("Patron::set_fees(): negative fees");
    m_fees = fees;
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

bool operator==(const Patron& a, const Patron& b)
{
    return (a.card_number() == b.card_number());
}

bool operator!=(const Patron& a, const Patron& b)
{
    return !(a == b);
}

// Library member functions
void Library::add_book(Book b)
{
    if (is_book(b)) throw Repeated_Book{};
    m_book.push_back(b);
}

void Library::add_patron(Patron p)
{
    if (is_patron(p)) throw Repeated_Patron{};
    m_patron.push_back(p);
}

void Library::check_out(Book b, Patron p, Chrono::Date d)
{
    if (!is_patron(p)) throw Invalid_Patron{};
    if (!is_book(b)) throw Invalid_Book{};
    if (!book_in(b)) throw Checked_Out_Book{};
    if (owes_fees(patron(p))) throw Patron_Owes_Fees{};

    m_transaction.push_back(Transaction{b, p, d});
    book(b).check_out();
    patron(p).set_fees(10.0);
}

vector<string> Library::with_fees() const
// Return names of users that owes fees
{
    vector<string> names;

    for (Patron p : m_patron)
        if (owes_fees(p))
            names.push_back(p.name());
    
    return names;
}

void Library::print_books(ostream& os) const
// Print the library books
{
    for (Book b : m_book)
        os << b;
}

void Library::print_patrons(ostream& os) const
// Print the library patrons
{
    for (Patron p : m_patron)
        os << p;
}

void Library::print_transactions(ostream& os) const
// Print the library transactions
{
    for (Transaction t : m_transaction)
        os << t;
}
   
bool Library::is_book(const Book& b) const
{
    for (Book x : m_book)
        if (x == b) return true;
    return false;
}

Book& Library::book(const Book& b)
{
    for (Book& x : m_book)
        if (x == b) return x;
    throw Invalid_Book{};
}

bool Library::book_in(const Book& b) const
{
    for (Book x : m_book)
        if (x == b)
            return !x.checked_out();
    return false;
}

bool Library::is_patron(const Patron& p) const
{
    for (Patron x : m_patron)
        if (x == p) return true;
    return false;
}

Patron& Library::patron(const Patron& p)
{
    for (Patron& x : m_patron)
        if (x == p) return x;
    throw Invalid_Patron{};
}

// Transaction operators
ostream& operator<<(ostream& os, const Library::Transaction& t)
{
    os << t.patron.name() << " toke " << t.book.title() << " (ISBN: " 
       << t.book.isbn() << ") on " << t.date << '\n';

    return os;
}

} // namespace Mylib

