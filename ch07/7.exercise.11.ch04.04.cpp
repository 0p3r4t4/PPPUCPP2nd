// 7.exercise.11.ch04.04.cpp
//
//  Revisit two programs you wrote for the exercises in Chapter 4 or 5. Clean
//  up that code according to the rules outlined in this chapter. See if you
//  find any bugs in the process.
//
// ORIGINAL STATEMENT
// 
//  4.exercise.04.cpp
//
//   Write a program to play a numbers guessing game. The user thinks of a number
//   between 1 and 100 and your program ask questions to figure out what the
//   number is (e.g., "Is the number you are thinking of less than 50?"). Your
//   program should be able to identify the number after asking no more than
//   seven questions. Hint: User the < and <= operators and the if-else
//   construct.
// 
// COMMENTS
//
//  In summary the chapter tell us to:
//
//      1. Review program presentation to the user.
//      2. Do testing trying to break the program and solve bugs found.
//      3. Clean up the code:
//          a) get rid of symbolic constants
//          b) divide the code into functions that do just one single logical
//          action
//          c) review code layout to improve code reading
//      4. Evaluate if we can recover from errors
//      5. Evaluate and implement improvements to the program
//
// 1. 
//  Why not give the user the chance to play again without exiting the program?
//  This prevents us from the kind of automatic testing we do with the script
//  7.exercise.11.ch04.04.test.bash. And since it's fairly simple I will not
//  implement it to retain the automatic testing capability (just for fun).
//  As stated in the comments (perhaps not in the right place) we only ask if
//  the number is more or less than our guess. The original game includes
//  asking if our guess is correct. As it turns out, doing so at a certain
//  point (where we have only two candidates left) let us enforce the 7
//  questions limit.
// 2.
//  If the user lies, or in certain combinations of answers, the program will
//  miscalculate a new range for guessing. This is because I don't check if new
//  limits are logical or not. Lower limit could not be greater than upper
//  limit and since we are shrinking the range, lower limit could not decrease
//  and upper limit could not increase. As it turns out, these checks will be
//  useless when guess_one_from_two() is introduced, but they serve well enough
//  during development implemented as checked_modify_range().
//  The script 7.exercise.11.ch04.04.test.bash permits us to test this program
//  in deep (the input domain is bounded and small enough to test it
//  completely).
// 3.a
//  Answers are currently magic constants. Also the distinction for asking if
//  the guess is less or more than the number.
// 3.b
//  We have all the code in the main body. Functions are demanded.
// 3.c
//  The 'flip-flop' if-then is basically duplicated code we can make more
//  concise. 
// 4.
//  We read chars for answers. Each line introduced by the user could be longer
//  and must be cleared after a correct or incorrect answer. We could use
//  cin.ignore() to clear input, but it interferes with the testing script. So
//  I will not implement it for the same reasons exposed on point 1.
//  There is any possible error from we want to recover? When
//  checked_modify_range() was in use, a try-catch in main have been needed.
//  Not to recover but to be capable to use error().
// 5.
//  The introduction of guess_one_from_two() lend us to effectively limit the
//  guesses to 7, and to add the type equal to the questions we do to the user.
//  It feels more natural this way since guess() is able to guess the number
//  but it repeats questions and tends to divagate when the range consists on 
//  two consecutive numbers.
//  Apart from this I don't know what to improve since the game is really
//  simple a well defined. Perhaps let the user say the upper limit, but then
//  the limit of 7 guesses will not be enforceable.

#include "std_lib_facilities.h"

const char yes {'y'};
const char no {'n'};
const char is_more {'M'};
const char is_less {'L'};

int first {1};
int last {100};
int candidate {0};
int question {0};

void checked_modify_range(int f, int l)
// This function seems unuseful now, but it really helps while programming.
{
    // First could not be greater than Last
    // First could decrease and Last coul not increase
    if ((f > l) || (f < first) || (l > last)) {
        error("You LIED!");
    }

    first = f;
    last = l;
}

void guess()
{
    candidate = (first+last)/2;

    // We do a flip-flop asking less or more to eliminate numbers at the
    // lower or higher limit. 
    char guess_type;
    if (question%2 == 0) guess_type = is_less;
    else guess_type = is_more;

    cout << "Is your number ";
    if (guess_type == is_less) cout << "less";
    else cout << "more";
    cout << " than " << candidate << "? (y/n)\n";

    char answer {' '};
    cin >> answer;
    if (answer == yes) {
        ++question;
        // if the answer is yes, we could ignore the candidate
        if (guess_type == is_less) checked_modify_range(first, candidate - 1);
        if (guess_type == is_more) checked_modify_range(candidate + 1, last);    
    }
    else if (answer == no) {
        ++question;
        // if the answer is not, the candidate must be preserved as guessable
        if (guess_type == is_less) checked_modify_range(candidate, last);
        if (guess_type == is_more) checked_modify_range(first, candidate);    
    }
    else {
        cout << "Sorry, I don't understand your answer. Again ...\n";
    }
}

void guess_one_from_two()
// Covers the case when the first and last are two consecutive numbers. The
// generalized formula from guess() kinda works but is inefficient. This one
// permits us to enforce the 7 guesses limit.
{
    cout << "Is the number you're thinking of the " << first << "? (y/n)\n";
    char answer {' '};
    cin >> answer;
    ++question;

    if (answer == yes) last = first;
    else if (answer == no) first = last;
    else {
        cout << "Sorry, I don't understand your answer. Again ...\n";
        --question;
    }
}

int main()
try
{
    cout << "Please, think of a number between " << first << " and " << last
        << ". I'll going to guess ...\n";

    while (first != last) {
        if (last-first == 1) guess_one_from_two();
        else guess();
    }

    cout << "The number you were thinking of is ... " << first << '\n';
    cout << "I only needed " << question << " questions to guess.\n";

    return 0;
}
catch (exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Unknown exception!\n";
    return 2;
}
