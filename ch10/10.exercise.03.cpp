// 10.exercise.03.cpp
//
//  Write a program that reads the data from raw_temps.txt created in exercise
//  2 into a vector and then calculates the mean and median temperatures in
//  your data set. Call this program temp_stats.cpp.
//
// COMMENTS
//
//  For the sake of standardization I will hold my naming schema, so the
//  program will be 10.exercise.03.cpp and the file it reads will be
//  10.exercise.02.output.
//
//  I will mantain temperature constraints from previous exercise as kind of
//  file format. Hour constraints are simply logical and enforceable.
//  
//  Got mean and median functions from 8.exercise.11.cpp
//  To calculate the median we must have a sorted vector. I can establish the
//  way to sort a vector of Registers by temperature defining a < operator. But
//  I don't see it enterely logical and somehow forced. Added to this,
//  readings_median() function should not modify the vector of Readings.

#include "std_lib_facilities.h"

const string if_name{"10.exercise.02.output"};

constexpr int min_hour{0};         // min hour in 24h format
constexpr int max_hour{23};        // max hour in 24h format
// Minimum and maximum temps to generate. There will be some extreme 
// conditions out there.
constexpr double min_temp{-100};   // ~ -73C
constexpr double max_temp{150};    // ~ 65C

struct Reading {            // a temperature reading
    int hour;               // hour after midnight [0:23]
    double temperature;     // in Fahrenheit
};

istream& operator>>(istream& is, Reading& rhs)
{
    int hour{0};
    double temp{0};

    is >> hour >> temp;

    if ((hour < min_hour) || (hour > max_hour) ||
        (temp < min_temp) || (temp > max_temp)) {
        is.clear(ios_base::failbit);
        return is;
    }

    rhs = Reading{hour, temp};

    return is;
}

void get_readings_from_file(vector<Reading>& v, const string& name)
{
    ifstream ist{name};
    if (!ist) error("Unable to open input file ", name);
    ist.exceptions(ist.exceptions()|ios_base::badbit);  // Force on badbit

    for (Reading r; ist >> r;)
        v.push_back(r);

    if (ist.eof()) ist.clear();     // File completely read
    if (ist.fail()) error("Not well formatted file ", name);
}

double readings_mean(const vector<Reading>& v)
{
    double sum{0};
    for (Reading r : v)
        sum += r.temperature;
    return sum/v.size();
}

double readings_median(const vector<Reading>& v)
// When the number of elements is even, the median is defined
// as the mean between the two most central values in the series.
{
    vector<double> values;

    // Extract temperatures from Readings and sort them
    for (Reading r : v)
        values.push_back(r.temperature);
    std::sort(values.begin(), values.end());

    if ((values.size()%2) == 1)               // odd number of elements
        return values[values.size()/2];       // the central element
    size_t idx{values.size()/2};
    return (values[idx-1]+values[idx])/2;     
}

int main()
try
{
    vector<Reading> readings;

    get_readings_from_file(readings, if_name);
    cout << "Got " << readings.size() << " temperature readings from file "
         << if_name << ".\n";
    cout << "Temperature mean: " << readings_mean(readings) << '\n';
    cout << "Temperature median: " << readings_median(readings) << '\n';
    return 0;
}
catch (exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Unknown exception!!\n";
    return 2;
}
