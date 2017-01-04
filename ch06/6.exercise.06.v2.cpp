// 6.exercise.06.v2.cpp
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
//  The v1 version of this exercise has a problem and, since Stroustrup exercise
//  solution has the same problem, I want to solve it in a new version while
//  having the former for comparison.
//
//  The problem is that we return false from sentence() as we reach an error in
//  the evaluation but not having consumed the rest of the input. This way:
//
//    Some birds fla . 
//
//  returns (Not OK) since "Some" is not a known determiner, and (Not OK)
//  again, while parsing the rest of the input, "birds fla . ", as "fla" is not
//  a verb. We should obtain a single (Not OK) but we get two.
//
//  This is an example of various problems we would face by the same cause:
//  early return of false evaluation with pending input. So, what can we do?
//
//  Let's suppose that we want to parse multiline sentences, so newline
//  character is not considered a sentence terminator. Only the dot terminates
//  a sentence. But if the sentence is not right, we must discard input. How
//  much we discard? All the input? What if we get the input from a file?
//  What if we know the sentence is not right before the end of the line or the
//  appearance of the dot? i.e. we want this:
//
//   This is a wrong sentece . C++ rules .
//   What if this ? We can discard all the line
//   the birds fly and
//   fish swim .
//
//  to evaluate as:
//
//   Not OK for "This is a wrong sentence"
//   OK     for "C++ rules"
//   Not OK for "What if this ? We can discard all the line"
//   OK     for "the birds fly and fish swim"
//
//  So if a sentence is wrong, we will discard input until a dot or a newline
//  is reached, whatever comes first.
//  How we do this? I don't know a streamlined way to achieve it. Perhaps
//  cin.ignore() or std::getline(). As our criteria to limit discard is double
//  (dot and newline) neither of them seem up to the work. So I'll go the
//  pedestrian way and consume characters in a loop in function discard_input().
//  The point to consume characters is that using cin >> operator skips blanks,
//  including newline character. So we use cin.get() instead.

#include "std_lib_facilities.h"

// Grammar terminals as alternatives for their rules
static const vector<string> verbs = {"rules", "fly", "swim"};
static const vector<string> nouns = {"birds", "fish", "C++"};
static const vector<string> conjunctions = {"and", "or", "but"};
static const vector<string> determiners = {"the"};

void discard_input()
{
    char c = ' ';

    while ( c != '.' && c != '\n' )
        c = cin.get();
}

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
    
    return true;
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

        if ( sentence() ) {
            cout << "OK\n";
        }
        else {
            cout << "Not OK\n";
            discard_input();
        }
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
