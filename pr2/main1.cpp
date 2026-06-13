#include <iostream>
#include "evklid.h"
using namespace std;

int main() {
    int c, m;
    cout << "c * d mod m = 1 (через u, v)" << endl;
    cout << "Введите c и m: ";
    cin >> c >> m;

    evklid(c, m);

    return 0;
}