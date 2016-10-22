#include "std_lib_facilities.h"

int main()
{
    double d = 0;
    while (cin >> d){
        int i {d};
        char c {i}; // Esto debería provocar un aviso en compilación mientras que
        char c2 {1000}; // Esto debería provocar un error de compilación
        int i2 = c;
        cout << "d==" << d
            << " i==" << i
            << " i2==" << i2
            << " char(" << c << ")\n";
    }
}
