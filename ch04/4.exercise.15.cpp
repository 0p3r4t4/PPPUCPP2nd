// 4.exercise.15.cpp
//
// Write a program that takes an input value n and then finds the first
// n primes.
//
// Comments:
//  I don't think that the Sieve of Eratosthenes is useful in this problem.
//  We need to simply iterate over natural numbers testing them being prime or
//  not, until we found the desired number of primes. So the solution from
//  exercise 12 fits better.

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
    
    cout << "How many prime numbers do you want to find? ";
    int limit {0};
    cin >> limit;

    int i {3};
    int count {1};

    while (count < limit) {
        if (is_prime(i, primes)) {
            primes.push_back(i);
            ++count;
        }
        ++i;
    }

    cout << "The " << limit << " first prime numbers:\n";
    for (int x : primes)
        cout << x << '\n';
    
    return 0;
}
