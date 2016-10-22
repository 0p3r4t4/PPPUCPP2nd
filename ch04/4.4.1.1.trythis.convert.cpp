#include "std_lib_facilities.h"

int main()
{
    // Exchange rates as expressed by oanda.com on october 2016 the 13th
    constexpr double yen_dollar_rate {0.00964};
    constexpr double kroner_dollar_rate {0.12295};
    constexpr double pound_dollar_rate {1.22721};

    double amount {0};

    char currency {' '};

    cout << "Please enter an amount of money followed by a currency\n"
        "Currencies supported:\n"
        "y for Japanese Yen\n"
        "k for Norwegian Kroner\n"
        "p for British Pound\n";

    while (cin >> amount >> currency){
        if (currency == 'y')
            cout << amount << " Japanese Yen(s) equals to " 
                << amount*yen_dollar_rate << " US Dollar(s)\n";
        else if (currency == 'k')
            cout << amount << " Norwegian Kroner(s) equals to " 
                << amount*kroner_dollar_rate << " US Dollar(s)\n";
        else if (currency == 'p')
            cout << amount << " British Pound(s) equals to " 
                << amount*pound_dollar_rate << " US Dollar(s)\n";
        else 
            cout << "Sorry! Currency indicated by " 
                << currency << " is not supported.\n";
    }

    return 0;
}
