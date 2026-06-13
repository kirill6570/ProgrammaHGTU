#include "regions.h"                 
#include <iostream>                   

using namespace std;               

map<string, string> regions;          // пустой словарь регионов
set<string> used_centers;             // пустое множество занятых центров

// CHANGE: создать регион region с административным центром center
void change(const string& region, const string& center) {
    // проверка: не занят ли уже этот центр другим регионом
    set<string>::iterator sit = used_centers.find(center);
    if (sit != used_centers.end()) {
        cout << "Ошибка: " << center << " уже является административным центром другого региона\n";
        return;
    }

    // проверка: не существует ли уже такой регион
    map<string, string>::iterator mit = regions.find(region);
    if (mit != regions.end()) {
        cout << "Ошибка: Регион " << region << " уже создан\n";
        return;
    }

    // добавляем регион и центр
    regions[region] = center;
    used_centers.insert(center);
    cout << "Новый регион " << region << " с административным центром " << center << "\n";
}

// RENAME: переименовать административный центр со старого названия на новое
void rename_center(const string& old_name, const string& new_name) {
    // проверка: не совпадают ли имена
    if (old_name == new_name) {
        cout << "Ошибка: Нельзя переименовать " << old_name << " в то же название\n";
        return;
    }

    // проверка: существует ли старый центр
    set<string>::iterator sit = used_centers.find(old_name);
    if (sit == used_centers.end()) {
        cout << "Ошибка: Административный центр " << old_name << " не найден\n";
        return;
    }

    // проверка: не занято ли уже новое имя другим центром
    sit = used_centers.find(new_name);
    if (sit != used_centers.end()) {
        cout << "Ошибка: " << new_name << " уже является административным центром другого региона\n";
        return;
    }

    // находим регион, у которого центр = old_name, и меняем
    for (map<string, string>::iterator mit = regions.begin(); mit != regions.end(); ++mit) {
        if (mit->second == old_name) {
            mit->second = new_name;
            break;
        }
    }

    // обновляем множества занятых центров
    used_centers.erase(old_name);
    used_centers.insert(new_name);
    cout << "Административный центр " << old_name << " переименован в " << new_name << "\n";
}

// ABOUT: вывести административный центр региона region
void about(const string& region) {
    map<string, string>::iterator mit = regions.find(region);
    if (mit == regions.end()) {
        cout << "Ошибка: Регион " << region << " не найден\n";
        return;
    }
    cout << "Регион " << region << " имеет административный центр " << mit->second << "\n";
}

// ALL: вывести все регионы и их административные центры
void print_all() {
    if (regions.empty()) {
        cout << "Нет созданных регионов\n";
        return;
    }

    bool first = true;                // флаг для форматирования (чтобы не было лишней запятой)
    for (map<string, string>::iterator mit = regions.begin(); mit != regions.end(); ++mit) {
        if (!first) {                 // если не первый, ставим запятую и пробел
            cout << ", ";
        }
        cout << mit->first << " - " << mit->second;
        first = false;
    }
    cout << endl;                     
}