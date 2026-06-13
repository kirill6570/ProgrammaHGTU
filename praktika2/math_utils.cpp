#include "math_utils.h"
#include <iostream>

using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// бинарное возведение: a^x mod p
int binaryPow(int a, int x, int p) {
    int res = 1;
    a %= p; // упрощаем основание
    
    cout << "промежуточные шаги бинарного возведения" << endl;
    while (x > 0) {
        // если степень нечетная, умножаем результат на текущее a
        if (x % 2 == 1) {
            res = (1LL * res * a) % p; 
        }
        // возводим основание в квадрат
        cout << "текущая степень x = " << x << ", a = " << a << ", промежуточный итог = " << res << endl;
        a = (1LL * a * a) % p;
        x /= 2; // сдвиг вправо переход к следующему биту
    }
    return res;
}

int fermatPow(int a, int x, int p) {
    cout << "применение теоремы Ферма" << endl;
    
    // проверка условий теоремы
    if (!isPrime(p)) {
        cout << "число p не простое. Теорема Ферма неприменима." << endl;
        return -1;
    }
    if (a % p == 0) {
        cout << "a делится на p. Теорема Ферма неприменима." << endl;
        return 0;
    }

    // по теореме: a^x mod p = a^(x mod (p-1)) mod p
    int new_x = x % (p - 1);
    cout << "упрощаем степень: " << x << " mod (" << p << "-1) = " << new_x << endl;
    
    return binaryPow(a, new_x, p);
}