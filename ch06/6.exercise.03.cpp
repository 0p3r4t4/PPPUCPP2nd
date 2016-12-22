// 6.exercise.03.cpp
//
// Add a factorial operator: use a suffix ! operator to represent "factorial".
// For example, the expression 7! means 7*6*5*4*3*2*1. Make ! bind tighter than
// * and /; that is, 7*8! means 7*(8!) rather than (7*8)!. Begin by modifying
// the grammar to account for a higher-level operator. To agree with the
// standard mathematical definition of factorial, let 0! evaluate to 1. Hint:
// The calculator functions deal with doubles, but factorial is defined only
// for ints, so just for x!, assign the x to an int and calculate the factorial
// of that int.
//
// Comments:
//  I have two options: 
//      - Create a new alternative to the Primary rule
//      - Create a new rule for the factorial (and other "higher-level
//      operators")
//  I decided to give a chance to the last one, performing changes in the
//  grammar as:
//
//      ...
//      Term:
//          Hiop
//          Term "*" Hiop
//          Term "/" Hiop
//      Hiop:
//          Primary
//          Primary "!"
//      ...
//  
//  So we must:
//      - create a new function hiop() to parse the new rule.
//      - make changes to term() invoking hiop() where we previously invoke
//      primary().
//      - create a function factorial() to calculate the value.
//
//  The factorial() function has an int argument and returns an int. This is
//  coherent to the mathematical definition despite we use it with doubles.
//  Also, it has been implemented in a non-recursive form. Recursivity
//  is elegant but it could be expensive. Factorial is a classic example of
//  recursivity, so I try something different. A recursive implementation would
//  be:
//
//      int factorial(int n)
//      {
//          if (n < 0) error("factorial(), invoked with a negative number");
//
//          if (n == 0) return 1;
//          else return (n * factorial(n-1));
//      }
//

#include "std_lib_facilities.h"

class Token {
    public:
        char kind;
        double value;
};

class Token_stream {
    public:
        Token get();
        void putback(Token t);
    private:
        bool full {false};
        Token buffer;
};

Token Token_stream::get() 
// Return a token from buffer or read a new one from cin.
{
    if (full) {
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;      // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
        case ';':
        case 'q':
        case '(': case ')':
        case '{': case '}':
        case '+': case '-': case '*': case '/':
        case '!':
            return Token{ch};
        case '.':
        case '0': case '1': case '2': case '3':
        case '4': case '5': case '6': case '7':
        case '8': case '9':
            {
                cin.putback(ch);
                double val;
                cin >> val;
                return Token {'8', val};
            }
        default:
            error("Bad token");
    }
}

void Token_stream::putback(Token t)
// Put back a token on Token_stream to later use
// Pre-condition:
//  The Token_stream buffer must not be full
{
    if (full) error("putback() into a full buffer");

    buffer = t;
    full = true;
}

Token_stream ts;
double expression();

int factorial(int n) 
// Calculates the factorial of n (n!)
// Non-recursive implementation.
// Pre-condition:
//  n must be positive
{
    if (n < 0) error("factorial(), invoked with a negative number");

    int f = 1;
    if (n != 0){
        while (n > 0) {
            f *= n;
            --n;
        }
    }
    return f;
}

double primary()
{
    Token t = ts.get();
    switch (t.kind) {
        case '(':   // handle '(' expression ')'
            {
                double d = expression();
                t = ts.get();
                if (t.kind != ')') error("')' expected");
                return d;
            }
        case '{':   // handle '{' expression '}'
            {
                double d = expression();
                t = ts.get();
                if (t.kind != '}') error("'}' expected");
                return d;
            }
        case '8':               // we use '8' to represent a number
            return t.value;     // return the number's value
        default:
            error("primary expected");
    }
}

double hiop()
{
    double left = primary();
    Token t = ts.get();

    switch (t.kind) {
        case '!':   // handle factorial operation
            return factorial(left);
            // This could be written:
            // {
            //      int n = left;
            //      double d = factorial(n);
            //      return d;
            // }
            // , but a brief comparison at Compiler Explorer (https://godbolt.org)
            // shows that the former has similar but smaller assembly code in
            // gcc 6.3
        default:    // otherwise, return the primary putting back t into ts
            ts.putback(t);
            return left;
    }
}

double term()
{
    double left = hiop();
    Token t = ts.get();         // get the next token from token stream

    while (true) {
        switch (t.kind) {
            case '*':
                left *= hiop();
                t = ts.get();
                break;
            case '/':
                {
                    double d = hiop();
                    if (d == 0) error("divide by zero");
                    left /= d;
                    t = ts.get();
                    break;
                }
            default:
                ts.putback(t);      // put t back into the token stream
                return left;
        }
    }
}

double expression()
{
    double left = term();       // read and evaluate a Term
    Token t = ts.get();         // get the next token from token stream

    while (true) {
        switch (t.kind) {
            case '+':
                left += term();     // evaluate Term and add
                t = ts.get();
                break;
            case '-':
                left -= term();     // evaluate Term and substract
                t = ts.get();
                break;
            default:
                ts.putback(t);      // put t back into the token stream
                return left;        // finally: no more + or -: return the answer
        }
    }
}

int main()
try
{
    cout << "Welcome to our simple calculator.\n"
         << "Please enter expressions using floating-point numbers.\n"
         << "(Currently +, -, *, /, grouping with () and {} and ! for factorial\n"
         << "are supported.)\n"
         << "Evaluate the expression with ; at the end. Enter q to quit.\n";

    double val = 0;
    while (cin) {
        Token t = ts.get();

        if (t.kind == 'q') break;   // 'q' for quit
        if (t.kind == ';') {        // ';' for print now
            cout << '=' << val << '\n';
        }
        else {
            ts.putback(t);
            val = expression();
        }
    }
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
