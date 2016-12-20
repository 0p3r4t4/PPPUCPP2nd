// 6.exercise.02.cpp
//
// Add the ability to use {} as well as () in the program, so that
// {(4+5)*6}/(3+4) will be a valid expression.
//
// Comments:
//
//  This one starts as a copy of 6.9.try_this.cpp and adds the greeting lines
//  proposed in points 4 and 5 from the Drill. Also add some comments (ripped
//  from the former files)
//
//  I think that {} must be a synonim of (), so we add a new rule to the Primary
//  token:
//
//       Primary:
//          ...
//          '{' Expression '}'
//
//  This new rule implies changes in:
//      Token_stream::get()
//      primary()
//      and greeting message ...

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

double term()
{
    double left = primary();
    Token t = ts.get();         // get the next token from token stream

    while (true) {
        switch (t.kind) {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/':
                {
                    double d = primary();
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
         << "(Currently +, -, *, /, and grouping with () and {} are supported.)\n"
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
