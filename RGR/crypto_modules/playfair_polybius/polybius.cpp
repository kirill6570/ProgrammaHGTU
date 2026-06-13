#include "polybius.h"
#include <fstream>
#include <cctype>
#include <map>
#include <sstream>

using namespace std;

char normalizePolybiusChar(char ch) {
    ch = toupper(ch);
    if (ch == 'J') return 'I';
    return ch;
}

string buildPolybiusSquare(const string& key) {
    string used;
    string full = key + "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    for (char ch : full) {
        ch = normalizePolybiusChar(ch);
        if (isalpha(ch) && used.find(ch) == string::npos) {
            used += ch;
        }
    }
    return used;
}

string polybiusEncrypt(const string& text, const string& key) {
    string square = buildPolybiusSquare(key);
    map<char, string> pos;
    for (int i = 0; i < 25; i++) {
        int row = i / 5 + 1;
        int col = i % 5 + 1;
        pos[square[i]] = to_string(row) + to_string(col);
    }
    
    string result;
    for (char ch : text) {
        ch = normalizePolybiusChar(ch);
        if (pos.count(ch)) {
            result += pos[ch] + " ";
        }
    }
    if (!result.empty()) result.pop_back();
    return result;
}

string polybiusDecrypt(const string& text, const string& key) {
    string square = buildPolybiusSquare(key);
    map<string, char> pos;
    for (int i = 0; i < 25; i++) {
        int row = i / 5 + 1;
        int col = i % 5 + 1;
        string code = to_string(row) + to_string(col);
        pos[code] = square[i];
    }
    
    string result;
    stringstream ss(text);
    string code;
    while (ss >> code) {
        if (pos.count(code)) {
            result += pos[code];
        }
    }
    return result;
}

void polybiusEncryptFile(const string& inFile, const string& outFile, const string& key) {
    ifstream in(inFile);
    ofstream out(outFile);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    out << polybiusEncrypt(content, key);
}

void polybiusDecryptFile(const string& inFile, const string& outFile, const string& key) {
    ifstream in(inFile);
    ofstream out(outFile);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    out << polybiusDecrypt(content, key);
}
