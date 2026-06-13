#include "caesar.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

string caesarEncrypt(const string &text, int shift) {
    string result;
    cout << "\n=== Шифрование Цезаря ===" << endl;
    for (size_t i = 0; i < text.size(); i++) {
        unsigned char ch = text[i];
        int num = (int)ch + shift;
        cout << "Символ '" << text[i] << "' (код " << (int)ch << ") + " << shift << " = " << num << " -> '" << (char)num << "'" << endl;
        result += (char)num;
    }
    return result;
}

string caesarDecrypt(const string &text, int shift) {
    string result;
    cout << "\n=== Расшифрование Цезаря ===" << endl;
    stringstream ss(text);
    string token;
    // если текст из чисел
    if (text.find(' ') != string::npos) {
        while (ss >> token) {
            int num = stoi(token) - shift;
            cout << "Число " << token << " - " << shift << " = " << num << " -> '" << (char)num << "'" << endl;
            result += (char)num;
        }
    } else {
        // если текст из символов
        for (size_t i = 0; i < text.size(); i++) {
            unsigned char ch = text[i];
            int num = (int)ch - shift;
            cout << "Символ '" << text[i] << "' (код " << (int)ch << ") - " << shift << " = " << num << " -> '" << (char)num << "'" << endl;
            result += (char)num;
        }
    }
    return result;
}

void caesarEncryptFile(const string &inFile, const string &outFile, int shift) {
    ifstream in(inFile);
    ofstream out(outFile);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    out << caesarEncrypt(content, shift);
}

void caesarDecryptFile(const string &inFile, const string &outFile, int shift) {
    ifstream in(inFile);
    ofstream out(outFile);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    out << caesarDecrypt(content, shift);
}