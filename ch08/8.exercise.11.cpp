// 8.exercise.11.cpp
//
//  Write a function that finds the smallest and the largest element of a
//  vector argument and also computes the mean and the median. Do not use
//  global variables. Either return a struct containing the results or pass
//  them back through reference arguments. Which of the two ways of returning
//  several result values do you prefer and why?
//
// COMMENTS
//
//  Since to calculate the median we must sort the numbers, we can take
//  advantage of that to get the smallest and largest element.
//
//  Median calculation differs on odd or even number of elements. Must test
//  that.
//
//  I prefer:
//      stats get_stats(const vector<double>& v);
//      my_stats = get_stats(data);
//  than:
//      void get_stats(const vector<double>& v, double& max, double& min,
//          double& mean, double& median);
//      get_stats(data, max, min, mean, median);
//
//  More concise and smaller number of parameters and arguments. Less prone to
//  errors, I think.
//

#include "std_lib_facilities.h"

struct Stats {
    double max{0};
    double min{0};
    double mean{0};
    double median{0};
};

void print(const string& label, const vector<double>& data)
// Only read arguments, so it safe to pass them by const-reference
{
    cout << label << ": { ";
    for (double d : data)
        cout << d << ' ';
    cout << "}\n";
}

void print_stats(const Stats& stats)
{
    cout << "Statistics:\n\tMax: " << stats.max << '\n'
         << "\tMin: " << stats.min << '\n'
         << "\tMean: " << stats.mean << '\n'
         << "\tMedian: " << stats.median << '\n';
}

double mean(const vector<double>& v)
{
    double sum{0};
    for (double d : v)
        sum += d;
    return sum/v.size();
}

double median(const vector<double>& v)
// The vector must be sorted
{
    if ((v.size()%2) == 1)          // odd number of elements
        return v[v.size()/2];   // the central element
    size_t idx{v.size()/2};
    return (v[idx-1]+v[idx])/2;
}

Stats get_stats(const vector<double>& v)
// Do not modify the passed vector
{
    vector<double> tmp{v};  // temporal vector to work
    
    sort(tmp.begin(), tmp.end());   // sort the work vector
    Stats stats;
    stats.min = tmp[0];
    stats.max = tmp[tmp.size()-1];
    stats.mean = mean(tmp);
    stats.median = median(tmp);
    
    return stats;
}

int main()
try {
    // Mean: 5.28571, Median: 6;
    vector<double> odd_data{3, 9, 1, 8, 7, 6, 3};
    // Mean: 4.75, Median: 4.5
    vector<double> even_data{4, 1, 9, 8, 5, 3, 2, 6};

    print("Odd (number of elements) data", odd_data);
    print_stats(get_stats(odd_data));
    cout << '\n';
    
    print("Even (number of elements) data", even_data);
    print_stats(get_stats(even_data));
    cout << '\n';

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
