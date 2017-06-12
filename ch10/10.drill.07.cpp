// 10.drill.07.cpp
//
//  Compare the two vectors and print Something's wrong! if the number of
//  elements or the values of elements differ.
//
// COMMENTS
//
//  We can compare two vectors directly with == operator, given that the type
//  of elements has == operator as well. Since Point has private data members
//  we should provide it.

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

bool operator==(const Point& lhs, const Point& rhs)
{
    return ((lhs.x() == rhs.x()) && (lhs.y() == rhs.y()));
}

istream& operator>>(istream& is, Point& p)
{
    double x, y;
    char ch1, ch2, ch3;

    is >> ch1 >> x >> ch2 >> y >> ch3;
    if (is && ch1 == '(' && ch2 == ',' && ch3 == ')')
        p = Point(x, y);
    else 
        is.clear(ios_base::failbit);
    
    return is;
}

ostream& operator<<(ostream& os, vector<Point>& vp)
{
    for (Point p : vp)
        os << '(' << p.x() << ", " << p.y() << ')' << '\n';

    return os;
}

constexpr int no_points{7};
const string of_name = "mydata.txt";
const string if_name = "mydata.txt";

void get_points(istream& is, vector<Point>& points, size_t size)
// if size is 0, do not limit number of points to be obtained
{
    for(Point p; is >> p;) {
        if (is) {
            points.push_back(p);
        }
        else {
            cout << "Not a point!\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if ((size != 0) && (points.size() >= size)) break;
    }
}

int main()
try{
    cout << "Write " << no_points << " points as pairs of coordinates with" 
         << " format (x,y):\n";
    vector<Point> original_points;
    get_points(cin, original_points, no_points);

    cout << "You've entered those points:\n" << original_points;

    cout << "Writing to file " << of_name << " ...\n";
    ofstream ost{of_name};
    if (!ost) error("can't open output file", of_name);
    ost << original_points;
    ost.close();

    cout << "Reading point from file " << if_name << " ...\n";
    vector<Point> processed_points;
    ifstream ist{if_name};
    if (!ist) error("can't open input file ", if_name);
    get_points(ist, processed_points, 0);

    cout << "Points in file \"" << if_name << "\":\n" <<  processed_points;

    // Provoke it
    // original_points[2] = Point{-1, -1};

    if (original_points != processed_points)
        cerr << "Something's wrong!\n";
    
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
