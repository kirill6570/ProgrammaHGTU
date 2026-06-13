#include "port.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Введите максимальный размер стека: ";
    cin >> max_stack_capacity;
    cout << "Введите количество секций судна: ";
    cin >> sections_count;

    string cmd;
    while (true) {
        cin >> cmd;
        if (cmd == "ARRIVE") {
            int weight;
            cin >> weight;
            arrive(weight);
        }
        else if (cmd == "LOAD") {
            load();
            break;
        }
        else {
            cout << "Ошибка: неизвестная команда\n";
        }
    }
    return 0;
}