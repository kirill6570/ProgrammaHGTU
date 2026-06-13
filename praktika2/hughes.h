#ifndef HUGHES_H
#define HUGHES_H

#include <string>
#include <gmpxx.h>
using namespace std;

mpz_class powMod(mpz_class base, mpz_class exp, mpz_class mod);
mpz_class inverseMod(mpz_class c, mpz_class m);
void hughesEncryptFile(const string &inFile, const string &outFile, mpz_class p, mpz_class g, mpz_class b);
void hughesDecryptFile(const string &inFile, const string &outFile, mpz_class p, mpz_class g, mpz_class b);

#endif
