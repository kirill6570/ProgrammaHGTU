#ifndef AES_H
#define AES_H

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <random>
#include <cstring>
#include <string>

using namespace std;

// ОБЪЯВЛЕНИЯ (extern) – без инициализации
extern const unsigned char sbox[256];
extern const unsigned char rcon[11];

// Вспомогательные функции
unsigned char xtime(unsigned char x);
void printHex(const string& label, const unsigned char* data, int len);
void generateRandomBytes(unsigned char* buf, int len);
void padPKCS7(vector<unsigned char>& data);
void unpadPKCS7(vector<unsigned char>& data);

// Основные функции AES
void keyExpansion(const unsigned char key[16], unsigned char w[11][16]);
void subBytes(unsigned char state[16]);
void shiftRows(unsigned char state[16]);
void mixColumns(unsigned char state[16]);
void addRoundKey(unsigned char state[16], const unsigned char key[16]);
void aesEncryptBlock(unsigned char block[16], unsigned char w[11][16], bool showTrace);
void aesCFB(vector<unsigned char>& data, unsigned char w[11][16], const unsigned char iv[16], bool encrypt);

#endif