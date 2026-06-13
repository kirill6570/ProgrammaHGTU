#ifndef PORT_H                    
#define PORT_H                     

#include <vector>                  // для std::vector (список стеков)
#include <stack>                   // для std::stack (стек контейнеров)
#include <string>                  // для std::string
#include <utility>                 // для std::pair (пара id + вес)

using namespace std;             
 
struct Stack {
    int id;                        // номер стека (1, 2, 3...)
    int current_weight;            // текущий вес всех контейнеров в стеке
    stack<pair<string, int> > containers; // стек пар (идентификатор, вес)
};

extern vector<Stack> stacks;       // все стеки
extern int max_stack_capacity;     // грузоподъёмность одного стека
extern int sections_count;         // количество секций на судне
extern int next_container_id;      // счётчик для генерации C001, C002...

// Функции
string make_container_id();        // генерирует C001, C002...
void arrive(int weight);           // команда ARRIVE
void load();                       // команда LOAD

#endif