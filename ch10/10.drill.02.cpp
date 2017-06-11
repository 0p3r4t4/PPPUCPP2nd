// 10.drill.02.cpp
//
//  Using the code and discussion in §10.4, prompt the user to input seven
//  (x,y) pairs. As the data is entered, store it in a vector of Points called
//  original_points.
//
// COMMMENTS
//
//  I don't know if I must simply ask the user for seven Points or enforce it.
//  I will enforce.
//  We must implement an input operator for Point. It will not handle errors
//  the exhaustive way though.
//  And, yes, I'm not doing it the way §10.4 does, but I can't resist myself.

#include "std_lib_facilities.h"

class Point {
public:
    Point(double x, double y);
    Point();
    double x() const { return m_x; }
    double y() const { return m_y; }
private:
    double m_x;
    double m_y;
};

Point::Point(double x, double y)
: m_x{x}, m_y{y} {  };

Point::Point()
: m_x{0}, m_y{0} {  };

istream& operator>>(istream& is, Point& p)
{
    double x, y;
    char ch1, ch2, ch3;

    is >> ch1 >> x >> ch2 >> y >> ch3;
    if (cin && ch1 == '(' && ch2 == ',' && ch3 == ')')
        p = Point(x, y);
    else 
        is.clear(ios_base::failbit);
    
    return is;
}

constexpr int no_points{7};

int main()
try{
    vector<Point> original_points;

    cout << "Write " << no_points << " points as pairs of coordinates with" 
         << " format (x,y):\n";

    while (original_points.size() < no_points) {
        Point p;
        if (cin >> p) {
            original_points.push_back(p);
        }
        else {
            cout << "That's not a point!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "You've entered those points:\n";
    for (Point p : original_points)
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
