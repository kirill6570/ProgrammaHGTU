#ifndef RSA_H
#define RSA_H

#include <string>
using namespace std;

long long powMod(long long base, long long exp, long long mod);
string rsaEncrypt(const string &message, long long d, long long N);
string rsaDecrypt(const string &cipher, long long c, long long N);
void rsaEncryptFile(const string &inFile, const string &outFile, long long d, long long N);
void rsaDecryptFile(const string &inFile, const string &outFile, long long c, long long N);

#endif
