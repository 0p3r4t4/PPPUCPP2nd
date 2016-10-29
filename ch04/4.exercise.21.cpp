// 4.exercise.21.cpp
//
// Modify the program from exercise 19 so that when you enter an integer, the
// program will output all the names with that score or score not found.

#include "std_lib_facilities.h"

bool name_in(string name, vector<string> names) {

    bool retval {false};

    for (string x : names)
        if (x == name) retval = true;

    return retval;
}

// find_score search for first occurence of score in 
// scores vector, beggining on index idx.
int find_score(int score, vector<int> scores, size_t begin)
{
    int idx {-1};
    size_t i {begin};

    while ((idx == -1) && (i < scores.size())) {
        if (scores[i] == score) idx = i;
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

    cout << "Type a score to show who has it: ";
    while (cin >> score) {
        vector<int> idxs;
        int idx = find_score(score, scores, 0);
        while (idx != -1) {
            idxs.push_back(idx);
            idx = find_score(score, scores, idx+1);
        }
        size_t idxs_size = idxs.size(); 
        // Artificially complex to beautify output
        if (idxs_size == 0) {
            cout << "Error: score not found\n";
        } else if (idxs_size == 1) {
            cout << "Only " << names[idxs[0]] << " has scored " << score << '\n';
        } else {
            for (size_t i=0; i<idxs_size-2; ++i)
                cout << names[idxs[i]] << ", ";
            cout << names[idxs[idxs_size-2]] << " and "
                << names[idxs[idxs_size-1]] << " have scored " << score << '\n';
        }
    
        cout << "Type a score to show who has it: ";
    }

    return 0;
}
