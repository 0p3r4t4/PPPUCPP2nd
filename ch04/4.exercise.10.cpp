// 4.exercise.10.cpp
//
// Write a program that plays the game "Rock, Paper, Scissors". 
// Use a switch-statement to solve this exercise. Also, the machine should
// give random answers (i.e., select the next rock, paper or scissors
// randomly). Real randomness is too hard to provide just now, so just build
// a vector with a sequence of values to be used as "the next value". If you
// build the vector into the program, it will always play the same game, so
// maybe you should let the user enter some values. Try variations to make it
// less easy for the user to guess which move the machine will make next.

#include "std_lib_facilities.h"

const vector<string> hands = {"rock", "paper", "scissors"};

bool is_hand(string hand)
{
    bool retval {false};

    for (auto v : hands)
        if (v == hand) retval = true;

    return retval;
}

string get_player_hand()
{
    string hand {""};
    bool ok {false};

    while (!ok && !cin.eof()) {
        cout << "Take your bet, rock, paper or scissors? ";
        cin >> hand;
        if (!is_hand(hand))
            cout << "That's not rock, paper os scissors ...\n";
        else
            ok = true;
    }

    return hand;
}

int main()
{
    cout << "Let's play rock, paper or scissors ....\n";

    cout << "Insert some word to randomize computer play: ";
    string random {""};
    // Get the user entry, spaces or not, until new line
    getline(cin, random);

    int hand_idx {0};               // Index to hands vector.
    int rand_idx {0};               // Index to random string characters.
    string player_hand {""};

    while(!cin.eof()) {
        // cycle through random string characters
        rand_idx = (rand_idx+1)%random.size();
        // select the computer hand by adding the current random string character
        // pointed by rand_idx to hand_idx, and use it to cycle throug hands
        // vector.
        hand_idx = (hand_idx+random[rand_idx])%hands.size();

        player_hand = get_player_hand();
        
        // call to get_player_hand could have return after EOF, and we don't
        // want to continue playing.
        if (!cin.eof()){
            cout << "Player has: " << player_hand
                << "\tComputer has: " << hands[hand_idx] << '\n'
                << "\tRand: " << random[rand_idx] << " Index: "
                << hand_idx << '\n';
            
            //switch-statement to play, here
        }
        else
            cout << "Bye!\n";
    }
    return 0;
}
