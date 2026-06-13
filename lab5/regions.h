#ifndef REGIONS_H                    
#define REGIONS_H                     

#include <map>                      
#include <set>                     
#include <string>                     

using namespace std;                

extern map<string, string> regions;   // регион  административный центр
extern set<string> used_centers;      // все занятые центры

void change(const string& region, const string& center); // CHANGE
void rename_center(const string& old_name, const string& new_name); // RENAME
void about(const string& region);    
void print_all();                     

#endif