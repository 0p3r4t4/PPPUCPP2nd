// 6.9.try_this.cpp
//
// Get the calculator as presented above to run, see what it does, and try to
// figure out why it works as it does.
//
// Comments:
//
//  In main loop there's an annoyance. The quit command works only if it's
//  introduced at the start of the program. Otherwise it fails with an "primary
//  expected" error. The problem goes on the main() as presented in page 209:
//
//    while (cin) {
//        Token t = ts.get();
//
//        if (t.kind == 'q') break;
//        if (t.kind == ';')
//            cout << '=' << val << '\n';
//        else 
//            ts.putback(t);
//        val = expression();
//    }
//
//  Here, after printing the evaluation with ';', the "val = expression();" get
//  the program to pause on the "Token t = ts.get();" and waits for cin to be
//  capable of read something in Token_stream::get(). If now we insert a "q",
//  Token_stream::get() do not recognize it and pumps the error.
//  This is only a case of error. I guess it's worse.
//  I don't know if this will be solved in chapter 7, but it doesn't let me
//  sleep well, so; we want to wait for input in the ts.get() in main(), and
//  evaluate with expression only if we have something but a quit or print
//  command:
//
//    while (cin) {
//        Token t = ts.get();
//
//        if (t.kind == 'q') break;
//        if (t.kind == ';') {
//            cout << '=' << val << '\n';
//        }
//        else {
//            ts.putback(t);
//            val = expression();
//        }
//    }
//
//  As I side effect, if we enter a print command without ans expression, the 
//  printed value is the last evaluated one. I can live with that.

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
    cin >> ch;

    switch (ch) {
        case ';':
        case 'q':
        case '(': case ')':
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
        case '(':
            {
                double d = expression();
                t = ts.get();
                if (t.kind != ')') error("')' expected");
                return d;
            }
        case '8':
            return t.value;
        default:
            error("primary expected");
    }
}

double term()
{
    double left = primary();
    Token t = ts.get();

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
                ts.putback(t);
                return left;
        }
    }
}

double expression()
{
    double left = term();
    Token t = ts.get();

    while (true) {
        switch (t.kind) {
            case '+':
                left += term();
                t = ts.get();
                break;
            case '-':
                left -= term();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

int main()
try
{
    double val = 0;
    while (cin) {
        Token t = ts.get();

        if (t.kind == 'q') break;
        if (t.kind == ';') {
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
