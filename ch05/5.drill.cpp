// 5.drill.cpp
//
// Below are 25 code fragments. Each is meant to be inserted into this
// "scaffolding" (see the book, I'm not going to cipy that twice).
//
// Each has zero or more errors. Your task is to find and remove all errors in
// each program. When you have removed those bugs, the resulting program will
// compile, run, and write "Success!" Even if you think you have spotted an
// error, you still need to enter the (original, unimproved) program fragment
// and test it; you may have guessed wrong about what the error is, or there
// may be more errors in a fragment tha you spotted. Also, one purpose of this
// drill is to give you a feel for how your compiler reacts to different kind
// of errors. (...) Do not fix problems by simply deleting a segment; repair
// them by changing, adding, or deleting a few characters.
//
// Comment:
//  I will to take the 25 code fragments in just one program. I guess that, if
//  I fix all the problems, "Success!" will be written 25 times. Of course
//  I will fix them one by one, not doing the next until the current is
//  correct.

#include "std_lib_facilities.h"

int main()
try {
    // Fragment 1 (Compile-time error)
    // Original -> error: ‘Cout’ was not declared in this scope
    // Cout << "Success!\n";
    // Fixed
    cout << "1. Success!\n";

    // Fragment 2 (Compile-time error)
    // Original -> error: missing terminating " character
    // cout << "Success!\n;
    // Fixed
    cout << "2. Success!\n";

    // Fragment 3 (Compile-time error)
    // Original -> error: stray ‘\’ in program 
    //          -> error: missing terminating " character
    //          -> error: ‘n’ was not declared in this scope
    // cout << "Success" << !\n";
    // Fixed
    cout << "3. Success" << "!\n"; // Being literal. cout << "Success!\n"; seems better

    // Fragment 4 (Compile-time error)
    // Original -> error: ‘success’ was not declared in this scope
    // cout << success << '\n';
    // Fixed
    cout << "4. Success!" << '\n';

    // Fragment 5 (Compile-time error)
    // Original -> error: conversion from ‘int’ to non-scalar type ‘std::string
    //             {aka std::basic_string<char>}’ requested
    //          -> error: cannot convert ‘std::string {aka
    //             std::basic_string<char>}’ to ‘int’ in assignment
    // string res = 7;
    // vector<int> v(10);
    // v[5] = res;
    // cout << "Success!\n";
    // Fixed
    int res = 7;
    vector<int> v5(10);
    v5[5] = res;
    cout << "5. Success!\n";

    // Fragment 6 (Compile-time error and Logical error)
    // Original -> 2 * error: no match for call to ‘(Vector<int>) (int)’
    // vector<int> v6(10);
    // v6(5) = 7;
    // if (v6(5) != 7) cout << "Success!\n";
    // Fixed
    vector<int> v6(10);
    v6[5] = 7;
    if (v6[5] == 7) cout << "6. Success!\n";   // Logical error in the comparison

    // Fragment 7 (Compile-time error)
    // Original -> error: ‘cond’ was not declared in this scope
    // if (cond) cout << "Success!\n";
    // else cout << "Fail!\n";
    // Fixed
    bool cond = true;
    if (cond) cout << "7. Success!\n";
    else cout << "Fail!\n";

    // Fragment 8 (Logical error)
    // Original -> prints Fail! instead of Success!
    // bool c8 = false;
    // if (c8) cout << "Success!\n";
    // else cout << "Fail!\n";
    // Fixed
    bool c8 = true;
    if (c8) cout << "8. Success!\n";
    else cout << "Fail!\n";
    
    // Fragment 9 (Logical error)
    // Original -> Print nothing
    // string s9 = "ape";
    // bool c9 = "fool"<s9;
    // if (c9) cout << "Success!\n";
    // Fixed
    string s9 = "ape";
    bool c9 = "fool"<s9;
    if (!c9) cout << "9. Success!\n";

    // Fragment 10 (Logical error)
    // Original -> Prints nothing. We can change the string literals or the
    //             logic behind de condition
    // string s10 = "ape";
    // if (s10 == "fool") cout << "Success!\n";
    // Fixed
    string s10 = "ape";
    if (s10 != "fool") cout << "10. Success!\n";

    // Fragment 11 (Compile-time error and Logical error)
    // Original -> error: no match for ‘operator<’ (operand types are
    //             ‘std::ostream {aka std::basic_ostream<char>}’ and ‘const char [10]’)
    //          -> Prints nothing. We can change the string literals or the
    //             logic behind de condition
    // string s11 = "ape";
    // if (s11 == "fool") cout < "Success!\n"; 
    // Fixed
    string s11 = "ape";
    if (s11 != "fool") cout << "11. Success!\n"; 

    // Fragment 12 (Compile-time error and Logical error)
    // Original -> error: could not convert ‘std::operator+(const
    //             std::basic_string<_CharT, _Traits, _Alloc>&, const _CharT*) [with _CharT
    //             = char; _Traits = std::char_traits<char>; _Alloc
    //             = std::allocator<char>](((const char*)"fool"))’ from
    //             ‘std::basic_string<char>’ to ‘bool’
    //          -> error: no match for ‘operator<’ (operand types are
    //             ‘std::ostream {aka std::basic_ostream<char>}’ and ‘const char[10]’)
    // string s12 = "ape";
    // if (s12 + "fool") cout < "12. Success!\n";
    // Fixed
    string s12 = "ape";
    if (s12 != "fool") cout << "12. Success!\n";

    // Fragment 13 (Logical error)
    // Original -> for-loop control always true; infinite loop.
    // vector<char> v13(5);
    // for (int i=0; 0<v13.size(); ++i)
    //     cout << "13. Success!\n";
    // Fixed (Warning about comparing a int (i) with unsigned integer
    // (v13.size8); using size_t type)
    vector<char> v13(5);
    for (size_t i=0; i<v13.size(); ++i)
        cout << "13. Success!\n";

    // Fragment 14
    // Original -> No error, although I understand is intended to iterate
    //             v14.size() times, so the comparison in the control statement
    //             cuase to iterate once more.
    // vector<char> v14(5);
    // for (int i=0; i<=v14.size(); ++i)
    //     cout << "14. Success!\n";
    // Fixed (size_t again)
    vector<char> v14(5);
    for (size_t i=0; i<v14.size(); ++i)
        cout << "14. Success!\n";

    // Fragment 15 (Logical error)
    // Original -> The magic number 6 do not cover completely the string we
    // want to print.
    // string s15 = "Success!\n";
    // for (int i=0; i<6; ++i)
    //     cout << s15[i];
    // Fixed
    string s15 = "15. Success!\n";
    for (size_t i=0; i<s15.size(); ++i)
        cout << s15[i];

    // Fragment 16 (Compile-time error; Syntax error)
    // Original -> error: ‘then’ was not declared in this scope
    //          -> also, there has no sense to write an if-statement that only
    //             executes one of its branches. A fix to this could be a
    //             simple cout << "Success!\n"; and no more
    // if (true) then
    //     cout << "Success!\n";
    // else 
    //     cout << "Fail\n";
    // Fixed
    if (true) 
        cout << "16. Success!\n";
    else 
        cout << "Fail\n";

    // Fragment 17 (Non-error)
    // Original -> The narrow conversion from int to char in the second line of
    //             code causes the comparison to not "work as expected".
    // int x17 = 2000;
    // char c17 = x17;
    // if (c17 == 2000) cout << "17. Success!\n";
    // Fixed
    int x17 = 2000;
    int c17 = x17;
    if (c17 == 2000) cout << "17. Success!\n";

    // Fragment 18 (Non_error)
    // Original -> It seems it works correctly, although it subscripts the
    //             string out of bounds. Correctly means luckily. std::string
    //             do not perform out of bounds checking with [] operator, so
    //             not exception is thrown.
    // string s18 = "18. Success!\n";
    // for (int i=0; i<1109; ++i)
    //     cout << s18[i];
    // Fixed
    string s18 = "18. Success!\n";
    for (size_t i=0; i<s18.size(); ++i)
        cout << s18[i];

    // Fragment 19 (Compile-time error)
    // Original -> error: missing template arguments before ‘v19’
    //          -> again, one more iteration than expected by making the
    //             for-statement condition <= instead of <
    // vector v19(5);
    // for (int i=0; i<=v19.size(); ++i)
    //     cout << "19. Success!\n";
    // Fixed
    vector<int> v19(5);
    for (size_t i=0; i<v19.size(); ++i)
        cout << "19. Success!\n";

    // Fragment 20 (Logical error)
    // Original -> Infinite while loop, varying value of j but evaluating 
    //             condition with i.
    // int i20 = 0;
    // int j20 = 9;
    // while (i20 < 10)
    //    ++j20;
    // if (j20 < i20)
    //    cout << "20. Success!\n";
    // Fixed
    int i20 = 0;
    int j20 = 9;
    while (i20 < 10)
        ++i20;
    if (j20 < i20)
        cout << "20. Success!\n";

    // Fragment 21 (Run-time error and more)
    // Original -> Floating point exception (Division by 0)
    //          -> Not the only error, read further
    // Comments:
    //  This one makes me feel stupid. In fact, I can't get what this piece of 
    //  code is intended to do, and it has more than one problem.
    //  At first I assume that it intends to test if 2 is a solution to a 
    //  quadratic equation, 2x²-3.5x-6=0 (as infered from
    //  5/(x-2)=2x+0.5). Using the exercise 18 from chapter 4, the solutions are
    //  x = 2.81552 and x = -1.06552. So making x double and value 2.81552
    //  should work, but it doesn't. See
    //  https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
    //  to know why. The solution to this is far more complex that I'm able to
    //  assume at this point of the book.
    //  So, I search the web and found solutions that modify the value of x and
    //  the mathematical expressions to the point to be barely recognizable.
    //  They work but dont's seem very sound to me. 
    //  What have we done to this point in the drill? Fix kinda silly errors.
    //  Is not logical to think this way and reduce everything to a pair of
    //  typographic mistakes?
    //  What happens if we modify the assignment:
    //      d = 5/(x-2)
    //  to
    //      d = 5.0/x+2
    //  the exclusion of parenthesis and the subtitution of - by + seemss to me
    //  like a probable mistake. 
    //  Of course we must include a float point value for the expression to
    //  evaluate in float point as a whole instead of as integers and cause
    //  a narrow result.
    //
    // int x21 = 2;
    // double d21 = 5/(x21-2);
    // if (d21 == 2*x21+0.5)
    //     cout << "21. Success!\n";
    // Fixed
    int x21 = 2;
    double d21 = 5.0/x21+2;
    if (d21 == 2*x21+0.5)
        cout << "21. Success!\n";
    
    // Fragment 22 (Compile-time error)
    // Original -> error: ‘std::string {aka std::basic_string<char>}’ is not
    //             a template
    // string<char> s = "Success!\n";
    // for (int i=0; i<=10; ++i)
    //     cout << s[i];
    // Fixed
    string s22 = "22. Success!\n";
    for (size_t i=0; i<s22.size(); ++i)
        cout << s22[i];

    // Fragment 23 (Compile-time error and more)
    // Original -> error: ‘j23’ was not declared in this scope
    //          -> simply declaring j give us a infinite while loop
    // int i23 = 0;
    // while (i23 < 10)
    //     ++j23;
    // if (j23 < i23)
    //     cout << "23. Success!\n";
    // Fixed
    int i23 = 0;
    int j23 = 0;
    while (i23 < 10)
        ++i23;
    if (j23 < i23)
        cout << "23. Success!\n";

    // Fragment 24 (See fragment 21)
    // Original -> It works at first try, just becuase the if condition
    //             is an assignment. We can not consider it correct.
    // int x24 = 4;
    // double d24 = 5/(x24-2);
    // if (d24 = 2*x24+0.5)
    //     cout << "24. Success!\n";
    // Fixed
    int x24 = 4;
    double d24 = 5.0/(x24-2);
    if (d24 == x24/2.0+0.5)
        cout << "24. Success!\n";

    // Fragment 25 (Compile-time error)
    // Original -> error: no match for ‘operator<<’ (operand types are
    //             ‘std::istream {aka std::basic_istream<char>}’ and ‘const
    //             char [14]’)
    // cin << "25. Success!\n";
    // Fixed
    cout << "25. Success!\n";

    return 0;
}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
    return 2;
}
