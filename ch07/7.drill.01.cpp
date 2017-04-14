// 7.drill.1.calculator08buggy.cpp
//
//  1. Starting from the file calculator08buggy.cpp, get the calculator to
//     compile.

/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include "std_lib_facilities.h"

// DRILL 1. Token has member functions. Define it as class.
// Also use uniform initialization for data members and obviate
// initialization where default initialization will do it.
class Token {
public:
	char kind;
	double value;
	string name;

	Token(char ch) :kind{ch} { }
	Token(char ch, double val) :kind{ch}, value{val} { }
	// DRILL.1. with this missing constructor the program complies and kinda
	// works.
	Token(char ch, string n) : kind{ch}, name{n} { }
};

class Token_stream {
public:
    // DRIL 1. The compiler won't protest, but is better to initialize full
    // with false rather than with a 0. 
    Token_stream() :full{false}, buffer{0} { }
	Token get();
    // DRILL 1. unget() is not used on the book, putback() is used instead
	void putback(Token t) { buffer=t; full=true; }
	void ignore(char c);
// DRILL 1. Put private members at the end of the class definition.
private:
	bool full;
	Token buffer;
};

const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
// DRILL 1. Lets get rid of magical constants, as "let" or "quit".
const string declkey = "let";
const string quitkey = "quit";

Token Token_stream::get()
{
	if (full) { full=false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
		return Token{ch};
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	cin.putback(ch);
		double val;
		cin >> val;
		return Token{number, val};
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			// DRILL 1. It's supposed to add chars to the string, so it's s+=ch
			// instead of s=ch
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			// DRILL 1. This could work, but the book insistently uses
			// cin.putback(ch) as substitute.
			// cin.unget();
			cin.putback(ch);
			// DRILL 1. Lets get rid of magical constants, as "let" or "quit".
			if (s == declkey) return Token{let};	
			// DRILL 1. I guess we must return a quit token instead of a name
			// one.
			if (s == quitkey) return Token{quit};
			return Token{name,s};
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
// It causes current Token in Token_stream to be discarded if Token's kind is
// of the type of token (number, let, name ...) indicated by argument.
// It also removes chars from cin until the kind of Token c is found.
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin>>ch)
		if (ch == c) return;
}

// DRILL 1. With function members we prefer a class declaration
class Variable {
public:
	string name;
	double value;
	// DRILL 1. Although is not really needed
	// Variable(string n, double v) :name(n), value(v) { }
};

// DRILL 1. var_table, as stated in the book, feels like a better name than
// "names"
vector<Variable> var_table;	

double get_value(string s)
{
    // DRILL 1. We prefer ranged-for loops
	// for (size_t i = 0; i < names.size(); ++i)
	// if (names[i].name == s) return names[i].value;
	for (const Variable& v : var_table)
	    if (v.name == s) return v.value;
	error("get: undefined name ", s);
}

void set_value(string s, double d)
{
    // DRILL 1. We prefer ranged-for loops
	// for (size_t i = 0; i<=names.size(); ++i)
	//      if (names[i].name == s) {
	//          names[i].value = d;
	//          return;
    //      }
    for (Variable& v : var_table)
        if (v.name == s) {
            v.value = d;
            return;
        }
	error("set: undefined name ", s);
}

bool is_declared(string s)
{
    // DRILL 1. We prefer ranged-for loops
	// for (size_t i = 0; i<names.size(); ++i)
	//      if (names[i].name == s) return true;
	for (const Variable& v : var_table)
	    if (v.name == s) return true;
	return false;
}

Token_stream ts;

double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
		t = ts.get();
		// DRILL 1. ')' is expected, not '('. A silly one.
		if (t.kind != ')') error("')' expected");
		// DRILL 1. If success, nothing is returned, so:
		return d;
	}
	case '-':
		return - primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	default:
		error("primary expected");
	}
}

double term()
{
	double left = primary();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
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
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != 'a') error ("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of " ,name);
	double d = expression();
	var_table.push_back(Variable{name,d});
	return d;
}

double statement()
{
	Token t = ts.get();
	switch(t.kind) {
	case let:
		return declaration();
	default:
		ts.putback(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while(true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.putback(t);
		cout << result << statement() << '\n';
	}
	// DRILL 1. Better catch exception than the narrower runtime_error
	catch(exception& e) {
		cerr << e.what() << '\n';
		clean_up_mess();
	}
}

int main()
try {
    calculate();
    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    // DRILL 1. Bad syntax in &&. In Linux I don't actually need this
    // char c;
    // while (cin >> c && c!=';') ;
    return 1;
}
catch (...) {
    cerr << "exception\n";
    // char c;
	// while (cin >> c && c!=';');
	return 2;
}
