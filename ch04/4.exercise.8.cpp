// 4.exercise.8.cpp
//
// There is an old story that the emperor wants to thank the inventor of
// the game of chess and asked the inventor to name his reward. The
// inventor asked for one grain of rice for the first square (of a chess board,
// supposedly), 2 for the second, 4 for the third, and so on, doubling for
// each of the 64 squares. That may sound modest, but there wasn't that much
// rice in the empire! Write a program to calculate how many squares are
// required to give the inventor at least 1000 grains of rice, at least
// 1,000,000 grains, and at least 1,000,000,000 grains. You'll need a loop, of
// course, and probably an int to keep track of which square you are at, an int
// to keep the number of grains on the current square, and an int to keep track
// of the grains on all previous squares. We suggest that you write out the
// value of all your variables for each iteration of the loop so that you can
// see what's going on.

#include "std_lib_facilities.h"

const vector<long int> milestones = {1000, 1000000, 1000000000};

int main()
{
    // of course, as the amount of rice grows, int type can't handle
    // such big numbers. On a 64 bit machine, results start to get weird
    // on iteration 32. And long int, and long long int (seems to be the
    // equivalent types on my system) gets weird on iteration 64.
    // "gets weird" == "overflows"
    long int rice {0};
    long int square_rice {1};
    // And I hit the monster. Google about std::vector<bool> and learn
    // how, nowadays, vector<bool> is a specialized vector whose index
    // operator do not return a bool. Solutions vary, but I choose
    // the simplest one, use a deque instead.
    deque<bool> milestone_flags;

    for (size_t i=0; i<milestones.size(); ++i)
        milestone_flags.push_back(false);
    
    for (int square=1; square <= 64; ++square) {

        cout << "Square (" << square << "):\n"
            << "\tPrevious rice accumulated:\t " << rice << " grains.\n"
            << "\tRice on current square:\t\t " << square_rice << " grains.\n"
            << "\tTotal rice:\t\t\t " << rice+square_rice << " grains.\n";
        
        rice += square_rice;
        square_rice *= 2;

        for (size_t i=0; i<milestones.size(); ++i) {
            if (rice >= milestones[i] && !milestone_flags[i]) {
                cout << "\nThe inventor now has at least " << milestones[i]
                    << " grains of rice, just by square " << square << "!!!\n\n"; 
                milestone_flags[i] = true;
            }
        }
    }

    return 0;
}
