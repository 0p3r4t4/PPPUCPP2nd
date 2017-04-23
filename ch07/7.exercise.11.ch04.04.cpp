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
//  As stated in the comments (perhaps not in the right place) we only ask if
//  the number is more or less than our guess. The original game includes
//  asking if our guess is correct. Perhaps we have to implement it that way.
// 2.
//  If the user always answer y or n, or he lies, the program is not capable of
//  detecting it. But we can solve it checking the answer with our current
//  limits.
// 3.a
//  Answers are currently magic constants.
// 3.b
//  We have all the code in the main body. Functions are demanded.
// 3.c
//  The 'flip-flop' if-then is basically duplicated code we can make more
//  concise.
// 4.
//  We read chars for answers. Each line introduced bu the user could be longer
//  and must be cleared after a correct or incorrect answer.
//  There is any possible error from we want to recover?
// 5.
//  I don't know what to improve since the game is really simple a well
//  defined. Perhaps let the user say the upper limit, but then the limit of 7
//  guesses will not be enforceable.

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
    if ((last-first) == 1) candidate = last;    // Correction to avoid loss
                                                // of information by int
                                                // division
    candidate = (first+last)/2;

    // We do a flip-flop asking less or more to eliminate numbers at the
    // lower or higher limit. Not doing so and always asking in one sense does the
    // questions max out at 8. The original game between two people
    // implies three answers: lower, higher or right answer.
    // I find it more funny this way, to tell the player the correct
    // number without his confirmation.

    char guess_type;
    if (question%2 == 0) guess_type = is_less;
    else guess_type = is_more;
    
    cout << "Is your number ";
    if (guess_type == is_less) cout << "less";
    else cout << "more";
    cout << " than " << candidate << "? (y/n)\n";

    char answer {' '};
    cin >> answer;
    ++question;
    if (answer == yes) {
        // if the answer is yes, we could dismiss the candidate
        if (guess_type == is_less) checked_modify_range(first, candidate - 1);
        if (guess_type == is_more) checked_modify_range(candidate + 1, last);    
    }
    else if (answer == no) {
        // if the answer is not, the candidate must be preserved as guessable
        if (guess_type == is_less) checked_modify_range(candidate, last);
        if (guess_type == is_more) checked_modify_range(first, candidate);    
    }
    else {
        cout << "Sorry, I don't understand your answer. Again ...\n";
        --question;
    }
    cout << first << ", " << last << '\n';
}

int main()
try
{
    cout << "Please, think of a number between " << first << " and " << last
        << ". I'll going to guess ...\n";

    while (first != last) {
        guess();
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
