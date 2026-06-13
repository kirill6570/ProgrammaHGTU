#include "rc4.h"
#include <fstream>

using namespace std;

string rc4Crypt(const string &text, const string &key) {
    int S[256];
    for (int i = 0; i < 256; i++) S[i] = i;

    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key.size()]) % 256;
        int tmp = S[i]; S[i] = S[j]; S[j] = tmp;
    }

    string result = text;
    int i = 0; j = 0;
    for (size_t k = 0; k < text.size(); k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        int tmp = S[i]; S[i] = S[j]; S[j] = tmp;
        unsigned char keystream = S[(S[i] + S[j]) % 256];
        result[k] = text[k] ^ keystream;
    }
    return result;
}

string rc4Encrypt(const string &text, const string &key) {
    return rc4Crypt(text, key);
}

string rc4Decrypt(const string &text, const string &key) {
    return rc4Crypt(text, key);
}

void rc4EncryptFile(const string &inFile, const string &outFile, const string &key) {
    ifstream in(inFile, ios::binary);
    ofstream out(outFile, ios::binary);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    string result = rc4Encrypt(content, key);
    out.write(result.data(), result.size());
}

void rc4DecryptFile(const string &inFile, const string &outFile, const string &key) {
    ifstream in(inFile, ios::binary);
    ofstream out(outFile, ios::binary);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    string result = rc4Decrypt(content, key);
    out.write(result.data(), result.size());
}
