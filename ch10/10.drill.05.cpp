// 10.drill.05.cpp
//
//  Close the ofstream and then open an ifstream for mydata.txt. Read the data
//  from mydata.txt and store it in a new vector called processed_points.
//
// COMMENTS
//
//  I will implement fill_from_file() from §10.4.

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

void fill_from_file(vector<Point>& points, const string& name)
{
    ifstream ist{name};
    if (!ist) error("can't open input file ", name);

    for (Point p; ist >> p;)
        points.push_back(p);
}

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

    cout << "You've entered those points:\n" << original_points;

    cout << "Writing to file " << of_name << " ...\n";
    ofstream ost{of_name};
    if (!ost) error("can't open output file", of_name);
    ost << original_points;
    ost.close();

    cout << "Reading point from file " << if_name << " ...\n";
    vector<Point> processed_points;
    fill_from_file(processed_points, if_name);

    cout << processed_points;   // Test if we read something
    
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
