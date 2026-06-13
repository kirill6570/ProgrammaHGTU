//task3.cpp     
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int X0, A, B, C, N;

    cout << "Задание 3: Линейный конгруэнтный генератор (LCG)\n";
    cout << "Введите количество чисел для генерации (N): ";
    cin >> N;
    cout << "Введите X0, A, B, C: ";
    cin >> X0 >> A >> B >> C;

    vector<int> seq;
    int x = X0;
    // генерируем последовательность
    for (int i = 0; i < N; i++) {
        seq.push_back(x);
        x = (A * x + B) % C;
        // проверяем на повтор
        for (size_t j = 0; j < seq.size(); j++) {
            if (x == seq[j]) {
                // красивый вывод с текстом
                cout << "\nСгенерированная последовательность:\n";
                for (int v : seq) cout << v << " ";
                cout << "\n\nПовтор начинается с индекса " << j << " (элемент " << seq[j] << ")\n";
                return 0;
            }
        }
    }

    // если повтор не найден
    cout << "\nСгенерированная последовательность:\n";
    for (int v : seq) cout << v << " ";
    cout << "\n\nПовторений в последовательности не обнаружено.\n";

    return 0;
}