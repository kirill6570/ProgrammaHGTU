#ifndef CAESAR_H
#define CAESAR_H

#include <string>
using namespace std;

string caesarEncrypt(const string &text, int shift);
string caesarDecrypt(const string &text, int shift);
void caesarEncryptFile(const string &inFile, const string &outFile, int shift);
void caesarDecryptFile(const string &inFile, const string &outFile, int shift);

#endif