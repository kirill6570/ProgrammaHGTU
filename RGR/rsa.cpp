#include "rsa.h"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

long long powMod(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

string rsaEncrypt(const string &message, long long d, long long N) {
    string result;
    cout << "\n=== Шифрование RSA ===" << endl;
    for (size_t i = 0; i < message.size(); i++) {
        long long m = (unsigned char)message[i];
        long long e = powMod(m, d, N);
        cout << "Символ '" << message[i] << "' (код " << m << ") -> " << m << "^" << d << " mod " << N << " = " << e << endl;
        result += to_string(e) + " ";
    }
    if (!result.empty()) result.pop_back();
    return result;
}

string rsaDecrypt(const string &cipher, long long c, long long N) {
    string result;
    cout << "\n=== Расшифрование RSA ===" << endl;
    stringstream ss(cipher);
    string token;
    while (ss >> token) {
        long long e = stoll(token);
        long long m = powMod(e, c, N);
        cout << "Число " << e << " -> " << e << "^" << c << " mod " << N << " = " << m << " -> '" << (char)m << "'" << endl;
        result += (char)m;
    }
    return result;
}

void rsaEncryptFile(const string &inFile, const string &outFile, long long d, long long N) {
    ifstream in(inFile);
    ofstream out(outFile);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    out << rsaEncrypt(content, d, N);
}

void rsaDecryptFile(const string &inFile, const string &outFile, long long c, long long N) {
    ifstream in(inFile);
    ofstream out(outFile);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    out << rsaDecrypt(content, c, N);
}