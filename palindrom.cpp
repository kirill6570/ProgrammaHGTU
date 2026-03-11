#include <iostream>
#include <string>
using namespace std;

bool Palindrome(const string& text) {
    int left = 0;
    int right = text.length() - 1;

    while (left < right) {
        while (left < right && text[left] == ' ') left++;
        while (left < right && text[right] == ' ') right--;

        if (text[left] != text[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");
    string text;
    cout << "Введите строку: ";
    getline(cin, text);

    if (Palindrome(text)) {
        cout << "Палиндром" << endl;
    } else {
        cout << "Не палиндром" << endl;
    }
    return 0;
}
