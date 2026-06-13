#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <string>
using namespace std;

string playfairEncrypt(const string &text, const string &key);
string playfairDecrypt(const string &text, const string &key);
void playfairEncryptFile(const string &inFile, const string &outFile, const string &key);
void playfairDecryptFile(const string &inFile, const string &outFile, const string &key);

#endif