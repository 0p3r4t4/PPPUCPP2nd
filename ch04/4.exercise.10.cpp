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
//
// Comments:
//  This program is far more complex than it was in my mind at start. The 
//  input control is driving me nuts and I need to relax on future exercises
//  to avoid lost myself on the details. The cheats this time are cin.eof()
//  and getline(). Sorry.
//  At least it plays "rock, paper and scissors" pretty well.

#include "std_lib_facilities.h"

const vector<string> hands = {"rock", "paper", "scissors"};

// Simply checks if a string is found on hands vector
bool is_hand(string hand)
{
    bool retval {false};

    for (auto v : hands)
        if (v == hand) retval = true;

    return retval;
}

// Get user input until he enters a valid hand
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
    constexpr int score_limit {5};
    int player_score {0};
    int computer_score {0};

    cout << "Let's play rock, paper or scissors ....\n";
    cout << "The first one to score " << score_limit << " wins.\n";

    cout << "Insert some word to randomize computer play: ";
    string random {""};
    // Get the user input, spaces or not, until new line
    getline(cin, random);

    int hand_idx {0};               // Index to hands vector.
    int rand_idx {0};               // Index to random string characters.
    string player_hand {""};
    string computer_hand {""};

    while( player_score < score_limit && computer_score < score_limit) {
        // cycle through random string characters
        rand_idx = (rand_idx+1)%random.size();
        // select the computer hand by adding the current random string character
        // pointed by rand_idx to hand_idx, and use it to cycle throug hands
        // vector.
        hand_idx = (hand_idx+random[rand_idx])%hands.size();

        player_hand = get_player_hand();
        computer_hand = hands[hand_idx];
        
        // call to get_player_hand could have return after EOF, and we don't
        // want to continue playing.
        if (!cin.eof()) {
            cout << "\tYou have " << player_hand << ", and I have "
                << computer_hand << "... ";
            // Since we know that the player_hand is correct, we can compare
            // based on the first character. We can't do a switch-case with
            // a string.
            if (player_hand[0] == computer_hand[0]) {
                cout << "DRAW!\n";
            } else {
                // I don't like this nested switch-statement at all
                switch (player_hand[0]) {
                    case 'r':
                        switch (computer_hand[0]) {
                            case 'p':
                                cout << "I win!\n";
                                ++computer_score;
                                break;
                            case 's':
                                cout << "You win!\n";
                                ++player_score;
                                break;
                        }
                        break;
                    case 'p':
                        switch (computer_hand[0]) {
                            case 's':
                                cout << "I win!\n";
                                ++computer_score;
                                break;
                            case 'r':
                                cout << "You win!\n";
                                ++player_score;
                                break;
                        }
                        break;
                    case 's':
                        switch (computer_hand[0]) {
                            case 'r':
                                cout << "I win!\n";
                                ++computer_score;
                                break;
                            case 'p':
                                cout << "You win!\n";
                                ++player_score;
                                break;
                        }
                        break;
                }
            }
            cout << "\tSCORE - Player: " << player_score << " - Computer: "
                << computer_score << '\n';
        } else {
            // As the user has ended the input, he loses ...
            // The game ends but we're not going to mock the user. Not
            // too much.
            computer_score = 5;        
        }
    }

    if (!cin.eof()) {
        if (player_score == 5)
            cout << "YOU WIN! Congratulations!\n";
        else
            cout << "I WIN! Sorry.\n";
    } else {
        cout << "Don't run away, coward!!!\n";
    }
    return 0;
}
