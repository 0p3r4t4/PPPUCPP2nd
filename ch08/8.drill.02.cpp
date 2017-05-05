// 8.drill.02.cpp
//
// Write three functions swap_v(int, int), swap_r(int&, int&), and
// swap_cr(const int&, const int&). Each should have the body:
//
//  { int temp; temp = a; a = b; b = temp; }
//
// where a and b are the names of the arguments.
// Try calling each swap like this ... (see main())
//
// Which functions and calls compiled, and why? After each swap that compiled,
// print the value of the arguments after the call to see if they were actually
// swapped. If you are surprised by a result, consult §8.6.

#include "std_lib_facilities.h"

void swap_v(int a, int b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void swap_r(int& a, int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

// This function does not compile as we are trying to assign values to
// read-only references. We can safely discard it.
// void swap_cr(const int& a, const int& b)
// {
//     int temp;
//     temp = a;
//     a = b;
//     b = temp;
// }

int main()
{
    int x = 7;
    int y = 9;
    
    // swap_v(x, y);   // Compiles but does not swap anything, as expected since 
    //                 // swap_v only manages copies of its arguments.
    swap_r(x, y);   // OK: Compiles and swaps values as expected
    // swap_v(7, 9);   // Compiles but does nothing, as temporary objects made
    //                 // inside function to store the arguments are destroyed
    //                 // on function return and no reference to original
    //                 // arguments is possible
    // swap_r(7, 9);   // Does not compile as a reference could not be initialized
    //                 // with an rvalue (literal) since there is no object that
    //                 // could be referenced.

    // Auxiliary output message. 
    cout << "x is now " << x << " and y is now " << y << '\n';

    const int cx = 7;
    const int cy = 9;

    // swap_v(cx, cy); // Compiles since we are passing copies of variables and, 
    //                 // I guess, a copy of a const variable does not need to be
    //                 // const itself. But it doesn't swap as it manages copies.
    // swap_r(cx, cy); // Does not compile. It seems that trying to make a non-const
    //                 // reference to a const variable is not fine. It makes
    //                 // sense.

    // These two calls also causes truncation of its arguments.
    // swap_v(7.7, 9.9);   // Compiles but does nothing. Same reason as swap_v(7,9)
    // swap_r(7.7, 9.9);   // Does not compile. Same reason as swap_r(7,9)

    // Auxiliary output message. 
    cout << "cx is now " << cx << " and cy is now " << cy << '\n';

    double dx = 7;
    double dy = 9;

    // swap_v(dx, dy); // Compiles but does not swap. Same as previous swap_v calls.
    // swap_r(dx, dy); // Surprisingly it does not compile. But, since we are facing
    //                 // an implicit conversion from double to int, what the 
    //                 // function is receiving is an rvalue and no reference can
    //                 // be made. It makes sense.

    // Auxiliary output message. 
    cout << "dx is now " << dx << " and dy is now " << dy << '\n';

    return 0;
}
