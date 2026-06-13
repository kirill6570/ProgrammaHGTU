#ifndef POLYBIUS_H
#define POLYBIUS_H

#include <string>
using namespace std;

string polybiusEncrypt(const string &text);
string polybiusDecrypt(const string &text);
void polybiusEncryptFile(const string &inFile, const string &outFile);
void polybiusDecryptFile(const string &inFile, const string &outFile);

#endif