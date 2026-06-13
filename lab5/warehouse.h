#ifndef WAREHOUSE_H                     
#define WAREHOUSE_H                     

#include <map>                         
#include <string>                     

using namespace std;                  

// Структура одной ячейки склада
struct Cell {
    string product;                     // название товара
    int quantity;                       // количество (0..10)
};

extern map<string, Cell> warehouse;     // адрес  ячейка
extern int total_cells;                 // всего ячеек
extern int occupied_cells;              // занятых ячеек

const int ZONES = 2;                    // зоны А и Б
const int SHELVES_PER_ZONE = 15;        // стеллажей в каждой зоне
const int SECTIONS = 3;                 // секций на стеллаже
const int ROWS = 5;                     // полок в секции

// Функции
string make_address(char zone, int shelf, int section, int row); // собрать адрес
void add(const string& product, int quantity, const string& address); // ADD
void remove(const string& product, int quantity, const string& address); // REMOVE
void info();                            // INFO

#endif