#include "warehouse.h"
#include <iostream>
#include <iomanip>

using namespace std;

map<string, Cell> warehouse;
int total_cells = ZONES * SHELVES_PER_ZONE * SECTIONS * ROWS;
int occupied_cells = 0;

string make_address(char zone, int shelf, int section, int row) {
    string addr;
    addr += zone;
    if (shelf < 10) addr += "0";
    addr += to_string(shelf);
    addr += to_string(section);
    addr += to_string(row);
    return addr;
}

void add(const string& product, int quantity, const string& address) {
    if (quantity <= 0 || quantity > 10) {
        cout << "Ошибка: количество должно быть от 1 до 10\n";
        return;
    }

    map<string, Cell>::iterator it = warehouse.find(address);

    if (it == warehouse.end()) {
        Cell new_cell;
        new_cell.product = product;
        new_cell.quantity = quantity;
        warehouse[address] = new_cell;
        occupied_cells++;
        cout << "Добавлено " << quantity << " " << product << " в " << address << "\n";
    } else {
        Cell& existing = it->second;
        if (existing.product != product) {
            cout << "Ошибка: Ячейка " << address << " занята товаром " << existing.product << "\n";
        } else {
            int new_q = existing.quantity + quantity;
            if (new_q > 10) {
                cout << "Ошибка: Превышена вместимость ячейки (максимум 10)\n";
            } else {
                existing.quantity = new_q;
                cout << "Добавлено " << quantity << " " << product << " (остаток: " << new_q << ")\n";
            }
        }
    }
}

void remove(const string& product, int quantity, const string& address) {
    if (quantity <= 0) {
        cout << "Ошибка: количество должно быть положительным\n";
        return;
    }

    map<string, Cell>::iterator it = warehouse.find(address);
    if (it == warehouse.end()) {
        cout << "Ошибка: Ячейка " << address << " не найдена\n";
        return;
    }

    Cell& cell = it->second;
    if (cell.product != product) {
        cout << "Ошибка: Товар " << product << " не найден в ячейке " << address << "\n";
        return;
    }

    if (cell.quantity < quantity) {
        cout << "Ошибка: Недостаточно товаров для удаления\n";
        return;
    }

    cell.quantity -= quantity;
    cout << "Удалено " << quantity << " " << product;

    if (cell.quantity == 0) {
        warehouse.erase(it);
        occupied_cells--;
        cout << " (ячейка освобождена)\n";
    } else {
        cout << " (остаток: " << cell.quantity << ")\n";
    }
}

void info() {
    double total_percent = (double)occupied_cells / total_cells * 100.0;
    cout << fixed << setprecision(2);
    cout << "Загруженность склада: " << total_percent << "%\n";

    char zones[2] = {'A', 'B'};
    for (int zi = 0; zi < 2; ++zi) {
        char zone = zones[zi];
        int occupied_in_zone = 0;
        int total_in_zone = SHELVES_PER_ZONE * SECTIONS * ROWS;

        for (map<string, Cell>::iterator it = warehouse.begin(); it != warehouse.end(); ++it) {
            if (it->first[0] == zone) {
                occupied_in_zone++;
            }
        }
        double zone_percent = (double)occupied_in_zone / total_in_zone * 100.0;
        cout << "Загруженность зоны " << zone << ": " << zone_percent << "%\n";
    }

    cout << "Заполненные ячейки:\n";
    for (map<string, Cell>::iterator it = warehouse.begin(); it != warehouse.end(); ++it) {
        cout << "  " << it->first << ": " << it->second.product << " (" << it->second.quantity << ")\n";
    }

    cout << "Пустые ячейки (пример):\n  ";
    int shown = 0;
    for (int zi = 0; zi < 2; ++zi) {
        char zone = zones[zi];
        for (int shelf = 1; shelf <= SHELVES_PER_ZONE; ++shelf) {
            for (int sec = 1; sec <= SECTIONS; ++sec) {
                for (int row = 1; row <= ROWS; ++row) {
                    string addr = make_address(zone, shelf, sec, row);
                    map<string, Cell>::iterator it = warehouse.find(addr);
                    if (it == warehouse.end()) {
                        cout << addr << " ";
                        shown++;
                        if (shown >= 10) goto enough;
                    }
                }
            }
        }
    }
enough:
    cout << endl;
}