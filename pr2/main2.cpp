#include <iostream>
#include "obr.h"
using namespace std;

int main() {
    int c, m;
    cout << "c^{-1} mod m = d" << endl;
    cout << "Введите c и m: ";
    cin >> c >> m;

    obr(c, m);

    return 0;
}