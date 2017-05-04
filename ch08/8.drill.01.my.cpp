// 8.drill.01.my.cpp
//
// Create three files: my.h, my.cpp and use.cpp. The header file my.h contains
//
//      extern int foo;
//      void print_foo();
//      void print(int);
//
// The source code file my.cpp #includes my.h and std_lib_facilities.h, defines
// print_foo() to print the value of foo using cout, and print(int i) to print
// the value of i using cout.
// The source code file use.cpp #includes my.h defines main() to set the
// value of foo to 7 and print it using print_foo(), and to print the value of
// 99 using print(). Note that use.cpp does not #include std_lib_facilities.h
// as it doesn't use any of those facilities.
// Get these files to compile and run. On Windows ... blah blah blah
//
// COMMENTS
//
//  As foo is defined as extern in my.h, we must define it in use.cpp in the
//  global scope for print_foo() to have visibility of it.
//  On Linux, to compile this multi-file program, we must only provide the
//  compiler all the .cpp files. So, using the compile script, executing:
//      ./compile 8.dril.01.*.cpp
//  is enough. And since is that simple I won't investigate about build systems
//  as Make or CMake. Too soon for that.

#include "8.drill.01.my.h"
#include "std_lib_facilities.h"

void print_foo()
{
    cout << "Value of foo is: " << foo << '\n';
}

void print(int i)
{
    cout << "Value of i is: " << i << '\n';
}
