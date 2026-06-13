#include "crypto_interface.h"
#include <cstring>
#include <vector>
#include <map>
#include <cctype>
#include <string>

using namespace std;

const string ALPHABET = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

char norm(char ch) {
    ch = toupper(ch);
    if (ch == 'J') return 'I';
    return ch;
}

string only_letters(const string& s) {
    string r;
    for (char c : s) {
        c = norm(c);
        if (ALPHABET.find(c) != string::npos) r += c;
    }
    return r;
}

vector<vector<char>> build_square(const string& key) {
    string used;
    string src = key + ALPHABET;
    for (char c : src) {
        c = norm(c);
        if (ALPHABET.find(c) != string::npos && used.find(c) == string::npos) {
            used += c;
        }
    }
    vector<vector<char>> sq(5, vector<char>(5));
    int k = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            sq[i][j] = used[k++];
    return sq;
}

map<char, pair<int,int>> get_pos(const vector<vector<char>>& sq) {
    map<char, pair<int,int>> pos;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            pos[sq[i][j]] = {i, j};
    return pos;
}

string prepare(const string& s) {
    string src = only_letters(s);
    string r;
    for (size_t i = 0; i < src.size();) {
        char a = src[i];
        char b = (i+1 < src.size()) ? src[i+1] : 'X';
        if (a == b) {
            r += a; r += 'X'; i++;
        } else {
            r += a; r += b; i += 2;
        }
    }
    if (r.size() % 2) r += 'X';
    return r;
}

static AlgorithmInfo info = {"playfair", 1};

extern "C" const AlgorithmInfo* get_algorithm_info() { return &info; }
extern "C" size_t get_output_size(size_t in, int op) { return in; }

extern "C" int encrypt(ConstBuffer key, ConstBuffer input, MutBuffer* output) {
    string k((char*)key.data, key.size);
    string in((char*)input.data, input.size);
    
    auto sq = build_square(k);
    auto pos = get_pos(sq);
    string prep = prepare(in);
    string out;
    
    for (size_t i = 0; i < prep.size(); i += 2) {
        char a = prep[i], b = prep[i+1];
        auto [r1,c1] = pos[a];
        auto [r2,c2] = pos[b];
        if (r1 == r2) {
            out += sq[r1][(c1+1)%5];
            out += sq[r2][(c2+1)%5];
        } else if (c1 == c2) {
            out += sq[(r1+1)%5][c1];
            out += sq[(r2+1)%5][c2];
        } else {
            out += sq[r1][c2];
            out += sq[r2][c1];
        }
    }
    
    if (out.size() > output->size) return -1;
    memcpy(output->data, out.c_str(), out.size());
    return 0;
}

extern "C" int decrypt(ConstBuffer key, ConstBuffer input, MutBuffer* output) {
    string k((char*)key.data, key.size);
    string in((char*)input.data, input.size);
    
    auto sq = build_square(k);
    auto pos = get_pos(sq);
    string out;
    
    for (size_t i = 0; i < in.size(); i += 2) {
        char a = in[i], b = in[i+1];
        auto [r1,c1] = pos[a];
        auto [r2,c2] = pos[b];
        if (r1 == r2) {
            out += sq[r1][(c1+4)%5];
            out += sq[r2][(c2+4)%5];
        } else if (c1 == c2) {
            out += sq[(r1+4)%5][c1];
            out += sq[(r2+4)%5][c2];
        } else {
            out += sq[r1][c2];
            out += sq[r2][c1];
        }
    }
    
    if (out.size() > output->size) return -1;
    memcpy(output->data, out.c_str(), out.size());
    return 0;
}
