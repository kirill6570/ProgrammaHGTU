#include "mod.h"
#include "prime.h"

int modf(int a, int x, int p) {
    if (!is_p(p)) return -1;
    if (a % p == 0) return -1;
    x = x % (p - 1);
    a = a % p;
    int r = 1;
    for (int i = 0; i < x; i++) {
        r = (r * a) % p;
    }
    return r;
}

int modb(int a, int x, int p) {
    a = a % p;
    int r = 1;
    while (x > 0) {
        if (x % 2 == 1) {
            r = (r * a) % p;
        }
        a = (a * a) % p;
        x = x / 2;
    }
    return r;
}