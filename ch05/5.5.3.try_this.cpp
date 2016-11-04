// 5.5.3.try_this.cpp
//
// Test *this program* with a variety of values. Print out the values of area1,
// area2, area3 and ratio. Insert more tests until all errors are caught. How
// do you know that you caught all errors? This is not a trick question; in
// this particular example you can give a valid argument for having caught all
// errors.
//
// Comments:
//  I don't know if I'm taking this problem right. I will use area() version
//  from 5.5.3 and let framed_area() (from 5.5 without magic constants) delegates 
//  error handling on that.
//  
//  Although area() tests its arguments to be greater than 0, representation
//  range overflow could trick us. Supose int to be 32 bit:
//      - 2^16 * 2^16 (65536*65536) give as 0 as result.
//      - 1431655765 * 3 give us -1 as result (and this conflicts with out
//      error reporting decision to return -1)
//      - 60000 * 60000 gives us -694967296, a negative number.
//  So, another effect of returning a value to indicate an error is that
//  we can not distingish the real cause of that error (bad arguments?
//  overflow?). We will stick to that decision to detect an erroneous result
//  without let the caller to know the cause.
//
//  Of course, since we don't allow arguments to be 0 and overflow can cause
//  the result to be, the caller must check the return value to not be 0.

#include "std_lib_facilities.h"

constexpr int frame_width {2};

// calculate area of a rectangle;
// return -1 to indicate a bad argument
int area(int length, int width)
{
    if (length <= 0 || width <= 0) return -1;
    return length*width;
}

// calculate area within frame
int framed_area(int x, int y)
{
    return area(x - frame_width, y - frame_width);
}

// Example function
int f(int x, int y, int z)
{
    int area1 = area(x, y);
    if (area1 <= 0) error("non-positive area");

    // area2, with frame_width of 2 will always be erroneous
    // It is nonsense to preserve it then
    //int area2 = framed_area(1, z);
    
    int area3 = framed_area(y, z);
    if (area3 <= 0) error("non-positive area");

    // by getting here, having pass through the previous test to area3,
    // we can be sure ratio would not cause division by zero
    double ratio = double(area1)/area3;

    cout << "\tarea1, area(x,y): " << area1 << '\n'
        //<< "\tarea2, framed_area(1, z): " << area2 << '\n'
        << "\tarea3, framed_area(y, z): " << area3 << '\n'
        << "\tratio, area1/area3: " << ratio << '\n';

    return 0;
}

int main()
{
    int x {0};
    int y {0};
    int z {0};

    while (cin >> x >> y >> z) {
        cout << "x:" << x << ", y:" << y << ", z:" << z << '\n';
        f(x, y, z);
    }
                            
    return 0;
}
