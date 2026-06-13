#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    string m[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
                  "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
                  "..-","...-",".--","-..-","-.--","--.."};
    string s, w;
    getline(cin, s);
    set<string> u;
    for (char c : s) {
        if (c == ' ') {
            if (!w.empty()) {
                sort(w.begin(), w.end());
                string code = "";
                for (char x : w) code += m[x - 'a'];
                u.insert(code);
                w = "";
            }
        } else w += c;
    }
    if (!w.empty()) {
        sort(w.begin(), w.end());
        string code = "";
        for (char x : w) code += m[x - 'a'];
        u.insert(code);
    }
    cout << u.size() << endl;
    return 0;
}
