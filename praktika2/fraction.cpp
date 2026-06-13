#include "fraction.h"
#include <iostream>
using namespace std;

void fraction(int a, int b, int d) {
    int a0 = a, b0 = b;

    // коэффициенты для подходящих дробей
    int p0 = 1, q0 = 0;     
    int p1 = 0, q1 = 1;    
    cout << "Цепная дробь " << a << "/" << b << " = [";

    while (b != 0) {
        int quot = a / b;       // частное
        int rem = a % b;        // остаток

        cout << quot;
        if (rem != 0) cout << "; ";

        int p2 = p0 - quot * p1;
        int q2 = q0 - quot * q1;

        a = b; b = rem;
        p0 = p1; q0 = q1;
        p1 = p2; q1 = q2;
    }
    cout << "]" << endl;

    int gcd = a;
    cout << "НОД(" << a0 << ", " << b0 << ") = " << gcd << endl;
    cout << a0 << "*(" << p0 << ") + " << b0 << "*(" << q0 << ") = " << gcd << endl;

    // проверка: d должно делиться на НОД
    if (d % gcd != 0) {
        cout << "Решений нет: " << d << " не кратно НОД=" << gcd << endl;
        return;
    }

    int k = d / gcd;
    int x = p0 * k;
    int y = q0 * k;

    cout << "\nРешение " << a0 << "a + " << b0 << "b = " << d << ":" << endl;
    cout << "a = " << x << endl;
    cout << "b = " << y << endl;
    cout << "Проверка: " << a0 << "*(" << x << ") + " << b0 << "*(" << y << ") = " << a0*x + b0*y << endl;
}