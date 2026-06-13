#include "warehouse.h"               
#include <iostream>                   
#include <sstream>                  

using namespace std;                 

int main() {
    int n;                              // количество запросов
    cout << "Введите количество запросов: ";
    cin >> n;                           
    cin.ignore();                       // пропускаем символ новой строки

    for (int i = 0; i < n; ++i) {       // цикл по запросам
        string line;                    // строка с командой
        getline(cin, line);             
        stringstream ss(line);          // разбиваем на слова
        string cmd;                     // первое слово — команда
        ss >> cmd;                      

        if (cmd == "ADD") {             // команда ADD
            string product, address;    // товар и адрес
            int quantity;               // количествwareо
            ss >> product >> quantity >> address; 
            add(product, quantity, address); // вызываем функцию
        }
        else if (cmd == "REMOVE") {     // команда REMOVE
            string product, address;
            int quantity;
            ss >> product >> quantity >> address;
            remove(product, quantity, address);
        }
        else if (cmd == "INFO") {       // команда INFO
            info();
        }
        else {                         
            cout << "Ошибка: неизвестная команда\n";
        }
    }
    return 0;                           
}