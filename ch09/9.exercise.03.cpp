// 9.exercise.03.cpp
//
//  Replace Name_pair::print() with a (global) operator << and define == and !=
//  for Name_pairs.
//
// COMMENTS
//
//  If we implement << operator globally, how can we access the data inside of
//  Name_pairs? Making the data public is not an option, but returning a const
//  reference to them through a const member function could do the trick.
//  It seems so.
//  I've also copied the object and used sort() on that copy. It somehow
//  simplifies the sorted print code at cost of one more copy than those
//  extrictly necessary.
//
//  For == operator, we must assure that data members from two objects are
//  equal. Since we have two vectors as sensible data and vector<> has its own
//  == operator, we can take advantage of that. We already have a way to refer
//  to the data members as done for << operator.
//  != operator can be defined based on == operator.

#include "std_lib_facilities.h"

class Name_pairs {
public:
    void read_names();      // read a series of names
    void read_ages();       // read the ages for each names

    void sort();            // sort names applying that order to their
                            // related ages
    const vector<string>& get_names() const { return name; }
    const vector<double>& get_ages() const { return age; }
private:
    const string stop{"stop"};  // command to stop read_names()
    vector<string> name;
    vector<double> age;

    bool is_in(const string& n) const; // check if string s is already in name
    size_t name_idx(const string& n) const; // return name index for n
};

bool Name_pairs::is_in(const string& n) const
// Checks if string n is already present on name vector.
{
    for (string x : name)
        if (x == n) return true;
    return false;
}

void Name_pairs::read_names()
// Asks the user for names and adds them to name vector until the user writes
// stop.
// No duplicate names are permitted.
{
    cout << "Write people names (write stop when there's enough)...\n: ";
    string n;
    while (cin >> n && n != stop) {
        if (is_in(n))
            cout << "Duplicated name " << n << "! Try again ...\n";
        else 
            name.push_back(n);
        cout << ": ";
    }
}

void Name_pairs::read_ages()
// Get ages for people in name vector.
{
    cout << "Give me the ages of each person, please ...\n";
    for (string n : name) {
        cout << "How old is " << n << "? ";
        double a{0}; 
        while (!(cin >> a)) {
            // Make sure that we read a number.
            cout << "Sorry, I don't understand you! How old is " << n << "? ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        age.push_back(a);
    }
} 

size_t Name_pairs::name_idx(const string& n) const
// Returns the index at which a name (n) is located on a vector (name).
// As the program goes we are almost sure the name will be present, so an error
// is thrown otherwise.
{
    size_t limit = name.size();
    for (size_t i = 0; i < limit; ++i)
        if (name[i] == n) return i;
    error("Name_pairs::name_idx(): No element found!");
}

void Name_pairs::sort()
// Sort name vector and extends the position changes to the age vector The
// vectors must be the same size.
{
    if (name.size() != age.size())
        error("Name_pairs::sort(): name and age"
              "sizes differ (no age read performed?)");

    vector<string> s_name{name};   // name work copy
    vector<double> s_age{age};     // age work copy

    // Perform sort on copies, not modifying the object state until the end
    using std::sort;      // Compiler only saw a candidate; Name_pairs::sort()
                          // so it must be forced. We could also use
                          // std::sort() instead.
    sort(s_name.begin(), s_name.end());
    size_t limit = s_name.size();
    for (size_t i = 0; i < limit; ++i)
        s_age[i] = age[name_idx(s_name[i])];

    // If everything goes right, exchange the vectors
    name = s_name;
    age = s_age;
}

ostream& operator<<(ostream& os, const Name_pairs& np)
// Prints a line with each name and its respective age, from the same both
// elements of two distinct vectors. Printing are done sorted by name.
{
    // Copy the Name_pairs object and sort it (left the original untouched)
    Name_pairs pairs{np};
    pairs.sort();

    // Get the data (by reference, needly const, to avoid copying)
    const vector<string>& name{pairs.get_names()};
    const vector<double>& age{pairs.get_ages()};
    
    if (name.size() != age.size())
        error("Name_pairs << operator: name and age"
              "sizes differ (no age read performed?)");

    // Now print sorted data
    size_t limit = name.size();
    for (size_t i = 0; i < limit; ++i)
        cout << "\t(" << name[i] << ", " << age[i] << ")\n";

    return os;
}

bool operator==(const Name_pairs& a, const Name_pairs& b)
{
    return (a.get_names() == b.get_names() &&
            a.get_ages()  == b.get_ages());
}

bool operator!=(const Name_pairs& a, const Name_pairs& b)
{
    return !(a == b);
}

int main()
try {
    Name_pairs pairs;

    pairs.read_names();
    pairs.read_ages();
    cout << "\nOK! So you tell me about these people:\n";
    cout << pairs;
    pairs.sort();
    cout << "\nThat sorted alphabetically by name are:\n";
    cout << pairs;
    cout << '\n';

    Name_pairs others;
    others.read_names();
    others.read_ages();
    others.sort();      // pairs are sorted, so to compare we must sort
                        // others too.
    cout << "\nOK! So you tell me about these people:\n";
    cout << others;
    // Test == and != operators
    if ( pairs == others )
        cout << "Exactly the same people!\n";
    if ( pairs != others )
        cout << "Just another set of people.\n";

    return 0;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch(...)
{
    cerr << "Unknown exception!\n";
    return 2;
}
