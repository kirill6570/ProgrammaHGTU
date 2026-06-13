#include "tram.h"
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

        if (cmd == "CREATE_TRAM") {
            string name;
            int cnt;
            ss >> name >> cnt;
            vector<string> stops(cnt);
            for (int j = 0; j < cnt; j++) ss >> stops[j];
            create_tram(name, stops);
        }
        else if (cmd == "TRAMS") {
            print_trams();
        }
        else if (cmd == "TRAMS_IN_STOP") {
            string stop;
            ss >> stop;
            trams_in_stop(stop);
        }
        else if (cmd == "STOPS_IN_TRAM") {
            string name;
            ss >> name;
            stops_in_tram(name);
        }
        else {
            cout << "Ошибка: неизвестная команда\n";
        }
    }
    return 0;
}