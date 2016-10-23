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

const vector<string> values = {"rock", "paper", "scissors"};

bool is_value(string value)
{
    bool retval {false};

    for (auto v : values)
        if (v == value) retval = true;

    return retval;
}

string get_player_value()
{
    string value {""};
    bool ok {false};

    while (!ok) {
        cout << "Take your bet, rock, paper or scissors? ";
        cin >> value;
        if (!is_value(value))
            cout << "That's not rock, paper os scissors ...\n";
        else
            ok = true;
    }

    return value;
}

vector<char> get_random_values()
{
    vector<char> randoms;
    string rword {""};

    cout << "Insert some word to randomize computer play: ";
    cin >> rword;
    for (auto c : rword)
        randoms.push_back(c);

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n';
    return randoms;
}

int main()
{
    int rand_index {0};
    int values_index {0};
    string player_value {""};

    cout << "Let's play rock, paper or scissors ....\n";

    vector<char> randoms;
    randoms = get_random_values();

    while(true) {
        // traverse random elements on a loop
        rand_index = (rand_index+1)%randoms.size();
        // select the computer value by adding the rand element, and control
        // range access by doing mod operation
        values_index = (values_index+randoms[rand_index])%values.size();

        player_value = get_player_value();
        cout << "Player has: " << player_value 
            << "\tComputer has: " << values[values_index] << '\n'
            << "\tRand: " << randoms[rand_index] << " Index: "
            << values_index << '\n';
        
        //switch-statement to play, here
    }
    return 0;
}
