// 4.exercise.17.cpp
//
// Write a program that finds the min, max and the mode of a sequence of
// strings.

#include "std_lib_facilities.h"

int main()
{
    vector<string> sample;

    cout << "Write a series of strings (end the input with Ctrl+D): ";
    string element {""};
    while (cin >> element)
        sample.push_back(element);

    if (sample.size() != 0) {
        // Vector to store different values from sample
        vector<string> values;
        // Vector to store the times each element from values appears in sample
        vector<int> times;
        
        // A sort sample simplifies the problem
        sort(sample);
        // First element in sample
        values.push_back(sample[0]);
        times.push_back(1);
        // Get every unique element and the times ir appears in sample
        for (size_t i=1; i<sample.size(); ++i) {
            if (sample[i] == sample[i-1]) {
                ++times[times.size()-1];
            } else {
                values.push_back(sample[i]);
                times.push_back(1);
            }
        }

        // min nad max
        string min {sample[0]};
        string max {sample[0]};
        for (string s : sample) {
            if (s < min) min = s;
            if (s > max) max = s;
        }
        // Time to get the max in times
        // What if there are more than a mode (various elements that appers
        // the same amount of times, and that amount is the maximum)? I think
        // that we still don't know enough to solve that situation in
        // an efficent way.
        int max_times {0};
        int idx {0};
        for (size_t i=0; i<times.size(); ++i) {
            if (times[i] > max_times) {
                max_times = times[i];
                idx = i;
            }
        }

        cout << "The min string in the sample is: \"" << min << "\"\n";
        cout << "The max string in the sample is: \"" << max << "\"\n";
        cout << "The mode of the sample is \"" << values[idx] << "\" with " 
            << times[idx] << " appareances.\n";

    } else {
        cout << "No data introduced.\n";
    }

    return 0;
}

