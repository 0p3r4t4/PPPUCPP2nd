// 6.exercise.06.v1.cpp
//
// Write a program that checks if a sentence is correct according to the
// "English" grammar in 6.4.1. Assume that every sentence is terminated by
// a full stop (.) surrounded by whitespace. For example, "birds fly but the
// fish swim . " is a sentence, but "birds fly but the fish swim" (terminating
// dot missing) and "birds fly but the fish swim." (no space before the dot)
// are not. For each sentence entered, the program should simply respond "OK"
// or "not OK". Hint: Don't bother with tokens; just read into a string using
// >>.
//
// Comments:
//
//  From the examples in the statement, I guess we must use the extended
//  grammar developed on exercise 5.  Also, the hint tell me that we can use
//  cin as a tokenizer. This conflicts with that grammar since the inclusion of
//  the NounPhrase rule adds an step on evaluation where I must preserve words
//  and cin has nothing but a putback() for characters; a more advanced
//  Token_stream will come in handy, but will add complexity. Must we treat
//  terminating dot as a command for evaluation or as a part of the grammar
//  definition to a sentece? I choose the later.
//
//  So, the grammar, as implemented, will be:
//
//      Sentence:
//          Subject Verb "."
//          Subject Verb Conjunction Sentence
//      Subject:
//          Noun
//          Determiner Noun
//      ...
//          
//  While Verb, Noun, Conjunction and Determiner rules alternatives are all
//  terminals, I use a generic function rather than a function for each rule.
//  This function merely searchs if a string exists on a predefined vector (one
//  for each rule and each one containing the terminals for it).

#include "std_lib_facilities.h"

// Grammar terminals as alternatives for their rules
static const vector<string> verbs = {"rules", "fly", "swim"};
static const vector<string> nouns = {"birds", "fish", "C++"};
static const vector<string> conjunctions = {"and", "or", "but"};
static const vector<string> determiners = {"the"};

bool is_in(string s, vector<string> v)
// Returns true if string s is contained in vector<string> v and returns false
// otherwise.
{
    for (string sv : v) 
        if (sv == s) return true;

    return false;
}

bool subject()
{
    string t;
    cin >> t;

    if ( is_in(t, determiners) ) {
        // There is a determiner, so we search for a noun
        cin >> t;
        if ( is_in(t, nouns) ) return true;
    }
    if ( is_in(t, nouns) ) return true;
    
    return false;
}

bool sentence()
{
    if ( !subject() ) return false;

    string t;
    cin >> t;
    if ( !is_in(t, verbs) ) return false;

    cin >> t;
    if ( t == "." ) return true;       // Sentence terminated
    if ( !is_in(t, conjunctions) ) return false;
    return sentence();
}

int main()
try
{
    cout << "Simple English grammar parser.\n"
         << "Enter sentences like \"birds fly but the fish swim . \",\n"
         << "terminated by a full stop surrounded by whitespaces.\n"
         << "The program will tell you if it's a correct sentence or not.\n"
         << "Type q and press enter to finish.\n";

    char c;

    while (cin) {
        cin >> c;

        if (c == 'q') break;    // 'q' for quit, but no noun could start by 'q' ...
        else cin.putback(c);

        cout << ( sentence() ? "OK" : "Not OK" ) << '\n';   // Ternary operator
    }

    return 0;
}
catch (exception& e)
{
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Oops! Unknown exception\n";
    return 2;
}
