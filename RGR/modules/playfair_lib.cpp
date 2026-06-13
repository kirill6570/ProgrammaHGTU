#include <string>
#include <vector>
#include <map>
#include <cctype>
using namespace std;

const string ALPHABET = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

char normalizeChar(char ch) { ch = toupper(ch); if (ch == 'J') return 'I'; return ch; }
bool isLatinLetter(char ch) { return ALPHABET.find(normalizeChar(ch)) != string::npos; }

vector<vector<char>> buildSquare(const string& key) {
    string used, source = key + ALPHABET;
    for (size_t i = 0; i < source.size(); i++) {
        char ch = normalizeChar(source[i]);
        if (isLatinLetter(ch) && used.find(ch) == string::npos) used += ch;
    }
    vector<vector<char>> sq(5, vector<char>(5)); int k = 0;
    for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) sq[i][j] = used[k++];
    return sq;
}

map<char, pair<int, int>> buildPos(const vector<vector<char>>& sq) {
    map<char, pair<int, int>> pos;
    for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) pos[sq[i][j]] = {i, j};
    return pos;
}

string onlyAlpha(const string& text) {
    string result;
    for (size_t i = 0; i < text.size(); i++) {
        char ch = normalizeChar(text[i]);
        if (isLatinLetter(ch)) result += ch;
    }
    return result;
}

string prepare(const string& text) {
    string src = onlyAlpha(text), result;
    size_t i = 0;
    while (i < src.size()) {
        char a = src[i], b = (i + 1 < src.size()) ? src[i + 1] : 'X';
        if (a == b) { result += a; result += 'X'; i++; }
        else { result += a; result += b; i += 2; }
    }
    if (result.size() % 2) result += 'X';
    return result;
}

extern "C" string playfairEncrypt(const string &text, const string &key) {
    auto sq = buildSquare(key); auto pos = buildPos(sq);
    string prep = prepare(text), result;
    for (size_t i = 0; i < prep.size(); i += 2) {
        char a = prep[i], b = prep[i+1];
        int r1 = pos[a].first, c1 = pos[a].second, r2 = pos[b].first, c2 = pos[b].second;
        if (r1 == r2) { result += sq[r1][(c1+1)%5]; result += sq[r2][(c2+1)%5]; }
        else if (c1 == c2) { result += sq[(r1+1)%5][c1]; result += sq[(r2+1)%5][c2]; }
        else { result += sq[r1][c2]; result += sq[r2][c1]; }
    }
    return result;
}

extern "C" string playfairDecrypt(const string &text, const string &key) {
    auto sq = buildSquare(key); auto pos = buildPos(sq);
    string src = onlyAlpha(text); if (src.size() % 2) src += 'X';
    string result;
    for (size_t i = 0; i < src.size(); i += 2) {
        char a = src[i], b = src[i+1];
        int r1 = pos[a].first, c1 = pos[a].second, r2 = pos[b].first, c2 = pos[b].second;
        if (r1 == r2) { result += sq[r1][(c1+4)%5]; result += sq[r2][(c2+4)%5]; }
        else if (c1 == c2) { result += sq[(r1+4)%5][c1]; result += sq[(r2+4)%5][c2]; }
        else { result += sq[r1][c2]; result += sq[r2][c1]; }
    }
    return result;
}
