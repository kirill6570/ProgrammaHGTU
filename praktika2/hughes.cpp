#include "hughes.h"
#include <iostream>
#include <fstream>
#include <gmpxx.h>
using namespace std;

mpz_class powMod(mpz_class base, mpz_class exp, mpz_class mod) {
    mpz_class result;
    mpz_powm(result.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod.get_mpz_t());
    return result;
}

mpz_class inverseMod(mpz_class c, mpz_class m) {
    mpz_class result;
    mpz_invert(result.get_mpz_t(), c.get_mpz_t(), m.get_mpz_t());
    return result;
}

void hughesEncryptFile(const string &inFile, const string &outFile, mpz_class p, mpz_class g, mpz_class b) {
    ifstream in(inFile);
    ofstream out(outFile);
    char ch;
    mpz_class k = 3, r;
    int count = 0;
    mpz_class B = powMod(g, b, p);
    cout << "B = " << B << endl;

    while (in.get(ch)) {
        r = powMod(g, k, p);
        mpz_class s = powMod(B, k, p);
        mpz_class e = (mpz_class((unsigned char)ch) * s) % p;
        out << r << " " << e << " ";

        if (count < 3)
            cout << "'" << ch << "' (" << (int)(unsigned char)ch << ") -> r=" << r << " e=" << e << endl;
        count++;
    }
    if (count > 3) cout << "... всего " << count << " символов" << endl;
    in.close();
    out.close();
}

void hughesDecryptFile(const string &inFile, const string &outFile, mpz_class p, mpz_class g, mpz_class b) {
    ifstream in(inFile);
    ofstream out(outFile);
    string r_str, e_str;
    int count = 0;

    while (in >> r_str >> e_str) {
        mpz_class r(r_str), e(e_str);
        mpz_class s = powMod(r, b, p);
        mpz_class inv = inverseMod(s, p);
        mpz_class ch = (e * inv) % p;
        out.put((char)ch.get_ui());

        if (count < 3)
            cout << "r=" << r << " e=" << e << " -> '" << (char)ch.get_ui() << "' (" << ch << ")" << endl;
        count++;
    }
    if (count > 3) cout << "... всего " << count << " символов" << endl;
    in.close();
    out.close();
}
