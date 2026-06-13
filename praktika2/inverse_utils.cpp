#include <iostream>
#include "inverse_utils.h"

using namespace std;

int findModularInverse(int c, int m) {
    int r0 = m, r1 = c;
    int x0 = 0, x1 = 1; // Коэффициенты для поиска d

    cout << "Вычисление взаимообратного числа c^-1 mod m" << endl;
    cout << "Шаг | r (остаток) | q (частное) | x (коэффициент)" << endl;
    cout << "-----------------------------------------------" << endl;

    int step = 1;
    while (r1 != 0) {
        int q = r0 / r1;
        
        // Обновляем остаток r
        int temp_r = r1;
        r1 = r0 % r1;
        r0 = temp_r;

        // Обновляем коэффициент x (который станет d)
        int next_x = x0 - q * x1;
        x0 = x1;
        x1 = next_x;

        cout << step << " | " << r0 << " | " << q << " | " << x0 << endl;
        step++;
    }

    // Если НОД (последний ненулевой остаток r0) не равен 1, обратного числа нет
    if (r0 != 1) {
        return -1;
    }

    // Приводим результат к положительному числу по модулю m
    int d = (x0 % m + m) % m;
    return d;
}