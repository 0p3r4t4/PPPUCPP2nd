// 4.exercise.09.cpp
//
// Try to calculate the number of rice grains that the inventor asked for in
// exercise 8 above. You'll find that the number is so large that it won't
// fit in an int or a double. Observe what happens when the number gets too
// large to represent exactly as an int and as a double. What is the largest
// number of squares for which you can calculate the exact number of grains
// (using an int)? What is the largest number of squares for which you can
// calculate the approximate number of grains (using a double)?
//
// Comments:
//  Using an int the variable overflows on iteration 32, so we can not
//  calculate further the 31st square.
//  Using a double seems to be enough for 64 iterations. How far can we go
//  if there were more squares? 1024th iteration gives an infinite value for
//  the drice variable. I return to the standard 64, but feel free to change
//  and test.

#include "std_lib_facilities.h"

int main()
{
    int rice {0};
    int square_rice {1};
    double drice {0};
    double dsquare_rice {1};

    for (int square=1; square <= 64; ++square) {

        rice += square_rice;
        drice += dsquare_rice;
        square_rice *= 2;
        dsquare_rice *= 2;

        cout << "Square " << square << ": int rice (" << rice << "), double rice ("
            << drice << ")\n";
    }

    return 0;
}
