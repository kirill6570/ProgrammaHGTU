#ifndef HILL_H
#define HILL_H

#include <string>
using namespace std;

string hillEncrypt(const string &text, const string &key);
string hillDecrypt(const string &text, const string &key);
void hillEncryptFile(const string &inFile, const string &outFile, const string &key);
void hillDecryptFile(const string &inFile, const string &outFile, const string &key);

#endif