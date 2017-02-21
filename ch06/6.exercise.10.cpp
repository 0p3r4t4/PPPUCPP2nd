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
const string err_msg_nk_precon = "n and k parameters relationship precondition violated.";
const string err_msg_product_overflows = "integer multiplication overflows.";
const string err_msg_eoi = "Unexpected end of input.";
const string err_msg_main_bad_option = "Bad option parsing.";

const string msg_setc_get = "Set cardinality (n)? ";
const string msg_subc_get = "Subset cardinality (n)? ";
const string msg_calc_option = "What type of calculation do you want? (p)ermutation, (c)ombination or (b)oth? ";
const string msg_again_option = "Do you want to perform a new calculation (y/n)? ";

static const vector<char> calc_options = {'p', 'P', 'c', 'C', 'b', 'B'};
static const vector<char> again_options = {'y', 'Y', 'n', 'N'};

bool is_in(const char c, const vector<char> v)
// Returns true if character c is contained in vector<char> v and returns false
// otherwise.
{
    for (char cv : v) 
        if (cv == c) return true;

    return false;
}

int get_natural(const string& msg)
// Asks the user (printing the message msg) for a positive integer.
// It keeps asking until a positive integer is entered or EOF is reached
// or signaled, in which case it throws an error.
// Tries to read an integer ignoring the rest of the line, whatever it is, and
// despite that read has been successful or not.
{
    int n = 0;
    
    for (;;) {
        cout << msg;
        cin >> n;
        if (cin) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (n < 0)
                cout << n << " is not a positive integer.\n";
            else
                return n;
        }
        else if (!cin.eof()) {
            cout << "Your input is not a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            error("get_natural(): " + err_msg_eoi);
        }
    }
}

char get_option(const string& msg, const vector<char> v)
// Asks the user (printing the message msg) for a char value (option).
// It keeps asking until the answer is a char value that is present in vector
// v or EOF is reached or signales, in which case it throws and error.
// Only the first character of a line is considered, ignoring the rest of it.
{
    char c = 0;
    for (;;) {
        cout << msg;
        cin >> c;
        if (cin) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (is_in(c, v))
                return c;
            else
                cout << c << " is not a valid option.\n";
        }
        else {
            // If cin fails reading a char, I guess the only way is to
            // have reached end of input. I could be mistaken, though.
            error("get_option(): " + err_msg_eoi);
        }
    }
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
// coefficient, using the multiplicative formula as stated in
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
    char option = ' ';

    cout << "Calculator for k-permutation and k-combination of n elements\n"
            "without repetition. Beware of large numbers, the calculator\n"
            "is very limited.\n";

    while (cin) {
        cout << endl;
        setc = get_natural(msg_setc_get);
        subc = get_natural(msg_subc_get);
        
        option = get_option(msg_calc_option, calc_options);
        switch(option) {
            case 'p':
            case 'P':
                cout << "  P(" << setc << ", " << subc << ") = "
                     << perm(setc, subc) << '\n'; 
                break;
            case 'c':
            case 'C':
                cout << "  C(" << setc << ", " << subc << ") = "
                     << comb(setc, subc) << '\n'; 
                break;
            case 'b':
            case 'B':
                cout << "  P(" << setc << ", " << subc << ") = "
                     << perm(setc, subc) << '\n'; 
                cout << "  C(" << setc << ", " << subc << ") = "
                     << comb(setc, subc) << '\n'; 
                break;
            default:
                error("main(): " + err_msg_main_bad_option);
        }

        option = get_option(msg_again_option, again_options);
        if (option == 'n' || option == 'N') break;
    }

    cout << "\nBye!\n\n";
    
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
