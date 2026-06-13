#include "crypto_interface.h"
#include <cstring>
#include <random>
#include <vector>

static long long mod_pow(long long base, long long power, long long mod) {
    long long result = 1;
    base %= mod;
    while (power > 0) {
        if (power & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        power >>= 1;
    }
    return result;
}

static long long mod_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

static bool is_prime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

static long long gen_prime() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dist(100, 300);
    long long p;
    do { p = dist(gen); } while (!is_prime(p));
    return p;
}

static long long n, e, d;
static bool init = false;

static void init_rsa() {
    if (init) return;
    long long p = gen_prime();
    long long q = gen_prime();
    while (p == q) q = gen_prime();
    n = p * q;
    long long phi = (p - 1) * (q - 1);
    e = 17;
    while (mod_inverse(e, phi) == -1 && e < phi) e++;
    d = mod_inverse(e, phi);
    init = true;
}

static AlgorithmInfo info = {"rsa", 0};

extern "C" const AlgorithmInfo* get_algorithm_info() {
    if (!init) init_rsa();
    return &info;
}

extern "C" size_t get_output_size(size_t input_size, int operation_type) {
    return input_size * sizeof(long long);
}

extern "C" int encrypt(ConstBuffer key, ConstBuffer input, MutBuffer* output) {
    if (!init) init_rsa();
    size_t exp = input.size * sizeof(long long);
    if (output->size < exp) return -1;
    long long* out = (long long*)output->data;
    for (size_t i = 0; i < input.size; i++)
        out[i] = mod_pow(input.data[i], e, n);
    return 0;
}

extern "C" int decrypt(ConstBuffer key, ConstBuffer input, MutBuffer* output) {
    if (!init) init_rsa();
    size_t blocks = input.size / sizeof(long long);
    if (output->size < blocks) return -1;
    const long long* in = (const long long*)input.data;
    for (size_t i = 0; i < blocks; i++) {
        long long dec = mod_pow(in[i], d, n);
        output->data[i] = (unsigned char)(dec & 0xFF);
    }
    return 0;
}
