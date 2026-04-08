#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

// 1. Быстрое возведение в степень по модулю
//    Вычисляет (a^b) % m за O(log b)
uint64_t mod_pow(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t res = 1;      // Результат
    a = a % m;             // Приводим a к остатку по модулю m

    while (b > 0) {
        // Если текущий бит b равен 1, умножаем результат на a
        if (b & 1) {
            res = (res * a) % m;
        }
        // Возводим a в квадрат и переходим к следующему биту
        a = (a * a) % m;
        b >>= 1;           // Сдвигаем b вправо (делим на 2)
    }
    return res;
}

// 2. Решето Эратосфена
//    Возвращает вектор всех простых чисел до limit
vector<uint64_t> sieve(int limit) {
    // Вектор-флаг: true — число простое, false — составное
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;  // 0 и 1 — не простые

    // Алгоритм решета Эратосфена
    for (int i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            // Вычёркиваем все кратные i, начиная с i*i
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    // Собираем простые числа в вектор
    vector<uint64_t> primes;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

//    Основана на теореме Диемитко:
//    Если n = q*R + 1, R — чётное, R < 4(q+1),
//    и 2^(n-1) ≡ 1 (mod n), а 2^R ≠ 1 (mod n),
//    то n — простое число.
bool is_prime_gost(uint64_t p, uint64_t q) {
    // Условие 1: p = q * R + 1 (проверяем, что p-1 делится на q)
    if ((p - 1) % q != 0) return false;

    // Вычисляем R
    uint64_t R = (p - 1) / q;

    // Условие 2: R должно быть чётным
    if (R % 2 != 0) return false;

    // Условие 3: R < 4*(q + 1)
    if (R >= 4 * (q + 1)) return false;

    // Условие 4 (малая теорема Ферма): 2^(p-1) ≡ 1 (mod p)
    if (mod_pow(2, p - 1, p) != 1) return false;

    // Условие 5: 2^((p-1)/q) ≠ 1 (mod p)
    // То есть 2^R ≠ 1 (mod p)
    if (mod_pow(2, (p - 1) / q, p) == 1) return false;
    return true;
}

// ГЛАВНАЯ ФУНКЦИЯ
int main() {
    int bits;
    cout << "Vvedite bits: ";
    cin >> bits;

    // Шаг 1: строим таблицу простых чисел до 500 (решето Эратосфена)
    vector<uint64_t> primes = sieve(500);

    // Шаг 2: выбираем q — простое число разрядностью ~ bits/2
    uint64_t q = 0;
    for (uint64_t p : primes) {
        if (p > (1ULL << (bits / 2))) break;
        q = p;
    }

    // Шаг 3: вычисляем нижнюю границу для N
    // N = floor(2^(bits-1) / q)
    uint64_t lower = (1ULL << (bits - 1)) / q;

    // Шаг 4: перебираем чётные u и находим простые числа
    vector<uint64_t> results;

    for (uint64_t u = 0; u < 2000 && results.size() < 10; u += 2) {
        uint64_t N = lower + u;           // N = floor(2^(bits-1)/q) + u
        uint64_t p = N * q + 1;           // p = N * q + 1

        // Проверяем, что p не превышает 2^bits
        if (p > (1ULL << bits)) continue;

        // Проверяем p на простоту по ГОСТ
        if (is_prime_gost(p, q)) {
            results.push_back(p);         // Добавляем в результат
        }
    }

    // Шаг 5: выводим 10 найденных простых чисел
    cout << "\n10 prostih chisel:\n";
    for (size_t i = 0; i < results.size(); i++) {
        cout << i + 1 << ": " << results[i] << endl;
    }

    return 0;
}
