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

#include "std_lib_facilities.h"
#include "9.exercise.05.Chrono.h"
#include "9.exercise.05.Mylib.h"

using Chrono::Date;
using Mylib::Book;

int main()
try
{
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

