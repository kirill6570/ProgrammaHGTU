#include <string>
#include <sstream>
#include <cstdint>
using namespace std;

long long powMod(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

extern "C" string rsaEncrypt(const string &message, long long d, long long N) {
    string result;
    for (size_t i = 0; i < message.size(); i++) {
        long long m = (unsigned char)message[i];
        long long e = powMod(m, d, N);
        result += to_string(e) + " ";
    }
    if (!result.empty()) result.pop_back();
    return result;
}

extern "C" string rsaDecrypt(const string &cipher, long long c, long long N) {
    string result;
    stringstream ss(cipher);
    string token;
    while (ss >> token) {
        long long e = stoll(token);
        long long m = powMod(e, c, N);
        result += (char)m;
    }
    return result;
}

