// 7.exercise.04.cpp
//
//  The get_value(), set_value(), is_declared(), and define_name() functions
//  all operate on the variable var_table. Define a class called Symbol_table
//  with a member var_table of type vector<Variable> and member functions
//  get(), set(), is_declared(), and declare(). Rewrite the calculator to use
//  a variable of type Symbol_table.

// This program implements a basic expression calculator based in this input
// grammar:
//
//  Calculation:
//      Statement
//      Print
//      Quit
//      Calculation Statement
//  Statement:
//      Declaration
//      Assignment
//      Expression
//  Print:
//      ";"
//  Quit:
//      "quit"
//  Declaration:
//      "let" Name "=" Expression
//      "const" Name "=" Expression
//  Assignment:
//      Name "=" Expression
//  Expression:
//      Term
//      Expression "+" Term
//      Expression "-" Term
//  Term:
//      Primary
//      Term "*" Primary
//      Term "/" Primary
//      Term "%" Primary
//  Primary:
//      Number
//      "("Expression")"
//      "-" Primary
//      "+" Primary
//      Name
//      Function"("Arguments")"
//  Function:
//      "sqrt"
//      "pow"
//  Arguments:
//      Expression
//      Argument","Expression
//  Number:
//      [floating-point-literal]
//  Name:
//      [alphabetic-char]
//      Name[alphabetic-char]
//      Name[digit-char]
//      Name"_"
//
// Input comes from cin through the Token_stream called ts.
//
// Comments:
//  define_name() do not exist. But Symbol_table::declare() is needed if the
//  var_table member is private.

#include "std_lib_facilities.h"

// Models a grammar token from input
class Token {
public:
    // kind is always needed while value and name are initialized depending on
    // the needs of each kind. Thus, three distinct constructors are defined.
	char kind;  
	double value;
	string name;

	Token(char ch) :kind{ch} { }
	Token(char ch, double val) :kind{ch}, value{val} { }
	Token(char ch, string n) : kind{ch}, name{n} { }
};

// Models cin as a Token stream
class Token_stream {
public:
    //Token_stream() :full{false}, buffer{0} { }
	Token get();
	void putback(Token t) { buffer.push_back(t); }
	void ignore(char c);
private:
	vector<Token> buffer;
};

// Token kinds - Arbitrarily chosen
const char let = 'L';
const char constant = 'C';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char sqrtfun = 's';
const char powfun = 'p';
// Keywords
const string declkey = "let";
const string constkey = "const";
const string quitkey = "quit";
// Builtin functions
const string sqrtkey = "sqrt";
const string powkey = "pow";

Token Token_stream::get()
// Processes cin to get tokens from the implemented grammar
{
    // If already have a tokens buffered, return the last one
    if (!buffer.empty()) {
        Token t = buffer.back();
        buffer.pop_back();
        return t;
    }

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
	case ',':   // Added as separator for function argument lists
		return Token{ch};   // These literals directly define Token kind
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':   // Numeric literal
	{	cin.putback(ch);
		double val;
		cin >> val;
		return Token{number, val};
	} 
	default:
	    // We can also expect strings. These to be keywords for declaration and
	    // exiting the program or variable names.
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			cin.putback(ch);
			if (s == declkey) return Token{let};	
			if (s == constkey) return Token{constant};
			if (s == quitkey) return Token{quit};
			if (s == sqrtkey) return Token{sqrtfun};
			if (s == powkey) return Token{powfun};
			return Token{name,s};
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
// Clear input until c or '\n' is found
{
    // First inspect if a Token of c kind is buffered
    // Eliminate not c kind tokens
    while (!buffer.empty() && buffer.back().kind != c)
        buffer.pop_back();
    // Buffer contains a c kind token
    if (!buffer.empty()) return;

    // and work directly on cin
	char ch{' '};
    while (ch != c && ch != '\n')
        ch = cin.get();
    return;
}

class Variable {
public:
	string name;
	double value;
	bool constant;
};

class Symbol_table {
    vector<Variable> var_table;
public:
    double get(string s);
    void set(string s, double d);
    bool is_declared(string s);
    void declare(string s, double d, bool c);
};

double Symbol_table::get(string s)
{
	for (const Variable& v : var_table)
	    if (v.name == s) return v.value;
	error("get: undefined name ", s);
}

void Symbol_table::set(string s, double d)
{
    for (Variable& v : var_table)
        if (v.name == s) {
            if (v.constant) error(s, " is a constant");
            v.value = d;
            return;
        }

	error("set: undefined name ", s);
}

bool Symbol_table::is_declared(string s)
{
	for (const Variable& v : var_table)
	    if (v.name == s) return true;
	return false;
}

void Symbol_table::declare(string s, double d, bool c)
{
    // This can be seen as redundant with declaration() doing the same check.
    // But remember that we directly declare variables and constants in the main
    // body, so it's well placed here.
    if (is_declared(s)) error(s, "is declared twice");
    var_table.push_back(Variable{s, d, c});
}

Symbol_table symbols;
Token_stream ts;

double expression();

double eval_function(char c)
// Evaluates function of kind c. The next on input must be "("Expression")".
{
    vector<double> args;    // Vector to store (variable number) of function 
                            // arguments.
    Token t = ts.get();
    if (t.kind != '(') error("'(' expected after function call");

    // Handle argument list. Default: no arguments, do nothing, thus, no
    // default on switch statement.
    switch (c) {
    case sqrtfun:
        args.push_back(expression());
        break;
    case powfun:
        args.push_back(expression());
        t = ts.get();
        if (t.kind != ',') error("Bad number of function arguments");
        args.push_back(expression());
        break;
    }

    t = ts.get();
    if (t.kind != ')') error("Bad number of function arguments");

    // Evaluation snd restrictions implementation
    switch (c) {
    case sqrtfun:
        if (args[0] < 0) error("sqrt() is undefined for negative numbers");
        return sqrt(args[0]);
    case powfun:
        return pow(args[0], narrow_cast<int>(args[1]));
    default:
        // In case we have defined the name as a token for Function rule but
        // forgot to implement its evaluation
        error("Function not implemented");
    }
}

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-':   // Negative signed numbers
		return - primary();
	case '+':   // Positive signed numbers
		return primary();
	case number:
		return t.value;
    case name:  // Variable: get value from table
		return symbols.get(t.name);
	case sqrtfun:
	case powfun:
	    // Call to eval_function by t.kind so we can collapse evaluation of
	    // distinct functions on a single line
	    return eval_function(t.kind);
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
        case '%':
        {   double d = primary();
            if (d == 0) error("divide by zero");
            left = fmod(left, d);
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

double assignment()
{
    // We get there by knowing that a name and an '=' come next.
    Token t = ts.get();
    string var_name = t.name;
    if (!symbols.is_declared(var_name)) error(var_name, " has not been declared");

    ts.get(); // Get rid of the '='
    double d = expression();
    symbols.set(var_name, d);
    return d;
}


double declaration()
{
    // Check if it's a regular declaration or a constant one
    bool is_const = false;
    Token t = ts.get();
    if (t.kind == constant) is_const = true;

    // Check part by part of Declaration gramamr rule behind "let" or "const"
	Token t2 = ts.get();
	if (t2.kind != name) error ("name expected in declaration");
	string var_name = t2.name;
	if (symbols.is_declared(var_name)) error(var_name, " declared twice");

	Token t3 = ts.get();
	if (t3.kind != '=') error("= missing in declaration of " ,var_name);

	double d = expression();
	symbols.declare(var_name, d, is_const);
	return d;
}

double statement()
{
	Token t = ts.get();
	switch(t.kind) {
	case let:
	case constant:
	    ts.putback(t);
		return declaration();
	case name:
	{
	    Token t2 = ts.get();
	    // Whatever t2 is, we have to rollback
        ts.putback(t2);
        ts.putback(t);
	    if (t2.kind == '=') {
	        return assignment();
	    }
	    // We could move the putback(t) inside the if-statement and let this
	    // fallback to the default case. I have my doubts that something like
	    // that won't give us problems on the future. The current solution also
	    // will be problematic if something else than an expression is
	    // introduced as a statement.
	    return expression();
	}
	default:
		ts.putback(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);   // Discard input until a print command or a new line
	                    // is found (inclusive).
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while(true) 
	try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();   // Remove print commands
		if (t.kind == quit) return;
		ts.putback(t);
		cout << result << statement() << '\n';
	}
	catch(exception& e) {
		cerr << e.what() << '\n';
		clean_up_mess();    // Discard remaining input and prompt user again
	}
}

int main()
try {
    // Predefined variables
    symbols.declare("k", 1000, false);
    // Predefined constants
    symbols.declare("pi", 3.14159265359, true);
    symbols.declare("e", 2.71828182846, true);
    
    calculate();
    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Uknown exception!\n";
	return 2;
}
