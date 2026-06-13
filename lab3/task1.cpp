#include <iostream>
#include <iomanip>

using namespace std;

// Функция, заданная графически (вариант 15, исправленная)
// Вычисляет значение y по графику для заданного x
double func(double x) {
    // Участок 1: x <= -6 -> y = 2x + 14 (при x=-6: 2*(-6)+14 = 2)
    if (x <= -6) {
        return 2 * x + 14;
    }
    // Участок 2: -6 < x <= 0 -> y = 2x + 10
    else if (x <= 0) {
        return 2 * x + 10;
    }
    // Участок 3: 0 < x <= 5 -> y = -2x + 10
    else if (x <= 5) {
        return -2 * x + 10;
    }
    // Участок 4: 5 < x <= 8 -> y = 2x - 10
    else if (x <= 8) {
        return 2 * x - 10;
    }
    // Участок 5: x > 8 -> y = 6
    else {
        return 6;
    }
}

int main() {
    double xn, xk, dx;

    cout << "Введите Xнач: ";
    cin >> xn;
    cout << "Введите Xкон: ";
    cin >> xk;
    cout << "Введите шаг dx: ";
    cin >> dx;

    if (dx <= 0) {
        cout << "Ошибка: шаг должен быть положительным" << endl;
        return 1;
    }

    cout << fixed << setprecision(2);
    cout << "\n-----------------------------" << endl;
    cout << "|     x     |     y     |" << endl;
    cout << "-----------------------------" << endl;

    for (double x = xn; x <= xk + 1e-9; x += dx) {
        cout << "| " << setw(8) << x << " | " << setw(8) << func(x) << " |" << endl;
    }

    cout << "-----------------------------" << endl;

    return 0;
}