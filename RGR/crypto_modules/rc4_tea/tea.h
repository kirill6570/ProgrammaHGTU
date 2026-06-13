#ifndef TEA_H
#define TEA_H

#include <string>
using namespace std;

string teaEncrypt(const string &text, const string &key);
string teaDecrypt(const string &text, const string &key);
void teaEncryptFile(const string &inFile, const string &outFile, const string &key);
void teaDecryptFile(const string &inFile, const string &outFile, const string &key);

#endif
