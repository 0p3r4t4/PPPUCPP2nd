// 4.exercise.14.cpp
//
// Modify the program described in the previous exercise to take an input value
// max and then find all prime numbers from 1 to max.
//
// Previous exercise:
//
// Create a program to find all the prime numbers between 1 and 100. There is
// a classic method for doing this, called "Sieve of Eratosthenes". If you
// don't know that method, get on the web and look it up. Write your program
// using this method.
//
// Comments:
//  The method (as stated by wikipedia at
//  https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) is:
//      1 - Create a list of consecutive integers from 2 through n.
//      2 - Initially, let p equal 2, the smallest primer number.
//      3 - Enumerate the multiplies of p by counting to n from 2p in increments
//      of p, and mark them in the list. The p itself should not be marked.
//      4 - Find the first number greater than p in the list that is not marked.
//      If there was not a such number, stop. Otherwise, let p now equal this
//      new number an repeat from step 3.

#include "std_lib_facilities.h"

int main()
{
    cout << "Find prime numbers from 1 to? ";
    int max {0};
    cin >> max;
    
    // (step 1) Use a vector as a list of numbers (its indexes)
    // and use the values contained as markers (0 not marked, 1 marked).
    // As stated in page 118, this vector will have "max+1" elements
    // initialized to zero. 
    vector<int> primes(max+1);

    for (int i=2; i <= max; ++i) {
        // (step 2 and 4) If not marked, this is the next prime (initially 2, as step 2 of the
        // method).
        if ( primes[i] == 0 ){
            // step 3
            int m {i+i};
            while (m <= max) {
                primes[m] = 1;
                m += i;
            }
        }
    }

    cout << "Primes between 1 and " << max << ":\n";
    for (int i=2; i <= max; ++i)
        if (primes[i] == 0) cout << i << '\n';
    
    return 0;
}
