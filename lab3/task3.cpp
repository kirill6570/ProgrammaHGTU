#include <iostream>  
#include <vector>    
#include <algorithm> 

using namespace std; 

int gcd(int a, int b) {
    while (b) {               // пока b не ноль
        int t = b;            // запоминаем b
        b = a % b;            // новое b = остаток от деления a на b
        a = t;                // a становится старым b
    }
    return a;                 // когда b = 0, a и есть НОД
}


int binpow(int base, int exp) {
    int res = 1;              // результат, начинаем с 1
    while (exp) {             // пока показатель не ноль
        if (exp & 1) {        // если последний бит показателя = 1
            res *= base;      // умножаем результат на основание
        }
        base *= base;         // основание возводим в квадрат
        exp >>= 1;            // сдвигаем показатель вправо (делим на 2)
    }
    return res;               // возвращаем base^exp
}

vector<int> stirling2(int n) { // Числа Стирлинга второго рода для заданного n
    vector<int> s(n + 1, 0);   // создаём вектор размером n+1, заполняем нулями
    s[1] = 1;                  // S(1,1) = 1 (база)
    for (int i = 2; i <= n; ++i) {        // для n от 2 до заданного
        for (int k = i; k >= 1; --k) {    // идём от k=i вниз до 1
            s[k] = s[k - 1] + k * s[k];   // формула: S(i,k) = S(i-1,k-1) + k * S(i-1,k)
        }
        s[0] = 0;             // S(i,0) всегда 0 для i > 0
    }
    return s;                 // возвращаем вектор чисел Стирлинга
}

int main() {
    int a, b;                 // объявляем переменные a и b
    cin >> a >> b;            

    if (b == 1) {             // если знаменатель 1, ряд расходится
        cout << "infinity" << endl;   
        return 0;             
    }
    vector<int> S = stirling2(a);   // получаем числа Стирлинга для a
    int C = 0;                      // переменная для хранения суммы
    for (int k = 1; k <= a; ++k) {
        int fact = 1;               // начинаем факториал с 1
        for (int i = 2; i <= k; ++i) {
            fact *= i;              // умножаем, чтобы получить k!
        }
        int pow_b1 = binpow(b - 1, a - k);   // (b-1)^(a-k)

        C += S[k] * fact * pow_b1;   
    }
    int numerator = b * C;                    // числитель дроби
    int denominator = binpow(b - 1, a + 1);   // знаменатель дроби

    int g = gcd(numerator, denominator);      // находим НОД
    numerator /= g;                           // сокращаем числитель
    denominator /= g;                         // сокращаем знаменатель

    cout << numerator << "/" << denominator << endl;   // выводим дробь
    return 0;                             
}