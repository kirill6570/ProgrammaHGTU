//task2.cpp
#include <iostream>      
#include <vector>        
#include <algorithm>     
#include <random>       
#include <cctype>     
using namespace std;   

bool isPrime(int n) { // Функция проверки: простое число или нет
    if (n <= 1) return false;              // 0 и 1 не простые
    for (int i = 2; i * i <= n; i++) {     // перебираем делители до корня
        if (n % i == 0) return false;      // если поделилось — составное
    }
    return true;                           // иначе простое
}

int main() {
    int n;
    cout << "Введите размер массива (n >= 10): ";
    cin >> n;                              // размер массива чисел

    minstd_rand0 gen(42); //генератор рандом чисел
    uniform_int_distribution<int> dist(-150, 150);   // диапазон -150, 150


    vector<int> arr(n); //запол массив
    for (int& x : arr) x = dist(gen);      // заполняем через range-based loop

    cout << "\n1. Исходный массив:\n";     // Выводим исходный массив
    for (int x : arr) cout << x << " ";
    cout << endl;

    vector<int> sorted = arr;              // делаем копию  // ТРЕТИЙ НАИМЕНЬШИЙ И ВТОРОЙ НАИБОЛЬШИЙ
    sort(sorted.begin(), sorted.end());    // сортируем по возрастанию

    int thirdMin = sorted[2];              // третий элемент (индекс 2)
    int secondMax = sorted[sorted.size() - 2]; // предпоследний элемент

    cout << "\n2. Третий наименьший: " << thirdMin << endl;
    cout << "   Второй наибольший: " << secondMax << endl;

    int left = min(thirdMin, secondMax);   // левая граница     //ЧИСЛА МЕЖДУ НИМИ 
    int right = max(thirdMin, secondMax);  // правая граница
    vector<int> between;

    for (int x : arr) {   //Выбираем элементы, которые строго между left и right
        if (x > left && x < right) {
            between.push_back(x);
        }
    }

    cout << "\n3. Числа между " << left << " и " << right << ":\n";
    for (int x : between) cout << x << " ";
    cout << endl;

//ПРОСТЫЕ И СОСТАВНЫЕ ЧИСЛА
    vector<int> primes;       // здесь будут простые
    vector<int> composites;   // здесь будут составные

    for (int x : arr) {
        if (isPrime(x))
            primes.push_back(x);
        else
            composites.push_back(x);
    }

    cout << "\n4. Простые числа: "; //выводим простые
    for (int x : primes) cout << x << " ";
    cout << endl;

    cout << "   Составные числа: "; //выводим составные
    for (int x : composites) cout << x << " ";
    cout << endl;

    if (primes.size() > composites.size()) {    // Сортируем ту группу, которой больше
        sort(primes.begin(), primes.end()); 
        cout << "   Простых больше, сортировка по возрастанию: ";
        for (int x : primes) cout << x << " ";
    } else {
        sort(composites.begin(), composites.end(), greater<int>()); // по убыванию
        cout << "   Составных больше, сортировка по убыванию: ";
        for (int x : composites) cout << x << " ";
    }
    cout << endl;

    int m; //Массив случайных чисел
    cout << "\n5. Введите размер массива символов: ";
    cin >> m;

    // Генерируем (от 32 до 126)
    uniform_int_distribution<int> charDist(32, 126);
    vector<char> chars(m);
    for (char& c : chars) c = charDist(gen);

    cout << "   Массив символов:\n   ";  // Выводим исходный массив символов
    for (char c : chars) cout << c << " ";
    cout << endl;

    auto it = remove_if(chars.begin(), chars.end(), [](char c) {     // Удаляем цифры и строчные буквы
        return isdigit(c) || (c >= 'a' && c <= 'z');
    });
    chars.erase(it, chars.end());

    cout << "   После удаления цифр и строчных букв:\n   ";
    for (char c : chars) cout << c << " ";
    cout << endl;

    vector<int> evens; // ЧЁТНЫЕ ЭЛЕМЕНТЫ 
    for (int x : arr) {
        if (x % 2 == 0) evens.push_back(x);
    }

    cout << "\n6. Чётные элементы:\n";
    for (int x : evens) cout << x << " ";
    cout << endl;

    return 0;   
}   