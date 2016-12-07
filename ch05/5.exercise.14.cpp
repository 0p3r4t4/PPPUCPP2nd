// 5.exercise.14.cpp
//
// Read (day-of-the-week, value) pairs from standard input. For example:
//
//  Tuesday 24 Friday 56 Tuesday -3 Thursday 99
//
// Collect all the values for each day of the week in a vector<int>. Write out the
// values of the seven day-of-the-week vectors. Print out the sum of the values
// in each vector. Ignore illegal days of the week, such as Funday, but accept 
// common synonyms such as Mon and monday. Write out the number of rejected values.

#include "std_lib_facilities.h"

// Accepted names for days of the week, taking 0 as Sunday, 1 as Monday, and so
// on until 6 as Saturday.
static const vector<vector<string>> week_day_names = { 
        {"Sunday", "sunday", "SUNDAY", "Sun", "sun", "SUN"},
        {"Monday", "monday", "MONDAY", "Mon", "mon", "MON"},
        {"Tuesday", "tuesday", "TUESDAY", "Tue", "tue", "TUE"},
        {"Wednesday", "wednesday", "WEDNESDAY", "wed", "Wed", "WED"},
        {"Thursday", "thursday", "THURSDAY", "Thu", "thu", "THU"},
        {"Friday", "friday", "FRIDAY", "Fri", "fri", "FRI"},
        {"Saturday", "saturday", "SATURDAY", "Sat", "sat", "SAT"}
    };

// Exception messages
static const string ex_msg_bad_input = "The input is not well formed.";
static const string ex_msg_get_day_post = "get_day_by_name() post-condition violated.";
static const string ex_msg_size_mismatch = "print_results() pre-condition violated.";

int get_day_by_name(const string& name)
// Try to find name in week_day_names. If successful returns the index
// in week_day_names where the name has been found. Returns -1 otherwise.
// Post-condition:
//  returned value must be in [-1, 6]
{
    int index = -1;
    bool found = false;

    for (size_t i = 0; i < week_day_names.size() && !found ; ++i) {
        for (string n : week_day_names[i])
            if (n == name) {
                index = i;
                found = true;
            }
    }

    if (index < -1 || index > 6) throw runtime_error(ex_msg_get_day_post);
    return index;
}

void print_results(const vector<vector<int>>& values)
// Print the sum of the values in each vector in ints inside values
// Each vector of values corresponds to the day of the week as expressed in
// week_day_names.
// Pre-condition:
//  values and week_day_names msut be of the same size
{
    if (values.size() != week_day_names.size()) throw runtime_error(ex_msg_size_mismatch);

    for (size_t i = 0; i < values.size(); ++i) {
        cout << "Values for " << week_day_names[i][0] << ":\n\t";
        int sum = 0;
        for (int v : values[i]) {
            sum += v;
            cout << v << ' ';
        }
        cout << "\n\tSum of values for " << week_day_names[i][0] << " is " << sum << '\n';
    }
}

int main()
try
{
    vector<vector<int>> values_per_day (7);
    int rejected_count = 0;

    string name = " ";
    int value = 0;

    cout << "\nPlease insert pairs with a day of the week and a value. For example:\n\n"
         << "\tTuesday 23\t-or-\tSun -4\n\n"
         << "End you input with Ctrl-D or Ctrl-Z.\n\n";

    while (cin >> name >> value) {
        int day = get_day_by_name(name);
        if (day != -1) {
            values_per_day[day].push_back(value);
        }
        else {
            cout << "Rejected input '" << name << ' ' << value
                 << "' since " << name << " is not a day of the week.\n";
            ++rejected_count;
        }
    }
    
    if (cin.eof()) {
        cout << "\nNumber of rejected inputs: " << rejected_count << "\n\n";
        print_results(values_per_day);
    }
    else {
        throw runtime_error(ex_msg_bad_input);
    }

    return 0;
}
catch (exception& e) 
{
    cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Oops! Unknown exception.\n";
    return 2;
}
