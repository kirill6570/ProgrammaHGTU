#include "tea.h"
#include <fstream>
#include <cstdint>
#include <cstring>

using namespace std;

void teaEncryptBlock(uint32_t v[2], const uint32_t k[4]) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0, delta = 0x9E3779B9;
    for (int i = 0; i < 32; i++) {
        sum += delta;
        v0 += ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
        v1 += ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
    }
    v[0] = v0; v[1] = v1;
}

void teaDecryptBlock(uint32_t v[2], const uint32_t k[4]) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0xC6EF3720, delta = 0x9E3779B9;
    for (int i = 0; i < 32; i++) {
        v1 -= ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
        v0 -= ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
        sum -= delta;
    }
    v[0] = v0; v[1] = v1;
}

string teaEncrypt(const string &text, const string &key) {
    uint32_t k[4];
    string kk = key;
    kk.resize(16, '\0');
    for (int i = 0; i < 4; i++)
        k[i] = ((unsigned char)kk[i*4] << 24) | ((unsigned char)kk[i*4+1] << 16) |
               ((unsigned char)kk[i*4+2] << 8) | (unsigned char)kk[i*4+3];

    string data = text;
    while (data.size() % 8 != 0) data += '\0';

    string result;
    for (size_t i = 0; i < data.size(); i += 8) {
        uint32_t v[2];
        v[0] = ((unsigned char)data[i] << 24) | ((unsigned char)data[i+1] << 16) |
               ((unsigned char)data[i+2] << 8) | (unsigned char)data[i+3];
        v[1] = ((unsigned char)data[i+4] << 24) | ((unsigned char)data[i+5] << 16) |
               ((unsigned char)data[i+6] << 8) | (unsigned char)data[i+7];
        teaEncryptBlock(v, k);
        for (int j = 0; j < 4; j++) result += (char)(v[0] >> (24 - j*8));
        for (int j = 0; j < 4; j++) result += (char)(v[1] >> (24 - j*8));
    }
    return result;
}

string teaDecrypt(const string &text, const string &key) {
    uint32_t k[4];
    string kk = key;
    kk.resize(16, '\0');
    for (int i = 0; i < 4; i++)
        k[i] = ((unsigned char)kk[i*4] << 24) | ((unsigned char)kk[i*4+1] << 16) |
               ((unsigned char)kk[i*4+2] << 8) | (unsigned char)kk[i*4+3];

    string result;
    for (size_t i = 0; i < text.size(); i += 8) {
        uint32_t v[2];
        v[0] = ((unsigned char)text[i] << 24) | ((unsigned char)text[i+1] << 16) |
               ((unsigned char)text[i+2] << 8) | (unsigned char)text[i+3];
        v[1] = ((unsigned char)text[i+4] << 24) | ((unsigned char)text[i+5] << 16) |
               ((unsigned char)text[i+6] << 8) | (unsigned char)text[i+7];
        teaDecryptBlock(v, k);
        for (int j = 0; j < 4; j++) result += (char)(v[0] >> (24 - j*8));
        for (int j = 0; j < 4; j++) result += (char)(v[1] >> (24 - j*8));
    }
    return result;
}

void teaEncryptFile(const string &inFile, const string &outFile, const string &key) {
    ifstream in(inFile, ios::binary);
    ofstream out(outFile, ios::binary);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    string result = teaEncrypt(content, key);
    for (size_t i = 0; i < result.size(); i++) out.put(result[i]);
}

void teaDecryptFile(const string &inFile, const string &outFile, const string &key) {
    ifstream in(inFile, ios::binary);
    ofstream out(outFile, ios::binary);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    string result = teaDecrypt(content, key);
    for (size_t i = 0; i < result.size(); i++) out.put(result[i]);
}