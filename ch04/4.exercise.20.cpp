// 4.exercise.20.cpp
//
// Modify the program from exercise 19 so that when you enter a name, the
// program will output the corresponding score or 'name not found'.

#include "std_lib_facilities.h"

bool name_in(string name, vector<string> names) {

    bool retval {false};

    for (string x : names)
        if (x == name) retval = true;

    return retval;
}

int find_name(string name, vector<string> names)
{
    int idx {-1};
    size_t i {0};

    while ((idx == -1) && (i < names.size())) {
        if (names[i] == name) idx = i;
        ++i;
    }

    return idx;
}

int main()
{
    vector<string> names;
    vector<int> scores;
    string name;
    int score;

    cout << "Insert pairs of name and score such as:\nJohn 27\nEnd input with"
        << " the pair NoName 0.\n";
    while ((cin >> name >> score) && (name != "NoName" || score != 0)) {
        if (name_in(name, names)) {
            cout << "Error: Name '" + name + "' introduced twice.\n";
            return 1;
        } else {
            names.push_back(name);
            scores.push_back(score);
        }
    }

    int idx {0};
    cout << "Type a name a get the score: ";
    while (cin >> name) {
        idx = find_name(name, names);
        if (idx == -1)
            cout << "Error: name not found\n";
        else
            cout << name << "'s score is " << scores[idx] << '\n';
        cout << "Type a name a get the score: ";
    }

    return 0;
}
