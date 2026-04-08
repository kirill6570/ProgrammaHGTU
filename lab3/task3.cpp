#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// наибольший общий делитель
long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// быстрое целочисленное возведение в степень
long long binpow(long long base, int exp) {
    long long res = 1;
    while (exp) {
        if (exp & 1) res *= base;
        base *= base;
        exp >>= 1;
    }
    return res;
}

// числа Стирлинга второго рода для заданного n (n >= 1)
vector<long long> stirling2(int n) {
    vector<long long> s(n + 1, 0);
    s[1] = 1;                     // S(n,1) = 1
    for (int i = 2; i <= n; ++i) {
        for (int k = i; k >= 1; --k) {
            s[k] = s[k - 1] + k * s[k];
        }
        s[0] = 0;
    }
    return s;
}

int main() {
    int a, b;
    cin >> a >> b;

    // ряд расходится при b = 1
    if (b == 1) {
        cout << "infinity" << endl;
        return 0;
    }

    vector<long long> S = stirling2(a);
    long long C = 0;

    for (int k = 1; k <= a; ++k) {
        // факториал k!
        long long fact = 1;
        for (int i = 2; i <= k; ++i) fact *= i;

        // (b-1)^(a-k)
        long long pow_b1 = binpow(b - 1, a - k);

        C += S[k] * fact * pow_b1;
    }

    long long numerator = b * C;
    long long denominator = binpow(b - 1, a + 1);

    long long g = gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;

    cout << numerator << "/" << denominator << endl;

    return 0;
}
