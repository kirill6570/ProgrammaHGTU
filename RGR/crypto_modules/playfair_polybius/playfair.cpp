#include "playfair.h"
#include <vector>
#include <map>
#include <fstream>
#include <cctype>

using namespace std;

const string ALPHABET = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

char normalizeChar(char ch) {
    ch = toupper(ch);
    if (ch == 'J') return 'I';
    return ch;
}

bool isLatinLetter(char ch) {
    ch = normalizeChar(ch);
    return ALPHABET.find(ch) != string::npos;
}

vector<vector<char>> buildPlayfairSquare(const string& key) {
    string used;
    string source = key + ALPHABET;
    for (size_t i = 0; i < source.size(); i++) {
        char ch = normalizeChar(source[i]);
        if (isLatinLetter(ch) && used.find(ch) == string::npos) {
            used += ch;
        }
    }
    vector<vector<char>> square(5, vector<char>(5));
    int k = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            square[i][j] = used[k++];
    return square;
}

map<char, pair<int, int>> buildPositions(const vector<vector<char>>& square) {
    map<char, pair<int, int>> pos;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            pos[square[i][j]] = {i, j};
    return pos;
}

string onlyLetters(const string& text) {
    string result;
    for (size_t i = 0; i < text.size(); i++) {
        char ch = normalizeChar(text[i]);
        if (isLatinLetter(ch)) result += ch;
    }
    return result;
}

string preparePlayfairText(const string& text) {
    string src = onlyLetters(text);
    string result;
    size_t i = 0;
    while (i < src.size()) {
        char a = src[i];
        char b = (i + 1 < src.size()) ? src[i + 1] : 'X';
        if (a == b) {
            result += a;
            result += 'X';
            i++;
        } else {
            result += a;
            result += b;
            i += 2;
        }
    }
    if (result.size() % 2 != 0) result += 'X';
    return result;
}

string playfairEncrypt(const string& text, const string& key) {
    auto square = buildPlayfairSquare(key);
    auto pos = buildPositions(square);
    string prepared = preparePlayfairText(text);
    string result;
    for (size_t i = 0; i < prepared.size(); i += 2) {
        char a = prepared[i], b = prepared[i + 1];
        int r1 = pos[a].first, c1 = pos[a].second;
        int r2 = pos[b].first, c2 = pos[b].second;
        if (r1 == r2) {
            result += square[r1][(c1 + 1) % 5];
            result += square[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            result += square[(r1 + 1) % 5][c1];
            result += square[(r2 + 1) % 5][c2];
        } else {
            result += square[r1][c2];
            result += square[r2][c1];
        }
    }
    return result;
}

string playfairDecrypt(const string& text, const string& key) {
    auto square = buildPlayfairSquare(key);
    auto pos = buildPositions(square);
    string src = onlyLetters(text);
    if (src.size() % 2 != 0) src += 'X';
    string result;
    for (size_t i = 0; i < src.size(); i += 2) {
        char a = src[i], b = src[i + 1];
        int r1 = pos[a].first, c1 = pos[a].second;
        int r2 = pos[b].first, c2 = pos[b].second;
        if (r1 == r2) {
            result += square[r1][(c1 + 4) % 5];
            result += square[r2][(c2 + 4) % 5];
        } else if (c1 == c2) {
            result += square[(r1 + 4) % 5][c1];
            result += square[(r2 + 4) % 5][c2];
        } else {
            result += square[r1][c2];
            result += square[r2][c1];
        }
    }
    return result;
}

void playfairEncryptFile(const string& inFile, const string& outFile, const string& key) {
    ifstream in(inFile);
    ofstream out(outFile);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    out << playfairEncrypt(content, key);
}

void playfairDecryptFile(const string& inFile, const string& outFile, const string& key) {
    ifstream in(inFile);
    ofstream out(outFile);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    out << playfairDecrypt(content, key);
}
