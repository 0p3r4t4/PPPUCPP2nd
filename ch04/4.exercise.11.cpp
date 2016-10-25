// 4.exercise.11.cpp
//
// Create a program to find all the prime numbers between 1 and 100. One way to
// do this is to write a function that will check if a number is prime (i.e.,
// see if the number can be divided by a prime number smaller than itself)
// using a vector of primes in order (so that if the vector is called primes,
// primes[0]==2, primes[1]==3, primes[2]==5, etc.). Then write a loop that goes
// from 1 to 100, checks each number to see if it is a prime, and stores each
// prime found in a vector. Write another loop that lists the primes you found.
// You might check your result by comparing your vector of prime numbers with
// primes. Consider 2 the first prime.
//
// Comments:
//  I don't feel confortable using a precalc vector of primes to calculate
//  those primes again, as I understand from the problem text. So I will
//  generate the primes vector on the go and reutilize it on further
//  iterations. 

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

    for (int i=3; i <= 100; ++i) {
        if (is_prime(i, primes))
            primes.push_back(i);
    }

    cout << "Primes between 1 and 100:\n";
    for (int x : primes)
        cout << x << '\n';
    
    return 0;
}
