// 5.3.2.try_this.cpp
//
// Try to compile those examples and see how the compiler responds. Try
// thinking of a few more errors yourself, and try those.
//
// Comments:
//  I have included examples for 5.3.3 to see how GNCC g++ 6.2 performs about
//  them.

#include "std_lib_facilities.h"

int area(int length, int width);

int main()
{
    // error: ‘arena’ was not declared in this scope
    int x0 = arena(7);

    // too few arguments to function ‘int area(int, int)’
    int x1 = area(7);

    // error: invalid conversion from ‘const char*’ to ‘int’ [-fpermissive]
    int x2 = area("seven", 2);
    
    // error: too many arguments to function ‘int area(int, int)’
    int x3 = area(1, 2, 3);

    // No error at all
    int x4 = area(10, -7);

    // No error at all 
    int x5 = area(10.7, 9.3);

    // No error at all
    char x6 = area(100, 9999);

    // error: conversion from ‘int’ to non-scalar type ‘std::__cxx11::string
    // {aka std::__cxx11::basic_string<char>}’ requested 
    string x7 = area(4, 5);

    // error: conflicting declaration ‘int x7’
    int x7 = area(4, 5);
    
    // error: redeclaration of ‘std::__cxx11::string x7’
    string x7 = "Test";

    // warning: narrowing conversion of ‘area(4, 5)’ from ‘int’ to ‘char’
    // inside { } [-Wnarrowing]
    string x8 {area(4, 5)};
}
