#include <iostream>
#include "mod.h"
using namespace std;

int main() {
    int a, x, p;
    cin >> a >> x >> p;

    cout << "fermat: " << modf(a, x, p) << endl;
    cout << "binary: " << modb(a, x, p) << endl;

    return 0;
}