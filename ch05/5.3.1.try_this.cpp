// 5.3.1.try_this.cpp
//
// Try to compile those examples and see how the compiler responds.
//
// Comments: compiled with GNUCC g++ 6.2.0 with options -std=c++1z -Wall,
// testing each area function call separately, and ignoring obvious warning
// messages as "unused variable 's1'".
// If s2 and s3 are active at same time, no error on s3 is detected, only in s2;
// perhaps the missing ; hides the s3 call and since the error detected in s2
// is not the absence of ; but too few arguments on call to area ...

#include "std_lib_facilities.h"

int area(int length, int width);

int main()
{
    // 18:20: error: expected ‘)’ before ‘;’ token 
    int s1 = area(7;

    // 22:20: error: too few arguments to function ‘int area(int, int)’
    int s2 = area(7)

    // 24:5: error: ‘Int’ was not declared in this scope
    Int s3 = area(7);

    // 29:19: error: missing terminating ' character
    // 30:1: error: expected primary-expression before ‘}’ token 
    int s4 = area('7);
}
    
