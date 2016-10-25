// 4.exercise.12.cpp
//
// Modify the program described in the previous exercise to take an input value
// max and then find all the prime numbers from 1 to max.

#include "std_lib_facilities.h"

bool is_prime(int number, vector<int> primes)
{
    size_t i {0};
    bool is_prime {true};

    while (is_prime && i<primes.size()) {
        if (number%primes[i] == 0) 
            is_prime = false;
        ++i;
    }

    return is_prime;
}

int main()
{
    vector<int> primes;
    primes.push_back(2);
    
    cout << "Find prime numbers from 1 to? ";
    int max {0};
    cin >> max;

    for (int i=3; i <= max; ++i) {
        if (is_prime(i, primes))
            primes.push_back(i);
    }

    cout << "Primes between 1 and 100:\n";
    for (int x : primes)
        cout << x << '\n';
    
    return 0;
}
