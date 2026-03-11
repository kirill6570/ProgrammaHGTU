






















#include <iostream>
#include <string>
#include <cctype>   // было <ctype> — неправильно
using namespace std;

int main() {
    string input;
    getline(cin, input);

    string result;

    for (char ch : input) {
        if (isalpha(static_cast<unsigned char>(ch)) || ch == ' ')
            result.push_back(ch);
    }

    cout << result << endl;
    return 0;
}
