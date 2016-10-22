#include "std_lib_facilities.h"

int main()
{
    double total {0};

    cout << "Look your pocket!\nHow many pennies do you have? ";
    int pennies {0};
    cin >> pennies;
    total += pennies;

    cout << "How many nickels do you have? ";
    int nickels {0};
    cin >> nickels;
    total += nickels*5;
    
    cout << "How many dimes do you have? ";
    int dimes {0};
    cin >> dimes;
    total += dimes*10;

    cout << "How many quarters do you have? ";
    int quarters {0};
    cin >> quarters;
    total += quarters*25;

    cout << "How many half dollars do you have? ";
    int halfs {0};
    cin >> halfs;
    total += halfs*50;

    cout << "How many dollars do you have? ";
    int dollars {0};
    cin >> dollars;
    total += dollars*100;

    cout << "OK!\n";
    
    if (pennies != 0){
        cout << "You have " << pennies;
        if (pennies == 1)
            cout << " penny.\n";
        else
            cout << " pennies.\n";
    }

    if (nickels != 0){
        cout << "You have " << nickels;
        if (nickels == 1)
            cout << " nickel.\n";
        else
            cout << " nickels.\n";
    }

    if (dimes != 0){
        cout << "You have " << dimes;
        if (dimes == 1)
            cout << " dime.\n";
        else
            cout << " dimes.\n";
    }

    if (quarters != 0){
        cout << "You have " << quarters;
        if (quarters == 1)
            cout << " quarter.\n";
        else
            cout << " quarters.\n";
    }

    if (halfs != 0){
        cout << "You have " << halfs;
        if (halfs == 1)
            cout << " half dollar.\n";
        else
            cout << " half dollars.\n";
    }

    if (dollars != 0){
        cout << "You have " << dollars;
        if (dollars == 1)
            cout << " dollar.\n";
        else
            cout << " dollars.\n";
    }

    cout << "The value of all your coins is $" << total/100 << " ("
        << total << " cents)\n";

    return 0;
    
}
