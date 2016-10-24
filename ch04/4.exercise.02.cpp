// 4.exercise.02.cpp
//
// If we define the median of a sequence as "a numbet do that exactly as many
// elements come before it in the sequence as come after it", fix the program
// in 4.6.3 do that it always prints out a median. Hint: A median need not to
// be an element of the sequence.

#include "std_lib_facilities.h"

int main()
{
    vector<double> temps;
    for (double temp; cin >> temp; )
        temps.push_back(temp);

    double sum {0};
    for (auto x : temps) sum += x;
    cout << "Average temperature: " << sum/temps.size() << '\n';

    sort(temps);
    double median {0};
    int idx = temps.size()/2;
    if (temps.size()%2 == 0)
        median = (temps[idx-1]+temps[idx])/2;
    else
        median = temps[idx];

    cout << "Median temperature: " << median << '\n';
}
