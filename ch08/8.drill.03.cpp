// 8.drill.03.cpp
//
// Write a program using a single file containing three namespaces X, Y and Z
// so that the following main() (see below) works correctly.
//
// Each namespace needs to define a variable called var and a function called
// print() that outputs the appropiate var using cout.
//
// COMMENT
//
//  clang-tidy protest with llvm-namespace-comment, recommendation to put a
//  comment to indicate the end of the namespace. I've got no problem to do it.
//  It also marks using-directives (using namespace Y) as bad, and prefers
//  using-declarations, but that goes against the exercise's objective.

#include "std_lib_facilities.h"

namespace X {
int var {0};
void print() { cout << "X::var value is " << var << '\n'; }
} // End of namespace X

namespace Y {
int var {0};
void print() { cout << "Y::var value is " << var << '\n'; }
} // End of namespace Y

namespace Z
{
int var {0};
void print() { cout << "Z::var value is " << var << '\n'; }
} // End of namespace Z

int main()
{
    X::var = 7;
    X::print();     // print X's var
    using namespace Y;
    var = 9;
    print();        // print Y's var
    {
        using Z::var;
        using Z::print;
        var = 11;
        print();    // print Z's var
    }
    print();        // print Y's var
    X::print();     // print X's var
}
