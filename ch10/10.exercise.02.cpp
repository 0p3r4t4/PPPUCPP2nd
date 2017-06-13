// 10.exercise.02.cpp
//
//  Write a program that creates a file of data in the form of the temperature
//  Reading type defined in §10.5. For testing, fill the file with at least 50
//  "temperature readings". Call this program store_temps.cpp and the file it
//  creates raw_temps.txt.
//
// COMMENTS
//
//  For the sake of standardization I will hold my naming schema, do the
//  program will be 10.exercise.02.cpp and the file it creates will be
//  10.exercise.02.output.
//
//  I approach this exercise as a random-esque file generator. I borrow the
//  C++11 way of doing randomization from 5.exercise.13.cpp, and add
//  std::uniform_real_distribution for doubles. Take for sure I barely have
//  idea of what I'm doing, but it seems to work.
//
//  It will be an improvement to prompt the user for the parameters, as number
//  of readings or min and max temperatures to observe.

#include "std_lib_facilities.h"

const string of_name{"10.exercise.02.output"};
constexpr size_t no_readings{50};
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

ostream& operator<<(ostream& os, const Reading& rhs)
{
    os << rhs.hour << ' ' 
       << std::fixed << std::setprecision(2) << rhs.temperature;
    return os;
}

Reading random_reading(std::default_random_engine& engine)
{
    std::uniform_int_distribution<int> hour_dist(min_hour, max_hour);
    std::uniform_real_distribution<double> temp_dist(min_temp, max_temp);

    return Reading{hour_dist(engine), temp_dist(engine)};
}

void write_readings_file(const string& file)
{
    ofstream ost{file};
    if (!ost) error("Can't open output file ", file);

    std::default_random_engine engine(std::time(nullptr));

    for (size_t i = 0; i < no_readings; ++i)
        ost << random_reading(engine) << '\n';
}

int main()
try
{
    write_readings_file(of_name);
    cout << no_readings << " temperature readings written in file "
         << of_name << '\n';
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
