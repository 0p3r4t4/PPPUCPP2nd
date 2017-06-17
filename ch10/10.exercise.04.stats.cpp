// 10.exercise.04.stats.cpp
//
//  Modify the store_temp.cpp program from exercise 2 to include a temperature
//  suffix c for Celsius or f for Fahrenheit temperatures. Then modify the
//  temp_stats.cpp program to test each temperature, converting the Celsius
//  readings to Fahrenheit before putting them into the vector.
//
// COMMENTS
//
//  This time, and it seems contrary to the criterion exposed on the first part
//  of the problem, the transformation will take place on the Reading >>
//  operator. I consider it as a representation change, where we read
//  temperatures with distinct scales and are able to store them on a
//  "normalized" form (Fahrenheit scale, in this case).
//
//  I borrow ctof() function from 5.exercise.06.cpp. There are "magic" numbers
//  on it, but since they're fixed values on the formula for conversion I don't
//  feel the need to make them symbolic constants.

#include "std_lib_facilities.h"

const string if_name{"10.exercise.04.output"};

constexpr int min_hour{0};         // min hour in 24h format
constexpr int max_hour{23};        // max hour in 24h format
// Minimum and maximum temps to generate. There will be some extreme 
// conditions out there.
constexpr double min_temp{-100};   // ~ -73C
constexpr double max_temp{150};    // ~ 65C
constexpr double celsius_absolute_zero{-273.15};
constexpr char fahrenheit_suffix{'f'};
constexpr char celsius_suffix{'c'};

struct Reading {            // a temperature reading
    int hour;               // hour after midnight [0:23]
    double temperature;     // in Fahrenheit
};

double ctof(double c)
// Converts Celsius to Fahrenheit
// pre-condition: Celsius temperature equal oe greater than 273.15 (absolute
//                zero)
{
    if (c < celsius_absolute_zero)
        error("Indicated temperature below absolute zero!");
    return c*9.0/5+32;      // Conversion formula
}

istream& operator>>(istream& is, Reading& rhs)
{
    int hour{0};        // If not default initialized with valid values,
    double temp{0};     // the read that provokes EOF will be masked by 
    char unit{'f'};     // setting only failbit on the checks before returning

    is >> hour >> temp >> unit;

    if (is.eof()) return is;    // Do not let all to default initialization 
                                // of read variables

    if ((hour < min_hour) || (hour > max_hour) ||
        ((unit != fahrenheit_suffix) && (unit != celsius_suffix))) {
        is.clear(ios_base::failbit);
        return is;
    }

    if (unit == celsius_suffix) temp = ctof(temp);  // Normalize to Fahrenheit
    // We couldn't check if the temperature is within range before normalizing
    if ((temp < min_temp) || (temp > max_temp)) {
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
    cout << "Temperature mean: " << readings_mean(readings) << " ºF\n";
    cout << "Temperature median: " << readings_median(readings) << " ºF\n";
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
