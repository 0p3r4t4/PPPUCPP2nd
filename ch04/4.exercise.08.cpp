// 4.exercise.08.cpp
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
//
// Comments:
//  I hit a monster. Google about std::vector<bool> and learn
//  how, nowadays, vector<bool> is a specialized vector whose subscript
//  operator do not return a bool. Solutions vary and read such a thing as
//  "proxy object reference" is too much for me at this point of the book, so
//  I choose the simplest one, use a deque instead. Cheat again, but learning
//  the hard way, for sure. Since in the context of the program I use the deque
//  member functions size(), push_back() and subscript operator [], it's not 
//  different from we know of a vector.

#include "std_lib_facilities.h"

const vector<int> milestones = {1000, 1000000, 1000000000};

int main()
{
    int rice {0};
    int square {1};
    int square_rice {1};
    deque<bool> milestone_flags;
    size_t milestone_hits {0};

    for (size_t i=0; i<milestones.size(); ++i)
        milestone_flags.push_back(false);
    
    while (milestone_hits < milestones.size()) {

        cout << "Square (" << square << "):\n"
            << "\tPrevious rice accumulated:\t " << rice << " grains.\n"
            << "\tRice on current square:\t\t " << square_rice << " grains.\n"
            << "\tTotal rice:\t\t\t " << rice+square_rice << " grains.\n";
        
        rice += square_rice;

        for (size_t i=0; i<milestones.size(); ++i) {
            if (rice >= milestones[i] && !milestone_flags[i]) {
                cout << "\nThe inventor now has at least " << milestones[i]
                    << " grains of rice, just by square " << square << "!!!\n\n"; 
                milestone_flags[i] = true;
                ++milestone_hits;
            }
        }
        
        square_rice *= 2;
        ++square;
    }

    return 0;
}
