// 8.exercise.12.cpp
//
//  Improve print_until_s() from §8.5.2. Test it. What makes a good set of test
//  cases? Give reasons. Then, write a print_until_ss() that prints until it
//  sees a second ocurrence of its quit argument.
//
// COMMENTS
//
//  Since we don't modify the parameter v we can pass it by const-reference and
//  the same goes about the quit parameter.
//
//  Set to test ...
//    Test with empty vectors and strings.
//    Test with quit string being the first or the last element of the vector.
//    Test with vectors not containing quit string.
//    Test with variables (or constants) as arguments.

#include "std_lib_facilities.h"

void print(const vector<string>& v, const string& quit, const string& which)
{
    cout << "Printing vector { ";
    for (string s : v) cout << s << ' ';
    cout << "} UNTIL the " << which << " appareance of '" << quit << "' ...\n";
}

void print_until_s(const vector<string>& v, const string& quit)
{
    print(v, quit, "first");    // Added for test information
    for (string s : v) {
        if (s == quit) return;
        cout << '\t' << s << '\n';
    }
}

void print_until_ss(const vector<string>& v, const string& quit)
{
    print(v, quit, "second");   // Added for test information
    bool seen{false};           // Tracks first occurrence of quit
    for (string s : v) {
        if (s == quit)
            if (seen) return;
            else seen = true;
        cout << '\t' << s << '\n';
    }
}

int main()
try
{
    vector<string> test_data{"1", "2", "3", "4", "5"};
    const vector<string> test_data_c{};
    string quit{"exit"};
    
    cout << "\nprint_until_s() tests:\n\n";
    print_until_s({"Hi!", "Hello", "Bye", "quit", "Until tomorrow"}, "quit");
    print_until_s(test_data, "");
    print_until_s(test_data_c, quit);
    print_until_s({"quit", "Hello", "Bye", "quit", "Until tomorrow"}, "quit");
    print_until_s({"Hi!", "Hello", "Bye", "quit", quit}, quit);

    cout << "\nprint_until_ss() tests:\n\n";
    print_until_ss({"Hi!", "Hello", "Bye", "quit", "Until tomorrow", "quit",
                    "No more"}, "quit");
    print_until_ss({"Hi!", "Hello", quit, "Bye", "exit", "quit", quit}, quit);

    return 0;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch(...)
{
    cerr << "Unknown exception!!\n";
    return 2;
}
