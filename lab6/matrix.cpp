#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;
//Задание 1
void task1_1() {
    int N;
    cout << "Введите N (чётное, >6): ";
    cin >> N;

    if (N % 2 != 0 || N <= 6) {
        cout << "Ошибка: N должно быть чётным и больше 6\n";
        return;
    }

    int matrix[100][100];
    srand(time(0));

    // заполняем и выводим исходную
    cout << "\nИсходная матрица:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 41 - 20;
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }

    int replaced_total = 0;
    int max_replaced = 0;
    int best_col = -1;

    // обрабатываем чётные столбцы (индексация с 1)
    for (int j = 0; j < N; j++) {
        if ((j + 1) % 2 == 0) {
            int col_replaced = 0;
            for (int i = 0; i < N; i++) {
                int val = matrix[i][j];
                if (val >= -10 && val <= 10) {
                    matrix[i][j] = 0;
                    replaced_total++;
                    col_replaced++;
                }
            }
            if (col_replaced > max_replaced) {
                max_replaced = col_replaced;
                best_col = j + 1;
            }
        }
    }

    cout << "\nМатрица после замены:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }

    cout << "\nКоличество заменённых элементов: " << replaced_total << endl;
    if (best_col != -1)
        cout << "Номер чётного столбца с максимальным числом замен: " << best_col << endl;
    else
        cout << "Замен не было\n";
}

//Задание 2
void task1_2() {
    int M, N;
    cout << "Введите M (>5) и N (>5): ";
    cin >> M >> N;

    if (M <= 5 || N <= 5) {
        cout << "Ошибка: M и N должны быть больше 5\n";
        return;
    }

    int matrix[100][100];
    srand(time(0));

    cout << "\nИсходная матрица:\n";
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 201 - 100;
            cout << setw(7) << matrix[i][j];
        }
        cout << endl;
    }

    int sorted_cols = 0;
    int squared_cols = 0;
    int zeroed_cols = 0;

    for (int j = 0; j < N; j++) {
        int pos = 0, neg = 0;
        for (int i = 0; i < M; i++) {
            if (matrix[i][j] > 0) pos++;
            else if (matrix[i][j] < 0) neg++;
        }

        if (pos > neg) {
            // сортировка первой половины столбца
            int half = M / 2;
            for (int i1 = 0; i1 < half - 1; i1++) {
                for (int i2 = i1 + 1; i2 < half; i2++) {
                    if (matrix[i1][j] > matrix[i2][j]) {
                        int t = matrix[i1][j];
                        matrix[i1][j] = matrix[i2][j];
                        matrix[i2][j] = t;
                    }
                }
            }
            sorted_cols++;
        }
        else if (pos < neg) {
            for (int i = 0; i < M; i++) {
                matrix[i][j] = matrix[i][j] * matrix[i][j];
            }
            squared_cols++;
        }
        else {
            for (int i = 0; i < M; i++) {
                matrix[i][j] = 0;
            }
            zeroed_cols++;
        }
    }

    cout << "\nМатрица после обработки:\n";
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(7) << matrix[i][j];
        }
        cout << endl;
    }

    cout << "\nСтатистика по столбцам:\n";
    cout << "Отсортировано: " << sorted_cols << endl;
    cout << "Возведено в квадрат: " << squared_cols << endl;
    cout << "Заменено на 0: " << zeroed_cols << endl;
}

// Задание 3
void task1_3() {
    int M, N;
    cout << "Введите M и N (размеры матрицы из 0 и 1): ";
    cin >> M >> N;

    int matrix[100][100];
    cout << "\nВведите матрицу построчно (0 или 1):\n";
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matrix[i][j];
        }
    }

    int total_squares = 0;
    int sizes[100] = {0};   // sizes[k] = количество квадратов со стороной k+1

    // максимально возможная сторона квадрата
    int max_size = M < N ? M : N;

    for (int size = 1; size <= max_size; size++) {
        for (int i = 0; i <= M - size; i++) {
            for (int j = 0; j <= N - size; j++) {
                bool all_ones = true;
                // проверяем квадрат size x size с верхним левым углом (i, j)
                for (int x = i; x < i + size && all_ones; x++) {
                    for (int y = j; y < j + size; y++) {
                        if (matrix[x][y] != 1) {
                            all_ones = false;
                            break;
                        }
                    }
                }
                if (all_ones) {
                    total_squares++;
                    sizes[size - 1]++;
                }
            }
        }
    }

    cout << "\nВсего найдено подматриц: " << total_squares << endl;
    for (int s = 1; s <= max_size; s++) {
        if (sizes[s - 1] > 0) {
            cout << sizes[s - 1] << " подматриц со стороной " << s << endl;
        }
    }
}