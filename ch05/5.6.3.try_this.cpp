// 5.6.3.try_this.cpp
//
// To see what an uncaught exception error looks like, run a small program that
// uses error() without catching any exception.

#include "std_lib_facilities.h"

// Without catching the exception for error, the output seems very nasty
//
// terminate called after throwing an instance of 'std::runtime_error'
//   what():  Whatever ...
//   Aborted (`core' generated)

// int main()
// {
//     error("Whatever ...");
// }

// Catching the exception, the output is very much controlled by us
//
// Error: Whatever ...

int main()
try {
    error("Whatever ...");
}
catch (exception& e) {
    cout << "Error: " << e.what() << '\n';
}


