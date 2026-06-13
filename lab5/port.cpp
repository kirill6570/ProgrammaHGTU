#include "port.h"               
#include <iostream>              
#include <algorithm>             

using namespace std;             

// Инициализация глобальных переменных
vector<Stack> stacks;              // пока нет ни одного стека
int max_stack_capacity = 0;        // будет задано пользователем
int sections_count = 0;            // будет задано пользователем
int next_container_id = 1;         // первый контейнер получит C001

// Генератор идентификатора контейнера
string make_container_id() {
    string id = "C";               // всегда начинаем с буквы C
    if (next_container_id < 10) { 
        id += "00";
    } else if (next_container_id < 100) { 
        id += "0";
    }
    id += to_string(next_container_id); // добавляем число
    next_container_id++;           // увеличиваем счётчик для следующего
    return id;                     
}

void arrive(int weight) {
    string id = make_container_id(); // получаем новый идентификатор

    for (vector<Stack>::iterator it = stacks.begin(); it != stacks.end(); ++it) {
        if (it->current_weight + weight <= max_stack_capacity) {
            // кладём пару (id, вес) в стек
            it->containers.push(pair<string, int>(id, weight));
            it->current_weight += weight; // увеличиваем вес стека
            cout << "Контейнер " << id << " размещен в стек " << it->id << "\n";
            return;                // выходим из функции
        }
    }

    int new_id = stacks.size() + 1; // номер нового стека
    Stack new_stack;               // создаём временную структуру
    new_stack.id = new_id;         // присваиваем номер
    new_stack.current_weight = weight; // кладём первый контейнер
    new_stack.containers.push(pair<string, int>(id, weight)); // добавляем в стек
    stacks.push_back(new_stack);   // добавляем стек в список
    cout << "Контейнер " << id << " размещен в стек " << new_id << "\n";
}

void load() {
    vector<pair<string, int> > all_containers; // временный вектор

    for (vector<Stack>::iterator it = stacks.begin(); it != stacks.end(); ++it) {
        // пока в стеке есть контейнеры
        while (!it->containers.empty()) {
            // берём верхний
            pair<string, int> top = it->containers.top();
            all_containers.push_back(top); // сохраняем
            it->containers.pop();          // удаляем из стека
        }
    }

    vector<pair<int, vector<string> > > sections(sections_count);

    for (vector<pair<string, int> >::iterator it = all_containers.begin(); it != all_containers.end(); ++it) {
        // ищем секцию с наименьшим текущим весом
        int min_idx = 0;           // сначала считаем минимальной первую
        for (int i = 1; i < sections_count; ++i) {
            if (sections[i].first < sections[min_idx].first) {
                min_idx = i;       // нашли секцию с меньшим весом
            }
        }
        sections[min_idx].first += it->second;   // добавляем вес
        sections[min_idx].second.push_back(it->first); // запоминаем id
    }

    for (int i = 0; i < sections_count; ++i) {
        cout << "Секция " << i + 1 << " (" << sections[i].first << " тонн): ";
        for (vector<string>::iterator vit = sections[i].second.begin(); vit != sections[i].second.end(); ++vit) {
            cout << *vit << " ";   // выводим идентификаторы
        }
        cout << endl;              
    }
}