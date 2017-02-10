// 6.exercise.10.cpp
// 
// A permutation is an ordered subset of a set. For example, say you wanted to
// pick a combination to a vault. There are 60 possible numbers, and you need
// three different numbers for the combination. There are P(60,3) permutations
// for the combination, where P is defined by the formula
// 
//                a! 
//     P(a,b) = ------,
//              (a-b)!
// 
// where ! is used as a suffix factorial operator. For example, 4! is
// 4*3*2*1.
// 
// Combinations are similar to permutations, except that the order of the
// objects doesn't matter. For example, if you were making a "banana split"
// sundea and wished to use three different flavors of ice cream out of five
// that you had, you wouldn't care if you used a scoop of vanilla at the
// beginning or the end; you would still have used vanilla. The formula for
// combination is
// 
//              P(a,b)
//     C(a,b) = ------.
//                b!
// 
// Design a program that asks users for two numbers, asks them whether they
// want to calculate permutations or combinations, and prints out the result.
// This will have several parts. Do an analysis of the above requeriments.
// Write exactly what the program will have to do. Then go into design phase.
// Write pseudo code for the program, and break it into sub-components. This
// program should have error checking. Make sure that all erroneous inputs will
// generate good error messages
//
// Comments: See 6.exercise.10.md

#include "std_lib_facilities.h"

const string err_msg_pmul_with_negs = "called with negative integers.";
const string err_msg_nk_precon =
        "n and k parameters relationship precondition violated.";
const string err_msg_product_overflows = "integer multiplication overflows.";

int get_natural(const string& msg)
// Currently it only reads a integer without any check. It's an straight
// version to check other functions implementation.
{
    int n;
    cout << msg;
    cin >> n;
    return n;
}

bool check_pmul(int a, int b)
// Partial implementation not using larger integer type and only for
// positive integers, from https://www.securecoding.cert.org INT32C.
// Is its work to tell if multiplication could
// be performed or not.
// Precondition:
//      Both arguments must be positive.
{
    if (a < 0 || b < 0) 
        error("check_pmul(): " + err_msg_pmul_with_negs);

    if ( a > (numeric_limits<int>::max() / b) )
        return false;

    return true;
}

int perm(int n, int k)
// Calculates the k-permutations of n elements, what we call P(n, k).
// This is not done with the factorial formula expressed in the statement but
// with a limited product. See 6.exercise.10.md for details.
// If either n or k equals zero, the permutation is 1.
//
// Preconditions:
//      - n and k must be positive and n >= k. It's very unlikely to happen
//      otherwise since we assume it is assured by previous calls to
//      get_natural(), but to maintain good habits ...
{
    if (n < 0 || k < 0 || n < k)
        error("perm(): " + err_msg_nk_precon);

    if (n == 0 || k == 0) return 1;

    int prod = 1;

    for (int i = n-k+1; i <= n; ++i)
        if (check_pmul(prod, i))
            prod *= i;
        else
            error("perm(): " + err_msg_product_overflows);

    return prod;
}

int comb(int n, int k)
// Calculates the k-combinations of n elements, what we call C(n, k).
// This is not done with the factorial formula expressed in the statement but,
// being the k-combinations of n element also known as the binomial
// coefficient, using the multiplicative formual as stated in
// https://en.wikipedia.org/wiki/Binomial_coefficient#Multiplicative_formula
// If either n or k equals zero, the combination is 1.
//
// Preconditions:
//      - n and k must be positive and n >= k. It's very unlikely to happen
//      otherwise since we assume it is assured by previous calls to
//      get_natural(), but to maintain good habits ...
{
    if (n < 0 || k < 0 || n < k)
        error("perm(): " + err_msg_nk_precon);

    if (n == 0 || k == 0) return 1;

    int prod = 1;

    for (int i = 1; i <= k; ++i)
        if (check_pmul(prod, n+1-i))
            // Multiplying first by the numerator ensure the division to have
            // no reminder. 
            prod = (prod * (n+1-i)) / i;
        else
            error("comb(): " + err_msg_product_overflows);

    return prod;
}

int main(void)
try
{
    int setc = 0;
    int subc = 0;

    cout << "Calculator for k-permutation and k-combination of n elements\n"
            "without repetition. Be ware of large numbers, the calculator\n"
            "is very limited.\n";

    while (cin) {
        cout << endl;
        setc = get_natural("Set cardinality (n)? ");
        subc = get_natural("Subset cardinality (k)? ");
        
        cout << "  P(" << setc << ", " << subc << ") = " << perm(setc, subc) << '\n'; 
        cout << "  C(" << setc << ", " << subc << ") = " << comb(setc, subc) << '\n'; 
    }
    
    return 0;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch(...)
{
    cerr << "Oops! Unknown exception.\n";
    return 2; 
}
