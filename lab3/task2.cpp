#include <iostream>  
#include <vector>     
#include <cstdint>  
using namespace std;

uint64_t mod_pow(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t res = 1;     // результат с 1 начинаем
    a %= m;               // сразу остаток от деления берём
    while (b) {           // пока есть биты
        if (b & 1) res = (res * a) % m;   // если бит 1, умножаем
        a = (a * a) % m;   // возводим в квадрат по модулю
        b >>= 1;           // сдвигаем биты вправо
    }
    return res;           // вернули a^b mod m
}

vector<uint64_t> sieve(int limit) {
    vector<bool> is_prime(limit + 1, true);   // все числа простые в начале
    is_prime[0] = is_prime[1] = false;        // 0 и 1 не простые
    for (int i = 2; i * i <= limit; i++)      // идём до корня
        if (is_prime[i])                      // если i простое
            for (int j = i * i; j <= limit; j += i)
                is_prime[j] = false;          // вычёркиваем кратные
    vector<uint64_t> primes;                 
    for (int i = 2; i <= limit; i++)
        if (is_prime[i]) primes.push_back(i); // собираем простые
    return primes;                            // вернули таблицу простых
}

bool is_prime_gost(uint64_t p, uint64_t q) {
    if ((p - 1) % q != 0) return false;       // q должно делить p-1
    uint64_t R = (p - 1) / q;                 // вычисляем R
    if (R % 2 != 0) return false;             // R чётное
    if (R >= 4 * (q + 1)) return false;       // R < 4(q+1)
    if (mod_pow(2, p - 1, p) != 1) return false;    // условие Ферма
    if (mod_pow(2, (p - 1) / q, p) == 1) return false; // 2^R != 1
    return true;                              // все проверки прошли — простое
}

int main() {
    int bits;
    cout << "Vvedite bits: ";
    cin >> bits;          // вводим разрядность (8, 16, 32...)

    vector<uint64_t> primes = sieve(500);   // строим простые до 500
    uint64_t q = 0;
    for (uint64_t p : primes)               // ищем q
        if (p <= (1ULL << (bits / 2))) q = p;   // q примерно половина разрядности

    uint64_t lower = (1ULL << (bits - 1)) / q;   // нижняя граница N
    vector<uint64_t> results;                     // сюда сложим найденные простые

    for (uint64_t u = 0; u < 2000 && results.size() < 10; u += 2) {
        uint64_t p = (lower + u) * q + 1;         // кандидат в простые
        if (p > (1ULL << bits)) continue;         // если вышли за разрядность — пропускаем
        if (is_prime_gost(p, q))                  // проверяем по ГОСТу
            results.push_back(p);                 // добавили простое
    }

    cout << "\n10 prostih chisel:\n";
    for (size_t i = 0; i < results.size(); i++)
        cout << i + 1 << ": " << results[i] << endl;   // результат

    return 0;   
}