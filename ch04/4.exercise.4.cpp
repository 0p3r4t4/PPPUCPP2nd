#include "std_lib_facilities.h"

int main()
{
    int first {1};
    int last {100};
    int guess {0};
    int question {0};

    cout << "Please, think of a number between " << first << " and " << last
        << ". I'll going to guess ...\n";

    char answer {' '};

    while (first != last) {
        if ((last-first) == 1) guess = last;    // Correction to avoid average loss
                                                // of information by int
                                                // division
        else guess = (first+last)/2;
    
        // We do a flip-flop asking less or more to eliminate numbers at the
        // lower or higher limit. Not doing so and always asking in one sense does the
        // questions max out at 8. The original game between two people
        // implies three answers: lower, higher or right answer.
        // I find it more funny this way, to tell the player the correct
        // number without his confirmation.
        if (question%2 == 0) {
            cout << "Is your number less than " << guess << "? (y/n)\n";

            cin >> answer;
            if (answer == 'y'){
                ++question;
                last = guess-1;
            }
            else if (answer == 'n'){
                ++question;
                first = guess;
            }
            else 
                cout << "Sorry, I don't understand your answer. Again ...\n";
        }
        else {
            cout << "Is your number more than " << guess << "? (y/n)\n";

            cin >> answer;
            if (answer == 'y'){
                ++question;
                first = guess+1;
            }
            else if (answer == 'n'){
                ++question;
                last = guess;
            }
            else 
                cout << "Sorry, I don't understand your answer. Again ...\n";
        }
    }

    cout << "The number you were thinking of is ... " << first << '\n';
    cout << "I only needed " << question << " questions to guess.\n";
    return 0;
}
