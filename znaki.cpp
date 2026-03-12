#include <iostream>
#include <locale>
#include <cwctype>
#include <string>
using namespace std;

int main() {
    locale::global(locale("ru_RU.utf8"));
    wcin.imbue(locale());
    wcout.imbue(locale());

    wstring input;
    getline(wcin, input);

    wstring result;

    for (wchar_t ch : input) {
        if (iswalpha(ch) || ch == L' ')
            result.push_back(ch);
    }

    wcout << result << endl;
    return 0;
}






















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
