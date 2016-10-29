// 4.exercise.19.cpp
//
// Write a program where you first enter a set of name-and-value pairs, such as
// Joe 17 and Barbara 22. For each pair, add the name to a vector called names
// and the numbers to a vector called scores (in corresponding positions, so
// that if names[7]=="Joe" the scores[7]==17). Terminate input with NoName 0.
// Check that each name is unique and terminate with an error message if a name
// is entered twice. Write out all the (name, score) pairs (one per line).

#include "std_lib_facilities.h"

bool name_in(string name, vector<string> names)
{
    bool retval {false};

    for (string x : names)
        if (x == name) retval = true;

    return retval;
}

int main()
{
    vector<string> names;
    vector<int> scores;
    string name;
    int score;

    while ((cin >> name >> score) && (name != "NoName" || score != 0)) {
        if (name_in(name, names)) {
            cout << "Error: Name '" + name + "' introduced twice.\n";
            return 1;
        } else {
            names.push_back(name);
            scores.push_back(score);
        }
    }

    cout << "\nPairs introduced:\n";
    for (size_t i=0; i<names.size(); ++i)
        cout << '(' << names[i] << ", " << scores[i] << ")\n";

    return 0;
}
