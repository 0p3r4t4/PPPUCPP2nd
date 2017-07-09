// 10.exercise.09.cpp
//
//  Write a program that takes two files containing sorted whitespace-separated
//  words and merges them, preserving order.

#include "std_lib_facilities.h"

void get_words(const string& name, vector<string>& words)
{
    ifstream ist{name};
    if (!ist) error("Unable to open input file ", name);
    ist.exceptions(ist.exceptions()|ios_base::badbit);

    for (string s; ist >> s;)
        words.push_back(s);

    if (ist.eof()) ist.clear();     // File completely read
    if (ist.fail()) error("Not well formatted file ", name);    // Unlikely
}

void merge_files(const string& if_name_1, const string& if_name_2,
                  const string& of_name)
{
    ofstream ost{of_name};
    if (!ost) error("Unable to open output file ", of_name);

    vector<string> words;
    get_words(if_name_1, words);
    get_words(if_name_2, words);
    sort(words);

    for (size_t i = 0; i < words.size()-1; ++i)
        ost << words[i] << ' ';
    ost << words.back();
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
    merge_files(if_name_1, if_name_2, of_name);
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
