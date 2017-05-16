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
//  vector to match. Implement all "operations" as memeber functions. Test the
//  class (of course: test early an often).
//
// COMMENTS
// 
//  Basically this is an encapsulation in a class of functionality implemented
//  in exercise 8 from chapter 8. We have half of the work already done.
//  
//  Constructors?
//  Ability to add more names?
//  print() and sort() implies name and age must be the same size.

#include "std_lib_facilities.h"

class Name_pairs {
public:
    void read_names();      // read a series of names
    void read_ages();       // read the ages for each names

    void print();           // print pairs of (name,age) sorted by name
    void sort();            // sort names applying that order to their
                            // related ages
private:
    const string stop{"stop"};  // command to stop read_names()
    vector<string> name;
    vector<double> age;

    bool is_in(const string& s); // Check if string s is already in name
};

bool Name_pairs::is_in(const string& s)
// Checks if string s is already present on vector v.
{
    for (string x : name)
        if (x == s) return true;
    return false;
}

void Name_pairs::read_names()
// Asks the user for names and adds them to name vector until the user writes
// stop.
// No duplicate names are permitted.
{
    cout << "Write people names (write stop when there's enough)...\n";
    for (;;) {
        cout << ": ";
        string n;
        cin >> n;
        if (n == stop) return;
        while (is_in(n)) {
            cout << "Duplicated name " << n << "! Try again ...\n: ";
            cin >> n;
        }
        name.push_back(n);
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

void Name_pairs::print()
// Prints a line with each name and its respective age, from the same both
// elements of two distinct vectors.
{
    size_t limit = name.size();     // To avoid evaluate a function call
                                    // at the for condition each loop
    for (size_t i = 0; i < limit; ++i)
        cout << "\t(" << name[i] << ", " << age[i] << ")\n";
}

int main()
try {
    Name_pairs pairs;

    pairs.read_names();
    pairs.read_ages();
    cout << "\nOK! So you tell me about these people:\n";
    pairs.print();
    //sort_pairs(name, age);
    //cout << "\nThat sorted by name are:\n";
    //print_pairs(name, age);
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
