// 8.exercise.08.cpp
//
//  Then, do that exercise again but allowing an arbitrary number of names.
//
// PREVIOUS STATEMENT
//  
//  Read five names into a vector<string> name, then prompt the user for the
//  ages of the people named and store the ages in a vector<double> age. Then
//  print out the five (name[i],age[i]) pairs. Sort the names
//  (sort(name.begin(),name.end()) and print out the (name[i],age[i]) pairs.
//  The tricky part here is to get the age vector in the correct order to match
//  the sorted name vector. Hint: Before sorting name, take a copy and use that
//  to make a copy of age in the right order after sorting name.
//  
// COMMENTS
//
//  Global constant name_no has no sense anymore.
//  With a bit of luck, only get_names() needs changes. We add a command to
//  stop inserting names, and check for it on user input inside and infinite
//  loop.

#include "std_lib_facilities.h"

const string stop{"stop"};

bool is_in(const vector<string>& v, const string& s)
// Checks if string s is already present on vector v.
{
    for (string x : v)
        if (x == s) return true;
    return false;
}

void get_names(vector<string>& name)
// Asks the user for names and adds them to a vector until the user writes
// stop.
// No duplicate names are permitted.
{
    cout << "Write people names (write stop when there's enough)...\n";
    for (;;) {
        cout << ": ";
        string n;
        cin >> n;
        if (n == stop) return;
        while (is_in(name, n)) {
            cout << "Duplicated name " << n << "! Try again ...\n: ";
            cin >> n;
        }
        name.push_back(n);
    }
}

void get_ages(const vector<string>& name, vector<double>& age)
// Get ages for people in name vector. Adds them to a "parallel" vector
// correlated by indexes.
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

void print_pairs(const vector<string>& name, const vector<double>& age)
// Prints a line with a name and its respective age, from the same both
// elements of two distinct vectors.
{
    size_t limit = name.size();     // To avoid evaluate a function call
                                    // at the for condition each loop
    for (size_t i = 0; i < limit; ++i)
        cout << '\t' << name[i] << " is " << age[i] << " years old.\n";
}

size_t name_idx(const vector<string>& name, const string& n)
// Returns the index at which a name (n) is located on a vector (name).
// As the program goes we are almost sure the name will be present, so an error
// is thrown otherwise.
{
    size_t limit = name.size();
    for (size_t i = 0; i < limit; ++i)
        if (name[i] == n) return i;
    error("name_idx(): No element found!");
}

void sort_pairs(vector<string>& name, vector<double>& age)
// Sort a vector (name) and extends the position changes to a second 
// vector (age) of the same size.
{
    vector<string> orig_name{name};   // Reference pre-sorted vector
    vector<double> orig_age{age};     // Source to build a new shuffled vector

    sort(name);
    size_t limit = name.size();
    for (size_t i = 0; i < limit; ++i)
        age[i] = orig_age[name_idx(orig_name, name[i])];
}

int main()
try {
    vector<string> name;
    vector<double> age;

    get_names(name);
    get_ages(name, age);
    cout << "\nOK! So you tell me about these people:\n";
    print_pairs(name, age);
    sort_pairs(name, age);
    cout << "\nThat sorted by name are:\n";
    print_pairs(name, age);
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
