#include "std_lib_facilities.h"

int main()
{
    cout << "Enter three integer values: ";
    int val1 {0};
    int val2 {0};
    int val3 {0};
    cin >> val1 >> val2 >> val3;

    int min {0};
    int mid {0};
    int max {0};

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
    
