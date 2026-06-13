#include "hill.h"
#include <fstream>

int modInverse(int a) {
    for (int i = 1; i < 256; i++)
        if ((a * i) % 256 == 1) return i;
    return 1;
}

string hillEncrypt(const string &text, const string &key) {
    int a = (unsigned char)key[0];
    int b = (unsigned char)key[1];
    int c = (unsigned char)key[2];
    int d = (unsigned char)key[3];

    string data = text;
    if (data.size() % 2 != 0) data += '\0';

    string result;
    for (size_t i = 0; i < data.size(); i += 2) {
        unsigned char x = data[i];
        unsigned char y = data[i + 1];
        result += (unsigned char)((a * x + b * y) % 256);
        result += (unsigned char)((c * x + d * y) % 256);
    }
    return result;
}

string hillDecrypt(const string &text, const string &key) {
    int a = (unsigned char)key[0];
    int b = (unsigned char)key[1];
    int c = (unsigned char)key[2];
    int d = (unsigned char)key[3];

    int det = (a * d - b * c) % 256;
    if (det < 0) det += 256;
    int invDet = modInverse(det);

    int ia = (invDet * d) % 256;
    int ib = (-invDet * b) % 256; if (ib < 0) ib += 256;
    int ic = (-invDet * c) % 256; if (ic < 0) ic += 256;
    int id = (invDet * a) % 256;

    string result;
    for (size_t i = 0; i < text.size(); i += 2) {
        unsigned char x = text[i];
        unsigned char y = text[i + 1];
        result += (unsigned char)((ia * x + ib * y) % 256);
        result += (unsigned char)((ic * x + id * y) % 256);
    }
    return result;
}

void hillEncryptFile(const string &inFile, const string &outFile, const string &key) {
    ifstream in(inFile, ios::binary);
    ofstream out(outFile, ios::binary);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    string result = hillEncrypt(content, key);
    for (size_t i = 0; i < result.size(); i++) out.put(result[i]);
}

void hillDecryptFile(const string &inFile, const string &outFile, const string &key) {
    ifstream in(inFile, ios::binary);
    ofstream out(outFile, ios::binary);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    string result = hillDecrypt(content, key);
    for (size_t i = 0; i < result.size(); i++) out.put(result[i]);
}
