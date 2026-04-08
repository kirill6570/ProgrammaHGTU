#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

// 1. Быстрое возведение в степень по модулю
//    Вычисляет (a^b) % m за O(log b)
uint64_t mod_pow(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t res = 1;
    a = a % m;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

// 2. Решето Эратосфена
//    Возвращает вектор всех простых чисел до limit
vector<uint64_t> sieve(int limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    vector<uint64_t> primes;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

// 3. Проверка числа на простоту по ГОСТ Р 34.10-94 (теорема Диемитко)
bool is_prime_gost(uint64_t p, uint64_t q) {
    // Условие 1: p = q * R + 1
    if ((p - 1) % q != 0) return false;
    uint64_t R = (p - 1) / q;
    // Условие 2: R чётное
    if (R % 2 != 0) return false;
    // Условие 3: R < 4(q+1)
    if (R >= 4 * (q + 1)) return false;
    // Условие 4: 2^(p-1) ≡ 1 mod p
    if (mod_pow(2, p - 1, p) != 1) return false;
    // Условие 5: 2^R ≠ 1 mod p
    if (mod_pow(2, (p - 1) / q, p) == 1) return false;
    return true;
}

int main() {
    int bits;
    cout << "Vvedite bits: ";
    cin >> bits;

    // Шаг 1: решето Эратосфена до 500
    vector<uint64_t> primes = sieve(500);

    // Шаг 2: выбрать q (простое, разрядность ~ bits/2)
    uint64_t q = 0;
    for (uint64_t p : primes) {
        if (p > (1ULL << (bits / 2))) break;
        q = p;
    }

    // Шаг 3: нижняя граница для N
    uint64_t lower = (1ULL << (bits - 1)) / q;
    vector<uint64_t> results;

    // Шаг 4: перебор чётных u, поиск 10 простых чисел
    for (uint64_t u = 0; u < 2000 && results.size() < 10; u += 2) {
        uint64_t N = lower + u;
        uint64_t p = N * q + 1;
        if (p > (1ULL << bits)) continue;
        if (is_prime_gost(p, q)) {
            results.push_back(p);
        }
    }

    // Шаг 5: вывод результатов
    cout << "\n10 prostih chisel:\n";
    for (size_t i = 0; i < results.size(); i++) {
        cout << i + 1 << ": " << results[i] << endl;
    }

    return 0;
} 
