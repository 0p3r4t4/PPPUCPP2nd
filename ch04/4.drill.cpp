#include "std_lib_facilities.h"

constexpr double CM_M_CONV_RATIO {0.01};
constexpr double IN_M_CONV_RATIO {2.54*CM_M_CONV_RATIO};
constexpr double FT_M_CONV_RATIO {12.0*IN_M_CONV_RATIO};
const vector<string> legal_units {"m", "cm", "in", "ft"};

bool is_legal_unit(string unit)
{
    bool is_legal {false};

    for (string legal_unit: legal_units)
        if (legal_unit == unit)
            is_legal = true;

    return is_legal;
}

double convert_to_mts(double amount, string units)
{
    double mts {0};

    if (units == "ft")
        mts = amount*FT_M_CONV_RATIO;
    else if (units == "in")
        mts = amount*IN_M_CONV_RATIO;
    else if (units == "cm")
        mts = amount*CM_M_CONV_RATIO;
    else
        mts = amount;

    return mts;
}

void print_legal_units()
{
    cout << "\tm for meters\n" << "\tcm for centimeters\n"
        << "\tin for inches\n" << "\tft for feet\n";
}

int main()
{
    double a {0}; 
    string unit {""};
    double mts {0};
    double smallest {0}; 
    double largest {0}; 
    double sum {0};
    int count {0};
    vector<double> values;
    
    cout.precision(15);

    cout << "Insert an amount followed by an unit string. Valid units are:\n";
    print_legal_units();

    while (cin >> a >> unit){
        if (is_legal_unit(unit)){
            mts = convert_to_mts(a, unit);
            if (count == 0){
                cout << a << unit << " (" << mts << "m) "
                    << " is the first number, the smallest and largest so far\n";
                smallest = mts;
                largest = mts;
            }
            else if (mts < smallest){
                cout << a << unit << " (" << mts << "m) "
                    << " the smallest so far\n";
                smallest = mts;
            }
            else if (mts > largest){
                cout << a << unit << " (" << mts << "m) "
                    << " the largest so far\n";
                largest = mts;
            }
            ++count;
            sum += mts;
            values.push_back(mts);
        }
        else {
            cout << unit << " is an ilegal unit in this program. Please use:\n";
            print_legal_units();
        }
    }

    cout << "Smallest value: " << smallest << " meters\n";
    cout << "Largest value: " << largest << " meters\n";
    cout << "Number of values: " << count << '\n';
    cout << "Sum of values: " << sum << " meters\n";

    cout << "Sorted lsit of values:\n";
    sort(values);
    for (double value: values)
        cout << '\t' << value << " meters\n";
    
    return 0;
}
