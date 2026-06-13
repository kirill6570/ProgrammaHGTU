#include "hughes.h"
#include <iostream>
using namespace std;

int pow_mod(int base, int exp, int mod) {
    base = base % mod;
    int r = 1;
    while (exp > 0) {
        if (exp % 2 == 1) r = (r * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return r;
}

int obr(int c, int m) {
    int a = c, b = m;
    int u0 = 1, u1 = 0;
    while (b != 0) {
        int q = a / b;
        int t = a % b;
        int u = u0 - q * u1;
        a = b; b = t;
        u0 = u1; u1 = u;
    }
    if (u0 < 0) u0 += m;
    return u0;
}

void hughes(int p, int g, int a, int b, int m_msg) {
    int A = pow_mod(g, a, p);
    int B = pow_mod(g, b, p);

    cout << "A = " << g << "^" << a << " mod " << p << " = " << A << endl;
    cout << "B = " << g << "^" << b << " mod " << p << " = " << B << endl;

    int k;
    cout << "k: ";
    cin >> k;

    int r = pow_mod(g, k, p);
    int s = pow_mod(B, k, p);
    int e = (m_msg * s) % p;

    cout << "r = " << g << "^" << k << " mod " << p << " = " << r << endl;
    cout << "s = " << B << "^" << k << " mod " << p << " = " << s << endl;
    cout << "e = " << m_msg << " * " << s << " mod " << p << " = " << e << endl;

    s = pow_mod(r, b, p);
    int s_inv = obr(s, p);
    int m_dec = (e * s_inv) % p;

    cout << "m = " << e << " * " << s_inv << " mod " << p << " = " << m_dec << endl;
}