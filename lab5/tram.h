#ifndef TRAM_H                           
#define TRAM_H                           

#include <map>                           
#include <set>               
#include <string>                     
#include <vector>                  

using namespace std;                   


extern map<string, vector<string> > trams;        // трамвай -> его остановки
extern map<string, set<string> > stop_to_trams;   // остановка -> какие трамваи через неё едут

// Функции
void create_tram(const string& name, const vector<string>& stops); 
void print_trams();                                               
void trams_in_stop(const string& stop);                           
void stops_in_tram(const string& name);                           

#endif