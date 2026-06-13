#include "obr.h"
#include <iostream>
using namespace std;

int obr(int c, int m) {
    int a = c, b = m;
    int a0 = a, b0 = b;
    int u0 = 1, v0 = 0;
    int u1 = 0, v1 = 1;

    cout << "\n=== Расширенный алгоритм Евклида ===" << endl;

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

    int u = u0;
    int d = a;

    cout << "\nНОД(" << a0 << ", " << b0 << ") = " << d << endl;

    if (d != 1) {
        cout << "Обратного нет!" << endl;
        return -1;
    }

    if (u < 0) u += m;

    cout << "\n=== Обратный элемент ===" << endl;
    cout << c << "^{-1} mod " << m << " = " << u << endl;
    cout << "Проверка: " << c << " * " << u << " mod " << m << " = " << (c * u) % m << endl;

    return u;
}