// 9.exercise.02.cpp
//
//  Design and implement a Name_pairs class holding (name,age) pairs where name
//  is a string and age is a double. Represent that as a vector<string>
//  (called name) and a vector<double> (called age) member. Provide an input
//  operation read_names() that reads a series of names. Provide a read_ages()
//  operation that prompts the user for an age for each name. Provide a
//  print() operation that prints out the (name[i],age[i]) pairs (one per line)
//  in the order determined by the name vector. Provide a sort() operation
//  that sorts the name vector in alphabetical order and reorganize the age
//  vector to match. Implement all "operations" as member functions. Test the
//  class (of course: test early an often).
//
// COMMENTS
// 
//  Basically this is an encapsulation in a class of functionality implemented
//  in exercise 8 from chapter 8. We have half of the work already done.
//  
//  Is default constructor enough? Since data members are default initialized,
//  I don't think I need explicit declared constructors.
//  
//  read_names() has been simplified compared to the former version.
// 
//  print() and sort() implies name and age must be the same size.
//
//  sort() is implemented slightly different than in reference exercise. I
//  think also better. Sort is performed on copies and only after all goes
//  right the sorted copies take the place of the originals. This way if a
//  exception is thrown, the previous object state is not modified (exception
//  safe code?).
//  Also, in Name_pairs::sort() we call std::sort(). If we jsut call it with
//  sort() the compiler argues that the only candidate is Name_pairs::sort().
//  So we must fully qualify std::sort() or use a local using declaration to
//  force the use of std::sort(). I'll take the second but the former is, by
//  the way, simpler and more readable. Doing things consciously wrong :-P
//
//  Ability to add more names? Not yet. It's not difficult; we must keep
//  track of the index where we start get more names to avoid asking ages for
//  the previous ones already entered. 
//  
//  print() prints the pairs sorted by name, but I don't think it should change
//  the class state, so copies must be in place. This function shares code with
//  sort() and perhaps we must take this code out to a new function. I have
//  some ideas to do so, but the will complicate the exercise beyond acceptable
//  (at least for me). I have taken the full qualified std::sort() this time.

#include "std_lib_facilities.h"

class Name_pairs {
public:
    void read_names();      // read a series of names
    void read_ages();       // read the ages for each names

    void print() const;     // print pairs of (name,age) sorted by name
    void sort();            // sort names applying that order to their
                            // related ages
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

void Name_pairs::print() const
// Prints a line with each name and its respective age, from the same both
// elements of two distinct vectors. Printing are done sorted by name.
{
    if (name.size() != age.size())
        error("Name_pairs::print(): name and age"
              "sizes differ (no age read performed?)");

    vector<string> s_name{name};   // name work copy
    vector<double> s_age{age};     // age work copy

    // First sort the copies
    std::sort(s_name.begin(), s_name.end());
    size_t limit = s_name.size();
    for (size_t i = 0; i < limit; ++i)
        s_age[i] = age[name_idx(s_name[i])];

    // Now print sorted
    for (size_t i = 0; i < limit; ++i)
        cout << "\t(" << s_name[i] << ", " << s_age[i] << ")\n";
}

int main()
try {
    Name_pairs pairs;

    pairs.read_names();
    pairs.read_ages();
    cout << "\nOK! So you tell me about these people:\n";
    pairs.print();
    pairs.sort();
    cout << "\nThat sorted alphabetically by name are:\n";
    pairs.print();
    cout << '\n';

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
