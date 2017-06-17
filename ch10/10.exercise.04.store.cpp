// 10.exercise.04.store.cpp
//
//  Modify the store_temp.cpp program from exercise 2 to include a temperature
//  suffix c for Celsius or f for Fahrenheit temperatures. Then modify the
//  temp_stats.cpp program to test each temperature, converting the Celsius
//  readings to Fahrenheit before putting them into the vector.
//
// COMMENTS
// 
//  The key to this exercise is wheter or not modify the Reading struct to hold
//  the units of the temperature. I decided not to modify it, so
//  random_reading() is not modified either. So, where to randomize writing the
//  Reading on Fahrenheit or Celsius? I want to honour min and max temperatures
//  as previously defined for Fahrenheit and since random_reading() is
//  unmodified, the place to convert some of them to Celsius is when they are
//  written to file. I could modify operator <<, but it feels strange to me to
//  do so; operators on a custom type should contemplate only the type. That's
//  my opinion and it will be so at least until we learn how to customize
//  output.  So operator << doesn't make sense for this exercise and the
//  Fahrenhit/Celsius distinction will be done in write_readings_file().
//
//  I borrow ftoc() function from 5.exercise.06.cpp. There are "magic" numbers
//  on it, but since they're fixed values on the formula for conversion I don't
//  feel the need to make them symbolic constants.

#include "std_lib_facilities.h"

const string of_name{"10.exercise.04.output"};
constexpr size_t no_readings{63};
constexpr int min_hour{0};         // min hour in 24h format
constexpr int max_hour{23};        // max hour in 24h format
// Minimum and maximum temps to generate. There will be some extreme 
// conditions out there.
constexpr double min_temp{-100};   // ~ -73C
constexpr double max_temp{150};    // ~ 65C
constexpr int fahrenheit{0};
constexpr int celsius{1};
constexpr char fahrenehit_suffix{'f'};
constexpr char celsius_suffix{'c'};

struct Reading {            // a temperature reading
    int hour;               // hour after midnight [0:23]
    double temperature;     // in Fahrenheit
};

double ftoc(double f)
// Converts Fahrenheit to Celsius
// pre-condition: Fahrenheit temperature equal or greater than -459.67
//                (absolute zero)
{
    if (f < -459.67) error("Indicated temperature below absolute zero!");
    return (f-32.0)*5/9;
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
    std::uniform_int_distribution<int> unit_dist(fahrenheit, celsius);

    for (size_t i = 0; i < no_readings; ++i) {
        int unit = unit_dist(engine);
        Reading reading{random_reading(engine)};
        ost << reading.hour << ' ';
        if (unit == fahrenheit)
            ost << std::fixed << std::setprecision(2)
                << reading.temperature << fahrenehit_suffix << '\n';
        else
            ost << std::fixed << std::setprecision(2)
                << ftoc(reading.temperature) << celsius_suffix << '\n';
    }
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
