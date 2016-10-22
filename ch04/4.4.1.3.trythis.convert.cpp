#include "std_lib_facilities.h"

int main()
{
    // Exchange rates as expressed by oanda.com on october 2016 the 13th
    constexpr double yen_dollar_rate {0.00964};
    constexpr double kroner_dollar_rate {0.12295};
    constexpr double pound_dollar_rate {1.22721};
    constexpr double yuan_dollar_rate {0.14858};

    double amount {0};

    char currency {' '};

    cout << "Please enter an amount of money followed by a currency\n"
        "Currencies supported:\n"
        "y for Japanese Yen\n"
        "k for Norwegian Kroner\n"
        "p for British Pound\n"
        "u for Chinese Yuan\n";

    while (cin >> amount >> currency){
        switch (currency){
            case 'y':
                cout << amount << " Japanese Yen(s) equals to " 
                    << amount*yen_dollar_rate << " US Dollar(s)\n";
                break;
            case 'k':
                cout << amount << " Norwegian Kroner(s) equals to " 
                    << amount*kroner_dollar_rate << " US Dollar(s)\n";
                break;
            case 'p':
                cout << amount << " British Pound(s) equals to " 
                    << amount*pound_dollar_rate << " US Dollar(s)\n";
                break;
            case 'u':
                cout << amount << " Chinese Yuan(s) equals to " 
                    << amount*yuan_dollar_rate << " US Dollar(s)\n";
                break;
            default:
                cout << "Sorry! Currency indicated by " 
                    << currency << " is not supported.\n";
                break;
        }
    }

    return 0;
}
