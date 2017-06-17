// 10.exercise.04.store.cpp
//
//  Modify the store_temp.cpp program from exercise 2 to include a temperature
//  suffix c for Celsius or f for Fahrenheit temperatures. Then modify the
//  temp_stats.cpp program to test each temperature, converting the Celsius
//  readings to Fahrenheit before putting them into the vector.
//
// COMMENTS
//

#include "std_lib_facilities.h"

const string of_name{"10.exercise.04.output"};
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
