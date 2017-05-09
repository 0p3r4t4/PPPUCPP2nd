// 8.exercise.07.cpp
//
//  Read five names into a vector<string> name, then prompt the user for the
//  ages of the people named and store the ages in a vector<double> age. Then
//  print out the five (name[i],age[i]) pairs. Sort the names
//  (sort(name.begin(),name.end()) and print out the (name[i],age[i]) pairs.
//  The tricky part here is to get the age vector in the correct order to match
//  the sorted name vector. Hint: Before sorting name, take a copy and use that
//  to make a copy of age in the right order after sorting name.

#include "std_lib_facilities.h"

constexpr size_t name_no{5};

void get_names(vector<string>& name)
{
    cout << "Write five people names ...\n";
    for (size_t i = 0; i < name_no; ++i) {
        cout << ": ";
        string n;
        cin >> n;
        name.push_back(n);
    }
}

void get_ages(const vector<string>& name, vector<double>& age)
{
    cout << "Give me the ages of each person, please ...\n";
    for (string n : name) {
        cout << "How old is " << n << "? ";
        double a{0}; 
        while (!(cin >> a)) {
            cout << "Sorry, I don't understand you! How old is " << n << "? ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        age.push_back(a);
    }
} 

void print_pairs(const vector<string>& name, const vector<double>& age)
{
    size_t limit = name.size();
    for (size_t i = 0; i < limit; ++i)
        cout << name[i] << " is " << age[i] << " years old.\n";
}

size_t name_idx(const vector<string>& name, const string& n)
{
    size_t limit = name.size();
    for (size_t i = 0; i < limit; ++i)
        if (name[i] == n) return i;
    error("name_idx(): No element found!");
}

void sort_pairs(vector<string>& name, vector<double>& age)
{
    vector<string> orig_name{name};
    vector<double> orig_age{age};

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
    print_pairs(name, age);
    sort_pairs(name, age);
    print_pairs(name, age);

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
