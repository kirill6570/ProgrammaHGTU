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
    wchar_t choice;

    wcout << L"Введите строку: ";
    getline(wcin, input);

    wcout << L"Выберите регистр (L - нижний, U - верхний): ";
    wcin >> choice;

    if (choice == L'L' || choice == L'l') {
        for (wchar_t &ch : input) ch = towlower(ch);
        wcout << L"Строка в нижнем регистре: " << input << endl;
    } 
    else if (choice == L'U' || choice == L'u') {
        for (wchar_t &ch : input) ch = towupper(ch);
        wcout << L"Строка в верхнем регистре: " << input << endl;
    } 
    else {
        wcout << L"Некорректный выбор регистра!" << endl;
        return 1;
    }

    return 0;
}