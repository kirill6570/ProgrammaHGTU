#ifndef TRANSPOS_H
#define TRANSPOS_H

#include <string>
using namespace std;

string transposEncrypt(const string &text, string key);
string transposDecrypt(const string &text, string key);
void transposEncryptFile(const string &inFile, const string &outFile, const string &key);
void transposDecryptFile(const string &inFile, const string &outFile, const string &key);

#endif
