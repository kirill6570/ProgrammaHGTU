#include <iostream>
#include "euclid.h"
using namespace std;

int Euclid(int c, int m, int &u, int &v) {
    int r0 = m, r1 = c;
    int x0 = 0, x1 = 1;
    int y0 = 1, y1 = 0;

    cout << "Шаг |  r |  q |  u |  v" << endl;
    cout << "----+----+---+----+----" << endl;

    int step = 1;
    while (r1 != 0) {
        int q = r0 / r1;
        int temp_r = r1;
        r1 = r0 % r1;
        r0 = temp_r;

        int next_x = x0 - q * x1;
        x0 = x1;
        x1 = next_x;

        int next_y = y0 - q * y1;
        y0 = y1;
        y1 = next_y;

        cout << "  " << step << "  | ";
        if (r0 < 10) cout << " ";
        cout << r0 << " | " << q << " | ";
        if (x0 >= 0) cout << " ";
        cout << x0 << " | ";
        if (y0 >= 0) cout << " ";
        cout << y0 << endl;
        step++;
    }

    u = x0;
    v = y0;

    cout << "\nНОД(" << c << ", " << m << ") = " << r0 << endl;
    cout << "u = " << u << endl;
    cout << "v = " << v << endl;
    cout << c << "*" << u << " + " << m << "*" << v << " = " << r0 << endl;

    if (r0 == 1) {
        int d = (u % m + m) % m;
        cout << "\nобратный элемент:" << endl;
        cout << c << "^-1 mod " << m << " = " << d << endl;
        cout << "проверка: " << c << "*" << d << " mod " << m << " = " << (1LL * c * d) % m << endl;
    }

    return r0;
}