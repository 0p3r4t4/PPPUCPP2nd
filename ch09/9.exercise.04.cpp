// 9.exercise.04.cpp
//
//  Look at the headache-inducing last example of §8.4. Indent it properly and
//  explain the meaning of the construct. Note that the example doesn't do
//  anything meaningful; it is pure obfuscation.
//
//  COMMENTS
//
//  The code do not link since there is no main() defined globally (and if we
//  move the main() we have outside, the program compiles but runs into a
//  segmentation fault. Nice.
//
//  The snippet defines a class named X with these data members:
//      - m, integer type.
//  and these function members:
//      - f, g, X, m3 and main
//      
//  f(int x) defines a class Y within it (§8.4 tell us to avoid this), declare
//  an int variable named m, assign to it the x parameter, declare an object of
//  type Y and calls itself with the value returned by Y.f(), that is always 1.
//  Previously assigned m is used for nothing. and since the function call
//  itself without an ending control, it conforms an infinite recursion that
//  leds to error. Also, in case we solve this and finally returns a value, f()
//  return type is declared void, so another bug arises.
//
//  The Y class has a data member, m, that is never used.
//
//  g(int m) executes a logical evaluation on an int (not very wise, but it
//  would work to differentiate if m is 0 or not) and each branch of the
//  if-else-statemente led to infinite recursion again. 
//
//  X() is the default constructor.
//  m3() does nothing.
//
//  The main() is clearly misplaced or poorly named. It just declares an X
//  typed variable and calls its f() with a 2 argument. And with the previous
//  explanations, this leads also to segmentation fault.

struct X {
    void f(int x) {
        struct Y {
            int f() { return 1; }
            int m;
        };
        int m;
        m = x;
        Y m2;
        return f(m2.f());
    }
    
    int m;

    void g(int m) {
        if (m) f(m+2);
        else {
            g(m+2);
        }
    }

    X() { }
    void m3() { }

    void main() {
        X a;
        a.f(2);
    }
};
