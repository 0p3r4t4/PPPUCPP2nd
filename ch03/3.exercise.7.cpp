#include "std_lib_facilities.h"

int main()
{
    cout << "Enter three strings: ";
    string val1 {" "};
    string val2 {" "};
    string val3 {" "};
    cin >> val1 >> val2 >> val3;

    string min {" "};
    string mid {" "};
    string max {" "};

    if (val1 < val2)
        if (val1 < val3){
            min = val1;
            if (val2 < val3){
                mid = val2;
                max = val3;
            } else {
                mid = val3;
                max = val2;
            }
        }
        else {
            min = val3; 
            mid = val1;
            max = val2;
        }
    else 
        if (val2 < val3){
            min = val2;
            if (val1 < val3){
                mid = val1;
                max = val3;
            } else {
                mid = val3;
                max = val1;
            }
        }
        else {
            min = val3; 
            mid = val2;
            max = val1;
        }

    cout << min << ", " << mid << ", " << max << '\n';
}
    
