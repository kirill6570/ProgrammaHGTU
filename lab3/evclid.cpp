#include <iostream>
using namespace std;

int mod_pow(int base, int power, int mod) {
    int result = 1;
    base %= mod;
    for (int i = 0; i < power; i++) {
        result = (result * base) % mod;
    }
    return result;
}

int extended_gcd(int a, int b, int &u, int &v) {
    if (b == 0) {
        u = 1;
        v = 0;
        return a;
    }
    int u1, v1;
    int gcd = extended_gcd(b, a % b, u1, v1);
    u = v1;
    v = u1 - (a / b) * v1;
    return gcd;
}

int mod_inverse(int a, int m) {
    int u, v;
    extended_gcd(a, m, u, v);
    return (u % m + m) % m;
}

int main() {
    int p, m, Ca, Cb;
    
    cout << "p = "; cin >> p;
    cout << "m = "; cin >> m;
    cout << "Ca = "; cin >> Ca;
    cout << "Cb = "; cin >> Cb;
    
    int Da = mod_inverse(Ca, p-1);
    int Db = mod_inverse(Cb, p-1);
    
    int x1 = mod_pow(m, Ca, p);
    int x2 = mod_pow(x1, Cb, p);
    int x3 = mod_pow(x2, Da, p);
    int result = mod_pow(x3, Db, p);
    
    cout << "Result = " << result << endl;
    
    return 0;
}
