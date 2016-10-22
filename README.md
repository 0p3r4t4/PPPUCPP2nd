Exercises (Try these and Drills) from Bjarne Stroutrup's Programming, Principles and Practice Using C++ (2nd Edition)
============================================================

Platform and Compilers
----------------------

I use mainly Ubuntu and derivative distros as programming platforms. 
Through my trip on this book I've used computers with Ubuntu 14.04 and
Xubuntu 16.04, both on 64 bits version.

I have used the latest GCC available as direct install from repositories, at
the moment of writing, version 6.2.0. To install it you have to execute the commands:

    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt-get update
    sudo apt-get install gcc-6 g++-6

The majority of the exercises were compiled with:

    g++-6 -std=c++1z -Wall -o <exercise>.out <exercise>.cpp

Sometimes I've statically analyze exercises with
[Cppcheck](http://cppcheck.sourceforge.net/). Feel free to Google about it and
consider other alternatives for static analysis as
[Clang-Tidy](http://clang.llvm.org/extra/clang-tidy/).


Other sources for exercises
---------------------------

If you want to examine other solutions and coding flavours, don't hesitate on taking a look at
these:

[Bjarne Stroustrup's Selected Exercise
Solutions](http://www.stroustrup.com/Programming/Solutions/exercise_solutions.html)  
On Github:  
* https://github.com/bewuethr/stroustrup_ppp
* https://github.com/thelastpolaris/Programming-Principles-and-Practice-Using-C-

