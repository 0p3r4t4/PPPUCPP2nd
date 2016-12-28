# Compiler and tools

To install GCC higher versions than the one provided by Ubuntu:

    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt-get update
    sudo apt-get install gcc-6 g++-6
    sudo apt-get install gcc-5 g++-5

---

To compile with the latest version of g++ in the most recent ISO standard
implementation (no optimization, architectural details or so provided):

    g++-6 -std=c++1z -Wall -o <exec_file> <source_file>

---

To static analyze with _clang-tidy_ (change `-I` argument as needed)

    clang-tidy <source_file> -checks=*,-google-readability-braces-around-statements,-readability-braces-around-statements -- -std=c++11 -I/usr/include/c++/6/

To static analyze with _Clang Static Analyzer_ (redundant if using
_clang-tidy_ already)

    scan-build g++ -std=c++1z <source_file>

To static analyze with _CppCheck_:

    cppcheck --enable=all <source_file>
