    #include "tram.h"                       
    #include <iostream>
    using namespace std;                      


    map<string, vector<string> > trams;        // пустой словарь трамваев
    map<string, set<string> > stop_to_trams;   // пустой словарь остановок

    void create_tram(const string& name, const vector<string>& stops) {
        map<string, vector<string> >::iterator it = trams.find(name);    // проверяем, нет ли уже трамвая с таким именем
        if (it != trams.end()) {
            cout << "Ошибка: Трамвай " << name << " уже существует\n";
            return;                            
        }
        trams[name] = stops;     // сохраняем маршрут в основной словарь

        for (vector<string>::const_iterator sit = stops.begin(); sit != stops.end(); ++sit) {
            const string& stop = *sit;         // текущая остановка
            stop_to_trams[stop].insert(name);  // добавляем трамвай во множество
        }

        cout << "Трамвай " << name << " создан\n";
    }

    void print_trams() {
        if (trams.empty()) {
            cout << "Нет созданных трамваев\n";
            return;
        }

        for (map<string, vector<string> >::iterator it = trams.begin(); it != trams.end(); ++it) {
            cout << "Трамвай " << it->first << ": ";
            // перебираем все остановки этого трамвая
            for (vector<string>::iterator vit = it->second.begin(); vit != it->second.end(); ++vit) {
                cout << *vit << " ";           // выводим каждую остановку
            }
            cout << endl;                      // переводим строку после каждого трамвая
        }
    }

    void trams_in_stop(const string& stop) {
        map<string, set<string> >::iterator it = stop_to_trams.find(stop);

        if (it == stop_to_trams.end()) {
            cout << "Остановка " << stop << " не найдена\n";
            return;
        }

        cout << "Остановку " << stop << " обслуживают трамваи: ";
        // перебираем все трамваи из множества у этой остановки
        for (set<string>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit) {
            cout << *sit << " ";               // выводим каждый трамвай
        }
        cout << endl;                          // переводим строку
    }

    void stops_in_tram(const string& name) {
        // ищем трамвай в словаре trams
        map<string, vector<string> >::iterator it = trams.find(name);

        // если не нашли
        if (it == trams.end()) {
            cout << "Ошибка: Трамвай " << name << " не найден\n";
            return;
        }

        cout << "Трамвай " << name << " проходит через остановки:\n";

        // перебираем все остановки этого трамвая
        for (vector<string>::iterator vit = it->second.begin(); vit != it->second.end(); ++vit) {
            const string& stop = *vit;         // текущая остановка
            cout << "  " << stop << ": ";

            // получаем множество всех трамваев на этой остановке
            set<string>& all_trams = stop_to_trams[stop];
            bool first = true;                 // флаг для форматирования (чтобы не было лишней запятой)

            for (set<string>::iterator sit = all_trams.begin(); sit != all_trams.end(); ++sit) {
                if (*sit != name) {            // исключаем текущий трамвай
                    if (!first) {              // если не первый, ставим запятую и пробел
                        cout << ", ";
                    }
                    cout << *sit;              // выводим имя другого трамвая
                    first = false;             // сбрасываем флаг
                }
            }

            if (first) { // если других трамваев не было (first остался true)
                cout << "нет других трамваев";
            }
            cout << endl;                      
        }
    }