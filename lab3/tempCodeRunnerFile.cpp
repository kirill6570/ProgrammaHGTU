#include <iostream>
#include <exception>
#include <cstdint>

using namespace std;
 
int reting(int x, int y) {
    if (x == 0 && y == 0) {
        throw "negodai";

    }
    return (x+y) /2;
}

int main() 
{
 int x = 0; // cеместр
 int y = 0; // экзамен
 cout << reting(x,y) << endl;
    return 0;
}