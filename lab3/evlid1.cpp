#include <iostream>
using namespace std;

int egcd(int a, int b, int &u, int &v) {
    if (b == 0) {
        u = 1;
        v = 0;
        return a;
    }
    int u1, v1;
    int g = egcd(b, a % b, u1, v1);
    u = v1;
    v = u1 - (a / b) * v1;
    return g;
}

int inv(int a, int m) {
    int u, v;
    egcd(a, m, u, v);
    return (u % m + m) % m;
}

int main() {
    int a, m;
    cin >> a >> m;
    cout << inv(a, m) << endl;
    return 0;
}
