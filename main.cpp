#include <iostream>
#include <locale>
#include <cwctype>
#include <string>

using namespace std;

bool isVowel(wchar_t ch) {
    ch = towlower(ch);
    wstring vowels = L"aeiouаеёиоуыэюя";
    return vowels.find(ch) != wstring::npos;
}

int main() {    
    locale loc("ru_RU.utf8");
    locale::global(loc);
    wcin.imbue(loc);
    wcout.imbue(loc);

    wstring input;
    wchar_t choice;

    wcout << L"Введите строку: ";
    getline(wcin, input);

    int vowelCount = 0;
    for (wchar_t ch : input) {
        if (isVowel(ch)) vowelCount++;
    }
    wcout << L"Количество гласных: " << vowelCount << endl;

    wcout << L"Выберите регистр (L - нижний, U - верхний): ";
    wcin >> choice;

    if (choice == L'L' || choice == L'l') {
        for (wchar_t &ch : input)
            ch = towlower(ch);
        wcout << L"Строка в нижнем регистре: " << input << endl;
    }
    else if (choice == L'U' || choice == L'u') {
        for (wchar_t &ch : input)
            ch = towupper(ch);
        wcout << L"Строка в верхнем регистре: " << input << endl;
    }
    else {
        wcout << L"Некорректный выбор регистра!" << endl;
        return 1;
    }

    return 0;
}
//cегодня гулял получается

