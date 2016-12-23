// 6.exercise.04.cpp
//
// Define a class Nmae_value that holds a string and a value. Rework exercise 19 in
// chapter 4 to use vectoe<Name_value> instead of two vectors.
//
//  4.exercise.19.cpp
//
//  Write a program where you first enter a set of name-and-value pairs, such as
//  Joe 17 and Barbara 22. For each pair, add the name to a vector called names
//  and the numbers to a vector called scores (in corresponding positions, so
//  that if names[7]=="Joe" the scores[7]==17). Terminate input with NoName 0.
//  Check that each name is unique and terminate with an error message if a name
//  is entered twice. Write out all the (name, score) pairs (one per line).
//  
// Comments:
//
//  Keeping on the termination conditions from the original problem statement,
//  there are not much to do but define the new class and make the chages derived
//  from its use.
//  No exceptions and no more detailed input management.

#include "std_lib_facilities.h"

class Name_value {
    public:
        string name;
        int value;
};

bool name_in(string name, vector<Name_value> pairs)
{
    bool retval {false};

    for (Name_value x : pairs)
        if (x.name == name) retval = true;

    return retval;
}

int main()
{
    vector<Name_value> pairs;
    string name;
    int value;

    while ((cin >> name >> value) && (name != "NoName" || value != 0)) {
        if (name_in(name, pairs)) {
            cerr << "Error: Name '" + name + "' introduced twice.\n";
            return 1;
        } else {
            pairs.push_back(Name_value {name, value});
        }
    }

    cout << "\nPairs introduced:\n";
    for (size_t i = 0; i < pairs.size(); ++i)
        cout << '(' << pairs[i].name << ", " << pairs[i].value << ")\n";

    return 0;
}
