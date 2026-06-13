#include "polybius.h"
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <cctype>
#include <utility>


using namespace std;

const string ALPHABET = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

char normalizeChar(char ch);
bool isLatinLetter(char ch);
map<char, pair<int, int>> buildPositions(const vector<vector<char>>& square);
string onlyLetters(const string& text);

vector<vector<char>> buildSquare() {
    vector<vector<char>> square(5, vector<char>(5));
    int k = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            square[i][j] = ALPHABET[k++];
    return square;
}

string polybiusEncrypt(const string& text) {
    auto square = buildSquare();
    auto pos = buildPositions(square);
    string src = onlyLetters(text);
    string result;
    for (size_t i = 0; i < src.size(); i++) {
        int r = pos[src[i]].first + 1;
        int c = pos[src[i]].second + 1;
        result += to_string(r) + to_string(c) + " ";
    }
    if (!result.empty()) result.pop_back();
    return result;
}

string polybiusDecrypt(const string& text) {
    auto square = buildSquare();
    string result;
    stringstream ss(text);
    string token;
    while (ss >> token) {
        if (token.size() != 2) { result += '?'; continue; }
        int r = token[0] - '1';
        int c = token[1] - '1';
        if (r >= 0 && r < 5 && c >= 0 && c < 5) result += square[r][c];
        else result += '?';
    }
    return result;
}

void polybiusEncryptFile(const string& inFile, const string& outFile) {
    ifstream in(inFile);
    ofstream out(outFile);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    out << polybiusEncrypt(content);
}

void polybiusDecryptFile(const string& inFile, const string& outFile) {
    ifstream in(inFile);
    ofstream out(outFile);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    out << polybiusDecrypt(content);
}