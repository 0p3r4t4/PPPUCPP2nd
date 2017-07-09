// 10.exercise.07.cpp
//
//  Make a version of the calculator from Chapter 7 that accepts Roman numerals
//  rather than the usual Arabic ones, for example, XXI + CIV == CXXV.
//
// COMMENTS
//
//  I take 7.exercise.09.cpp as the base for this one.
//  Also I'll improve Roman_int class from previous exercise to add support for
//  arithmetic operations.
//
//  This exercise is merely put here to make me regret not to have done
//  exercise 10 from chapter 7.
//
//  The changes to grammar are minimal; [floating-point-literal] will be
//  replaced with [roman-numeral-literal], and we have to rethink about
//  functions (mainly sqrt) and representation range of Roman numerals.
//
//  And Roman numerals have no negative or zero concept, so must be taken into
//  account. Unary + and - operatorss make no sense either.
//
//  Using Roman_int in the calculator exposes a bug in Roman::get_particle,
//  since it doesn't putback to input stream '\n' chars.
//
// This program implements a basic expression calculator based in this input
// grammar:
//
//  Calculation:
//      Statement
//      Command
//      Print
//      Calculation Statement
//  Statement:
//      Declaration
//      Assignment
//      Expression
//  Command:
//      "help"
//      "symbols"
//      "quit"
//  Print:
//      ";"
//      "\n"
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
//      Name
//      Function"("Arguments")"
//  Function:
//      "sqrt"
//      "pow"
//  Arguments:
//      Expression
//      Argument","Expression
//  Number:
//      [roman-numeral-literal]
//  Name:
//      [alphabetic-char]
//      Name[alphabetic-char]
//      Name[digit-char]
//      Name"_"
//
// Input comes from cin through the Token_stream called ts.

#include "std_lib_facilities.h"
#include "10.exercise.07.roman.h"

// Models a grammar token from input
class Token {
public:
    // kind is always needed while value and name are initialized depending on
    // the needs of each kind. Thus, three distinct constructors are defined.
	char kind;  
    Roman::Roman_int value;
	string name;

	Token(char ch) :kind{ch} { }
	Token(char ch, Roman::Roman_int val) :kind{ch}, value{val} { }
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
const char command = 'c';
const char print = ';';
const char number = '8';
const char name = 'a';
const char sqrtfun = 's';
const char powfun = 'p';
// Keywords
const string declkey = "let";
const string constkey = "const";
const string symkey = "symbols";
const string helpkey = "auxilium";
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

	char ch = ' ';

    // Discard every "space" character except '\n'
	while (isspace(ch) && ch != '\n')
        ch = cin.get();   // instead of >> to capture spaces (and other separators)

	switch (ch) {
	case ';':       // We now have two alternatives for print, so we group them
	case '\n':
	    return Token{print};
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
	case ',':   // Added as separator for function argument lists
		return Token{ch};   // These literals directly define Token kind
    case 'M': case 'D': case 'C': case 'L':
    case 'X': case 'V': case 'I':               // Roman numeral literal
    {
        cin.putback(ch);
        Roman::Roman_int val;
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
			if (s == quitkey) return Token{command, quitkey};
			if (s == helpkey) return Token{command, helpkey};
			if (s == symkey) return Token{command, symkey};
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
    Roman::Roman_int value;
	bool constant;
};

class Symbol_table {
    vector<Variable> var_table;
public:
    Roman::Roman_int get(string s);
    void set(string s, Roman::Roman_int d);
    bool is_declared(string s);
    void declare(string s, Roman::Roman_int d, bool c);
    void print();
};

Roman::Roman_int Symbol_table::get(string s)
{
	for (const Variable& v : var_table)
	    if (v.name == s) return v.value;
	error("get: undefined name ", s);
}

void Symbol_table::set(string s, Roman::Roman_int d)
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

void Symbol_table::declare(string s, Roman::Roman_int d, bool c)
{
    // This can be seen as redundant with declaration() doing the same check.
    // But remember that we directly declare variables and constants in the main
    // body, so it's well placed here.
    if (is_declared(s)) error(s, "is declared twice");
    var_table.push_back(Variable{s, d, c});
}

void Symbol_table::print()
{
    for (Variable v : var_table) {
        cout << v.name << " = " << v.value << " (" << v.value.as_int() << ')';
        if (v.constant) cout << " [constant]";
        cout << '\n';
    }
}

Symbol_table symbols;
Token_stream ts;

Roman::Roman_int expression();

Roman::Roman_int eval_function(char c)
// Evaluates function of kind c. The next on input must be "("Expression")".
{
    vector<Roman::Roman_int> args;    // Vector to store (variable number) of function 
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
        return Roman::Roman_int(narrow_cast<int>(sqrt(args[0].as_int())));
    case powfun:
        return Roman::Roman_int(pow(args[0].as_int(), args[1].as_int()));
    default:
        // In case we have defined the name as a token for Function rule but
        // forgot to implement its evaluation
        error("Function not implemented");
    }
}

Roman::Roman_int primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	Roman::Roman_int d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
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

Roman::Roman_int term()
{
	Roman::Roman_int left = primary();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	Roman::Roman_int d = primary();
			left /= d;
			break;
		}
        case '%':
        {   Roman::Roman_int d = primary();
            left %= d;
            break;
        }
		default:
			ts.putback(t);
			return left;
		}
	}
}

Roman::Roman_int expression()
{
	Roman::Roman_int left = term();
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

Roman::Roman_int assignment()
{
    // We get there by knowing that a name and an '=' come next.
    Token t = ts.get();
    string var_name = t.name;
    if (!symbols.is_declared(var_name)) error(var_name, " has not been declared");

    ts.get(); // Get rid of the '='
    Roman::Roman_int d = expression();
    symbols.set(var_name, d);
    return d;
}

Roman::Roman_int declaration()
{
    // Get the declaration keyword token to define if it's constant or not
    Token t = ts.get();

    // Check part by part of Declaration gramamr rule behind "let" or "const"
	Token t2 = ts.get();
	if (t2.kind != name) error ("name expected in declaration");
	string var_name = t2.name;
	if (symbols.is_declared(var_name)) error(var_name, " declared twice");

	Token t3 = ts.get();
	if (t3.kind != '=') error("= missing in declaration of " ,var_name);

	Roman::Roman_int d = expression();
	symbols.declare(var_name, d, t.kind == constant);
	return d;
}

Roman::Roman_int statement()
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

void print_help()
{
    cout << "\n\tTiny Roman calculator help.\n"
            "\n\tBASIC SYNTAX\n\n"
            "\tFinish an expression with ; or new line to print results.\n"
            "\tSupported operands: *, /, %, +, -, = (assignment).\n"
            "\tYou can use parenthesis to group expressions: IV*(II+III).\n"
            "\n\tCOMMANDS\n\n"
            "\tauxilium   Prints this help message.\n"
            "\tsymbols    Prints currently declared variables and constants.\n"
            "\tquit       Exit the program.\n"
            "\n\tFUNCTIONS\n\n"
            "\tsqrt(n)    Square root of n.\n"
            "\tpow(n,e)   e power of n, with e an integer number.\n"
            "\n\tVARIABLES\n\n"
            "\tVariable names must be composed of alphanumeric characters and '_',\n"
            "\tand must start with an alphabetic character except M, D, C, L,\n"
            "\tX, V and I, as they express Roman numerals.\n\n"
            "\tlet var = expr     Declares a variable var and initializes it\n"
            "\t                   with expr expression evaluation value.\n\n"
            "\tconst var = expr   Declares and initializes a constant named var.\n\n"
            "\tvar = expr         Assigns a new value to a previously declared\n"
            "\t                   variable.\n\n"
            "\tPredefined variables:\n"
            "\t\tk    M (1000)\n\n";
}

void calculate()
{
	while(true) 
	try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();   // Remove print commands
		if (t.kind == command) {
		    if (t.name == quitkey) return;
            if (t.name == helpkey) print_help();
            if (t.name == symkey) symbols.print();
            ts.ignore(print); // To ignore whatever comes after a command.
        }
		else {
            ts.putback(t);
            cout << result << statement() << '\n';
        }
	}
	catch (Roman::Not_roman& e) {
	    cerr << "Result out of bounds of Roman numeral representation\n";
	    clean_up_mess();
	}
	catch(exception& e) {
		cerr << e.what() << '\n';
		clean_up_mess();    // Discard remaining input and prompt user again
	}
}

int main()
try {
    // Predefined variables
    symbols.declare("k", Roman::Roman_int{"M"}, false);
    
    cout << "Tiny Roman calculator. Write auxilium for help.\n";
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
