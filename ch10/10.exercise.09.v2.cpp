// 10.exercise.09.v2.cpp
//
//  Write a program that takes two files containing sorted whitespace-separated
//  words and merges them, preserving order.
//
// COMMENTS
//
//  Ok. Let's do this program as it is intended to be done. The first version
//  is a lazy one and do not take advantage of the strong precondition that is
//  input files to be already sorted.

#include "std_lib_facilities.h"

void merge_sorted_files(const string& if_name_1, const string& if_name_2,
                        const string& of_name)
{
    ifstream ist1{if_name_1};
    if (!ist1) error("Unable to open first input file ", if_name_1);
    ist1.exceptions(ist1.exceptions()|ios_base::badbit);

    ifstream ist2{if_name_2};
    if (!ist2) error("Unable to open second input file ", if_name_2);
    ist2.exceptions(ist2.exceptions()|ios_base::badbit);

    ofstream ost{of_name};
    if (!ost) error("Unable to open output file ", of_name);

    string w1, w2;
    ist1 >> w1;         // Read ahead to comply with while condition in case
    ist2 >> w2;         // of an empty file (or both)

    while (ist1 && ist2) {  // check for EOF. Error reading string is unlikely
        if (w1 < w2) {
            ost << w1 << ' ';
            ist1 >> w1;
        }
        else {
            ost << w2 << ' ';
            ist2 >> w2;
        }
    }

    if (!ist1) ost << w2;    // write dangling word from while-loop
    else ost << w1;
        
    // consume the remaining file
    // note the ' ' before the word, taking advantage of the dangling
    // word, to avoid a space to be printed at the end of the output file
    if (!ist1) for (string w; ist2 >> w;) ost << ' ' << w;
    else       for (string w; ist1 >> w;) ost << ' ' << w;
}

int main()
try {
    string if_name_1{""};
    string if_name_2{""};
    string of_name{""};

    cout << "Merge whitespace-separated sorted words from two files.\n";
    cout << "First input file name: ";
    cin >> if_name_1;
    cout << "Second input file name: ";
    cin >> if_name_2;
    cout << "Output file name: ";
    cin >> of_name;

    cout << "Merging ...";
    merge_sorted_files(if_name_1, if_name_2, of_name);
    cout << "\nDone.\n";
    return 0;
}
catch (exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Unknown exception!!!\n";
    return 2;
}
