// 5.10.1.try_this.cpp
//
// Find a pair of values so that the pre-condition of this version of area
// holds, but the post-condition doesn't
//
// Comments:
//  As stated in 5.5.3.try_this.cpp, depending on the representational range of
//  int type, the product of two positive int variables could result, by
//  overflow, in a negative number (i.e., 60000 and 60000 if int is 4 bytes)

#include "std_lib_facilities.h"

int area(int length, int width)
// calculate area of a rectangle
// pre-conditions: length and width are positive
// post-condition: returns a positive value that is the area
{
    if (length <= 0 || width <= 0) throw runtime_error("area() pre-contitions violated");
    int a = length*width;
    if (a <= 0) throw runtime_error("area() post-condition violated");
    return a;
}

int main()
try 
{
    int length = 0;
    int width = 0;
    
    cout << "Write length and width to get the area of the rectangle:\n"
        << "(Test with negative numbers and numbers large enough to overflow\n"
        << "to violate pre and post-conditions of area() function)\n";
    
    while (cin >> length >> width)
        cout << "Area is " << area(length, width) << '\n';

    return 0;
}
catch (runtime_error& e) {
    cout << "Error: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cout << "Error: unknown exception\n";
    return 2;
}
