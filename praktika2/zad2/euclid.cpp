#include <iostream>
#include "euclid.h"
using namespace std;

int Euclid(int c, int m, int &u, int &v) {
    int r0 = m, r1 = c;
    int x0 = 0, x1 = 1; // Коэффициенты для c (u)
    int y0 = 1, y1 = 0; // Коэффициенты для m (v)

    cout << "Шаг | r | q | u | v" << endl;

    int step = 1;
    while (r1 != 0) {
        int q = r0 / r1;
        
        // Обновление остатка
        int temp_r = r1;
        r1 = r0 % r1;
        r0 = temp_r;

        // Обновление коэф u 
        int next_x = x0 - q * x1;
        x0 = x1;
        x1 = next_x;

        // Обновление коэф v 
        int next_y = y0 - q * y1;
        y0 = y1;
        y1 = next_y;

        cout << "  " << step << " | " << r0 << " | " << q << " | " << x0 << " | " << y0 << endl;
        step++;
    }

    u = x0;
    v = y0;
    return r0; 
}