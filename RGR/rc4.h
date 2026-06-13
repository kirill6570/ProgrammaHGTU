#ifndef RC4_H
#define RC4_H

#include <string>
using namespace std;

string rc4Crypt(const string &text, const string &key);
void rc4CryptFile(const string &inFile, const string &outFile, const string &key);

#endif