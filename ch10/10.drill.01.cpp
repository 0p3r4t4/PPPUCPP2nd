// 10.drill.01.cpp
//
//  Start a program to work with points, discussed in §10.4. Begin by defining
//  the data type Point that has two coordinate members x and y.
//
// COMMMENTS
//
//  This is not exactly the Point from book, since it has public data
//  members and this has private data members. For such a trivial exercise it
//  would not matter, but I really prefer to hide data as a rule.

#include "std_lib_facilities.h"

class Point {
public:
    Point(double x, double y);
    double x() const { return m_x; }
    double y() const { return m_y; }
private:
    double m_x;
    double m_y;
};

Point::Point(double x, double y)
: m_x{x}, m_y{y} {  };

int main()
try{
    Point p{3.14, 2.69};

    cout << '(' << p.x() << ", " << p.y() << ')' << '\n';
    
    return 0;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch(...)
{
    cerr << "Unknown exception!!\n";
    return 2;
}
