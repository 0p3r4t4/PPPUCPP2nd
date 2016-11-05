// 5.7.try_this.2.cpp
//
// Look it up. Check some information sources to pick good values for the
// min_temp (the "minimum temperature") and max_temp (the "maximum
// temperature") constants for our program. Those values will determine the
// limits and usefulness of our program.
//
// Comments:
//  I suppose that we're working with Farenheit temperatures.
//  Depending on the field of application of our program, the max_temp and
//  min_temp constants could be more restrained, I guess, but I choose values
//  wide enough for us as a species.
//
//  This program, in contrast with previous 'Try this' seems to be optimized to
//  do the calculations on the fly, without storing the values on a container.
//  My unoptimized solution to this would be to get rid of constants and add an
//  if-statement on the for-loop as:
//
//    for (double temp; cin >> temp; ) {
//        ++no_of_temps;
//        sum += temps;
//        if (no_of_temps == 1) {
//            high_temp = temp;
//            low_temp = temp;
//        } else {
//            if (temp > high_temp) high_temp = temp;
//            if (temp < low_temp) low_temp = temp;
//        }
//    }
//
//  This way we can ignore temperature units and logical upper and lower limits to
//  the temperature values. Of course, it's a test in each iteration of the
//  for-loop, a test to be true only the first time. Not too much efficient
//  code.

#include "std_lib_facilities.h"

constexpr double max_temp {9569.93};       // Temperature (ºF) from the Sun's photosphere.
constexpr double min_temp {-459.67};       // Absolute zero (ºF)

int main()
{
    double sum = 0;
    double high_temp = min_temp;
    double low_temp = max_temp;
    int no_of_temps = 0;

    for (double temp; cin >> temp; ) {
        ++no_of_temps;
        sum += temp;
        if (temp > high_temp) high_temp = temp;
        if (temp < low_temp) low_temp = temp;
    }

    cout << "High temperature: " << high_temp << '\n';
    cout << "Low temperature: " << low_temp << '\n';
    cout << "Average temperature: " << sum/no_of_temps << '\n';
}
