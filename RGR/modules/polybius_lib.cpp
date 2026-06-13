#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cctype>
using namespace std;
const string ALPH = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
vector<vector<char>> sq(5, vector<char>(5));
map<char, pair<int, int>> pos;
bool init = false;
void build() { if (init) return; int k = 0;
    for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) { sq[i][j] = ALPH[k++]; pos[sq[i][j]] = {i, j}; }
    init = true; }
extern "C" string polybiusEncrypt(const string &text) { build(); string result;
    for (size_t i = 0; i < text.size(); i++) { char ch = toupper(text[i]); if (ch == 'J') ch = 'I';
        if (pos.count(ch)) { int r = pos[ch].first+1, c = pos[ch].second+1; result += to_string(r)+to_string(c)+" "; } }
    if (!result.empty()) result.pop_back(); return result; }
extern "C" string polybiusDecrypt(const string &text) { build(); string result; stringstream ss(text); string token;
    while (ss >> token) { if (token.size()==2) { int r=token[0]-'1', c=token[1]-'1';
        if (r>=0&&r<5&&c>=0&&c<5) result += sq[r][c]; else result += '?'; } } return result; }
