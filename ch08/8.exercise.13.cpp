// 8.exercise.13.cpp
//
//  Write a function that takes a vector<string> argument and returns a
//  vector<int> containing the number of characters in each string. Also find
//  the longest and the shortest string and the lexicographically first and
//  last string. How many separate functions would you use for these tasks?
//  Why?
//
// COMMENTS
//
//  Given that a function is assumed to do one logical action, there will be a
//  function for each task. So, summarizing, FIVE functions, at least. I would
//  assume we know about string::size() and do not need to implement a function
//  to get the length of a string.
//
//  I will implement each function to do just one thing, without taking
//  advantage of previous sorts or string length calculations.

#include "std_lib_facilities.h"

void print_i_vector(const string& label, const vector<int>& data)
// Only read arguments, so it safe to pass them by const-reference
{
    cout << label << ": { ";
    for (int i : data)
        cout << i << ' ';
    cout << "}\n";
}

void print_s_vector(const string& label, const vector<string>& data)
// Only read arguments, so it safe to pass them by const-reference
{
    cout << label << ": { ";
    for (string i : data)
        cout << "\"" << i << "\" ";
    cout << "}\n";
}

vector<int> gen_length_vector(const vector<string>& v)
// Generates a vector<int> with the lengths of strings on v.
{
    vector<int> lv;

    for (string s : v)
        lv.push_back(s.size());

    return lv;
}

vector<string> longest_string(const vector<string>& v)
// Returns the longest string(s). It returns a vector since v could contain
// various strings with the same size.
// Precondition:
//  v size must be at least 1. This is, v could not be empty.
{
   if (v.size() == 0) error("longest_string(): empty vector");

   size_t max{v[1].size()};    // Init max tracking to size of the first element

   // First vector traversal to find longest length
   for (string s : v)
       if (s.size() > max) max = s.size();

   // Second vector traversal to get longest strings
   vector<string> lv;
   for (string s: v)
       if (s.size() == max) lv.push_back(s);

   return lv;
}

vector<string> shortest_string(const vector<string>& v)
// Returns the shortest string(s). It returns a vector since v could contain
// various strings with the same size.
// Precondition:
//  v size must be at least 1. This is, v could not be empty.
{
   if (v.size() == 0) error("shortest_string(): empty vector");

   size_t min{v[1].size()};    // Init min tracking to size of the first element

   // First vector traversal to find shortest length
   for (string s : v)
       if (s.size() < min) min = s.size();

   // Second vector traversal to get shortest strings
   vector<string> sv;
   for (string s: v)
       if (s.size() == min) sv.push_back(s);

   return sv;
}

string first_string(vector<string> v)
// Returns the first lexicograpically string from v.
// We don't want to modify the argument, so we have two options:
//  - Pass by const-reference and make a copy inside
//  - Pass by value
// In each case we declare our intention to not modify the argument.
// Precondition:
//  v size must be at least 1. This is, v could not be empty.
{
    if (v.size() == 0) error("first_string(): empty vector");

    sort(v.begin(), v.end());
    return v[0];
}

string last_string(const vector<string>& v)
// Returns the last lexicograpically string from v.
// We don't want to modify the argument, so we have two options:
//  - Pass by const-reference and make a copy inside
//  - Pass by value
// In each case we declare our intention to not modify the argument.
// Precondition:
//  v size must be at least 1. This is, v could not be empty.
{
    if (v.size() == 0) error("last_string(): empty vector");

    vector<string> tmp{v};
    sort(tmp.begin(), tmp.end());
    return tmp[tmp.size()-1];
}

int main()
try
{
    vector<string> data{"one", "two", "three", "four", "five", "six", "seven"};

    print_s_vector("The strings vector is", data);
    print_i_vector("The corresponding lengths are", gen_length_vector(data));
    print_s_vector("The longest strings are", longest_string(data));
    print_s_vector("The shortest strings are", shortest_string(data));
    cout << "The first lexicographically string is: \""
         << first_string(data) << "\"\n";
    cout << "The last lexicographically string is: \""
         << last_string(data) << "\"\n";

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
