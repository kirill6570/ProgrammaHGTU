#include "regions.h"
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    int n;
    cout << "Введите количество запросов: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "CHANGE") {
            string region, center;
            ss >> region >> center;
            change(region, center);
        }
        else if (cmd == "RENAME") {
            string old_name, new_name;
            ss >> old_name >> new_name;
            rename_center(old_name, new_name);
        }
        else if (cmd == "ABOUT") {
            string region;
            ss >> region;
            about(region);
        }
        else if (cmd == "ALL") {
            print_all();
        }
        else {
            cout << "Ошибка: неизвестная команда\n";
        }
    }
    return 0;
}