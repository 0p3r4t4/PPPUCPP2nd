# Exercises (Try these and Drills) from Bjarne Stroustrup's Programming, Principles and Practice Using C++ (2nd Edition)

## Why

After more than a decade without doing any serious programming (some bash and
Python for system administration tasks do not count, I guess) I faced a
required massive modification of an old C program and got bitten again by the
coding snake.

I have two main points to struggle with:

-   A strong sense for a need to **return to the basics**.

-   A **personal debt with C++**, having already used it but just as a
    glorified C with classes (and from I've learned recently, doing so rather
    poorly and mistakenly).

I hope that **_Programming, Principles and Practice Using C++_** could cope
with those.

To be clear, I return to programming as a hobbyist. A full time job as a
sysadmin and two children don't let me be more ambitious. But that's fine to
me.

At first I only want to have a repository that I could synchronize and use
through my two personal systems and, perhaps, my mom's PC while visiting her.
Also, being very used to _subversion_, I saw an opportunity to play a bit with
_git_.  As a very shy person, I choose _GitLab(.com)_ (as opposed to
_GitHub(.com)_, although after the 20170131 database incident I setup a
mirror repository on https://github.com/0p3r4t4/PPPUCPP2nd) mainly, if not
only, by the unlimited private repositories.

As I proceeded through the book I've searched for references to compare my
exercises with. And I found it tremendously useful; find a better solution and
learn from it, catch those little details that I've disregarded, or, in the
rare ocassions when it happens, the triumphal sensation of thinking _"my
solution is better"_, are all enriching experiences.  And since I found
enrichment on others' job, it will be greedy not to share mine (you never know
if, or when, it will be useful to somebody else).

---

## About my exercises

I'm neither a seasoned programmer nor a newbie, so despite learning new things
through the study of the book, I also know a few things explained later or not
exposed at all (not a criticism since the book has its scope).

So, although I've tried to restrict myself to the contents of the book,
sometimes I investigate and go a little bit further. I feel that this behaviour
is somehow enforced by the author in his perspective about what programming is
(or at least in how I understand him). In spite of this, I think I don't
deviate that much, so if somebody studying the book uses this repository as a
reference, there will be no problem to understand these little oddities of
mine.

As a point of fact:

-   I don't use `keep_window_open()` since in Linux it annoys me more that it
    helps me.

-   I tend not to use `error()` function provided by `std_lib_facilities.h`.
    Somehow I feel better throwing on my own.

-   I sometimes, as an user, don't buy the `a program is allowed to terminate
    after finding an error` assumption to the point that an user's input error
    causes no further opportunities.

Some exercises have a companion file with a _.input_ extension. Those are
input samples to quickly test programs with the help of command redirection.

---

## Notes

_In construction_

---

## My review of the book (so far)

_In construction_

---

## Platform, Compilers and Tools

I use mainly Ubuntu and derivative distros as programming platforms. In this
case I've used computers with Ubuntu and Xubuntu with versions ranging from 
14.04 to 16.04 and almost all the time 64 bits versions.

I have used the latest GCC available as direct install from repositories, at
the moment of writing, version 6.2.0. To install it you have to execute the
commands:

    sudo add-apt-repository ppa:ubuntu-toolchain-r/test sudo apt-get update
    sudo apt-get install gcc-6 g++-6

I use to compile the exercises with a rather poor command line:

    g++-6 -std=c++1z -Wall -o <exercise> <exercise>.cpp

Sometimes I perform static analysis on exercises with
[Cppcheck](http://cppcheck.sourceforge.net/) and
[Clang-Tidy](http://clang.llvm.org/extra/clang-tidy/).  See [notes on compiler
and
tools](https://gitlab.com/0p3r4t4/PPPUCPP2nd/blob/master/notes/compiler_and_tools.md)
for more details.

---

## License

I don't actually think that my source code in this repository deserves any
licensing.  It's far from useful in any real-world scenario other than
for educational purpouses (and perhaps not even that).

I don't care about what could be done with the source code, so I choose a [MIT
License](https://gitlab.com/0p3r4t4/PPPUCPP2nd/blob/master/LICENSE) for one
sole reason: the disclaimer of the warranty.

Said that, there are exceptions to my, almost complete, lack of interest in the
licensing terms. Such exceptions are:

-   `std_lib_facilities.h` file present in each chapter directory and other
    supporting code supplied by Bjarne Stroustrup in the [support site for
    the book](http://www.stroustrup.com/Programming) are, of course,
    copyrighted by him. 

-   Problem statements heading almost every source file are excerpts from the
    book put there for my own convenience, and are, of course, copyrighted by
    Bjarne Stroustrup.

---

## Other sources for exercises

If you want to examine other solutions and coding flavours, don't hesitate on
taking a look at these:

Of course, [Bjarne Stroustrup's Selected Exercise Solutions](http://www.stroustrup.com/Programming/Solutions/exercise_solutions.html)  

Also (with no order of preference):

-   (broken link) [TheParryEffect - Programming](http://theparryeffectprogramming.blogspot.co.uk)
-   [Nick Maclaren's Computing Courses - Programming in Modern C++ - Drill and Exercise Code](http://people.ds.cam.ac.uk/nmm1/C++/Exercises/)
-   <https://github.com/bewuethr/stroustrup_ppp>
-   <https://github.com/thelastpolaris/Programming-Principles-and-Practice-Using-C->
-   <https://github.com/Jtaim/Programming-Principles-and-Practice-Using-Cpp>
