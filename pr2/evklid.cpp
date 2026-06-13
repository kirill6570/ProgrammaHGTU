#include "evklid.h"
#include <iostream>
using namespace std;

void evklid(int c, int m) {
    int a = c, b = m;
    int a0 = a, b0 = b;
    int u0 = 1, v0 = 0;
    int u1 = 0, v1 = 1;

    cout << "\nРасширенный алгоритм Евклида" << endl;

    while (b != 0) {
        int q = a / b;
        int r = a % b;
        int u_next = u0 - q * u1;
        int v_next = v0 - q * v1;

        cout << a << " = " << b << " * " << q << " + " << r;
        cout << " | u=" << u_next << " v=" << v_next << endl;

        a = b;
        b = r;
        u0 = u1;
        v0 = v1;
        u1 = u_next;
        v1 = v_next;
    }

    int u = u0, v = v0;
    int d = a;

    cout << "\nНОД(" << a0 << ", " << b0 << ") = " << d << endl;
    cout << a0 << " * " << u << " + " << b0 << " * " << v << " = " << d << endl;

    if (d == 1) {
        if (u < 0) u += m;
        cout << "\nc * d mod m = 1:" << endl;
        cout << c << " * " << u << " mod " << m << " = " << (c * u) % m << endl;
    } else {
        cout << "\nОбратного нет (НОД != 1)" << endl;
    }
}