// 10.exercise.08.cpp
//
//  Write a program that accepts two file names and produces a new file that is
//  the contents of the first file followed by the contents of the second; that
//  is, the program concatenates the two files.
//

#include "std_lib_facilities.h"

void add_content_from(string name, ofstream& ost)
{
    ifstream ist{name};
    if (!ist) error("Unable to open input file ", name);
    ist.exceptions(ist.exceptions()|ios_base::badbit);

    while (!ist.eof()) {
        char c = ist.get();     // char by char to preserve format. Unefficient.
        if (!ist.eof()) ost << c;   // avoid a trash character when EOF is reached
    }

    if (ist.eof()) ist.clear();     // File completely read
    if (ist.fail()) error("Not well formatted file ", name);    // Unlikely
}

void concat_files(const string& if_name_1, const string& if_name_2,
                  const string& of_name)
{
    ofstream ost{of_name};
    if (!ost) error("Unable to open output file ", of_name);

    add_content_from(if_name_1, ost);
    add_content_from(if_name_2, ost);
}

int main() 
try {
    string if_name_1{""};
    string if_name_2{""};
    string of_name{""};

    cout << "Concatenate two files.\n";
    cout << "First input file name: ";
    cin >> if_name_1;
    cout << "Second input file name: ";
    cin >> if_name_2;
    cout << "Output file name: ";
    cin >> of_name;

    cout << "Concatenating ...";
    concat_files(if_name_1, if_name_2, of_name);
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
