// 4.exercise.03.cpp
//
// Read a sequence of double values into a vector. Think of each value as the
// distance between two cities along a given route. Compute and print the total
// distance (the sum of all distances). Find and print the smallest and
// greatest distance between two neighboring cities. Find and print the mean
// distance between two neighboring cities.

#include "std_lib_facilities.h"

int main()
{
    vector<double> distances;

    cout << "Please, insert distances between neighboring cities along a route:\n";

    for (double distance; cin >> distance; )
        distances.push_back(distance);

    if (distances.size()==0) error("No distances inserted!");
    
    double min {distances[0]};
    double max {distances[0]};
    double total {0};

    for (double d : distances) {
        if (d<min) min = d;
        if (d>max) max = d;
        total += d;
    }

    cout << "Total route distance: " << total << '\n';
    cout << "Smallest distance between two neighboring cities: " << min << '\n';
    cout << "Greatest distance between two neighboring cities: " << max << '\n';
    cout << "The mean distance between neighboring cities is "
        << total/distances.size() << '\n';

    return 0;
}
